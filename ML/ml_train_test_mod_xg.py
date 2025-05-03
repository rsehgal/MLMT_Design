import uproot
import numpy as np
from sklearn.ensemble import RandomForestRegressor
from sklearn.multioutput import MultiOutputRegressor
from sklearn.metrics import mean_squared_error, r2_score
from xgboost import XGBRegressor
# -------- Config -------- #
train_file_path = "train.root"
test_file_path = "test.root"
tree_name = "groundTruthPoCA"  # Replace with actual tree name

num_train_events = 10000   # Set number of training events to load
num_test_events = 0 #100000 # Set number of test events to load
# ------------------------ #

def WriteRootTree(filename,treename,branchesName,data):
    output_branches={}
    for i, key in enumerate(branchesName):
        output_branches[key] = data[:, i]
    with uproot.recreate(filename) as f:
        f[treename] = output_branches  # Tree name = "predictionTree"

    print("==== ROOT file written ====")

def load_data(file_path, tree_name, num_events,train=True):
    tree = uproot.open(file_path)[tree_name]
    if num_events == 0:
        data = tree.arrays(library="np")
    else:
        data = tree.arrays(library="np", entry_stop=num_events)
    
    all_keys1 = list(data.keys())
    print(all_keys1)
    all_keys = all_keys1[0:15]
    print(all_keys)
    input_keys = all_keys[:12]
    input_keys = input_keys + [all_keys1[15]]
    print(input_keys)
    output_keys = all_keys[-3:]
    #exit()
    
    X = np.column_stack([data[k] for k in input_keys])
    y = np.column_stack([data[k] for k in output_keys])
    #angleDev = np.column_stack(data["angleDev"])
    
    # Filter out rows where any y is -50000
    valid_mask = ~np.any(y == -50000, axis=1)
    if train:
        X = X[valid_mask]
        y = y[valid_mask]
    #angleDev = angleDev[valid_mask]
    
    return X, y, output_keys#,angleDev

# Load training data
X_train, y_train, output_keys = load_data(train_file_path, tree_name, num_train_events,True)
print("==== Training Data loaded ====")
# Load testing data
X_test, y_test, _ = load_data(test_file_path, tree_name, num_test_events,False)
print("==== Testing Data loaded ====")

# Train model
#model = MultiOutputRegressor(RandomForestRegressor(n_estimators=100, random_state=42))
model = MultiOutputRegressor(XGBRegressor(objective='reg:squarederror'))
model.fit(X_train, y_train)
print("==== Model Ready  ====")

# Predict
y_pred = model.predict(X_test)
print("==== Prediction Done ====")
# Evaluation

#mse = mean_squared_error(y_test, y_pred, multioutput='raw_values')
#r2 = r2_score(y_test, y_pred, multioutput='raw_values')

#print("\nEvaluation per output coordinate:")
#for i, key in enumerate(output_keys):
#    print(f"{key}: MSE = {mse[i]:.4f}, R² = {r2[i]:.4f}")

#print("==== Evaluation Done =====")

angleDev = X_test[:,12]
#angleDev_clean=angleDev[mask]

final_output = np.column_stack((y_pred,angleDev))
np.savetxt("output.csv", final_output, delimiter=" ")

branchesName = ['x','y','z','angleDev'];
WriteRootTree("prediction_xg.root","tree",branchesName,final_output)


print("==== Output file written ====")
