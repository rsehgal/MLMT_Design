import uproot
import numpy as np
from sklearn.ensemble import RandomForestRegressor
from sklearn.multioutput import MultiOutputRegressor
from sklearn.metrics import mean_squared_error, r2_score

# -------- Config -------- #
train_file_path = "train.root"
test_file_path = "test.root"
tree_name = "groundTruthPoCA"  # Replace with actual tree name

num_train_events = 10000   # Set number of training events to load
num_test_events = 0 #100000 # Set number of test events to load
# ------------------------ #

def load_data(file_path, tree_name, num_events):
    tree = uproot.open(file_path)[tree_name]
    if num_events == 0:
        data = tree.arrays(library="np")
    else:
        data = tree.arrays(library="np", entry_stop=num_events)
    
    all_keys = list(data.keys())
    input_keys = all_keys[:12]
    output_keys = all_keys[-3:]
    
    X = np.column_stack([data[k] for k in input_keys])
    y = np.column_stack([data[k] for k in output_keys])
    
    # Filter out rows where any y is -50000
    valid_mask = ~np.any(y == -50000, axis=1)
    X = X[valid_mask]
    y = y[valid_mask]
    
    return X, y, output_keys

# Load training data
X_train, y_train, output_keys = load_data(train_file_path, tree_name, num_train_events)
print("==== Training Data loaded ====")
# Load testing data
X_test, y_test, _ = load_data(test_file_path, tree_name, num_test_events)
print("==== Testing Data loaded ====")

# Train model
model = MultiOutputRegressor(RandomForestRegressor(n_estimators=100, random_state=42))
model.fit(X_train, y_train)
print("==== Model Ready  ====")

# Predict
y_pred = model.predict(X_test)
print("==== Prediction Done ====")
# Evaluation
mse = mean_squared_error(y_test, y_pred, multioutput='raw_values')
r2 = r2_score(y_test, y_pred, multioutput='raw_values')

print("\nEvaluation per output coordinate:")
for i, key in enumerate(output_keys):
    print(f"{key}: MSE = {mse[i]:.4f}, R² = {r2[i]:.4f}")

print("==== Evaluation Done =====")

np.savetxt("output.csv", y_pred, delimiter=" ")

print("==== Output file written ====")
