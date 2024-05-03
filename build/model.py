import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# Input data
'''
data = np.array([
    [200.059, 318.462, 200.342, 318.64, -20, -20],
    [208.85, 336.943, 208.537, 337.302, -10, -10],
    [268.209, 267.616, 268.494, 267.793, 0, 0],
    [337.34, 208.43, 336.722, 208.712, 10, 10],
    [320.576, 201.067, 319.441, 200.621, 20, 20],
    [319.334, 200.095, 200.156, 319.043, -20, 20],
    [337.25, 209.141, 208.968, 336.876, -10, 10],
    [208.633, 336.404, 337.456, 209.203, 10, -10],
    [201.076, 319.522, 319.018, 201.344, 20, -20],
    [252.749, 251.598, 210.478, 385.787, -10, 0],
    [387.461, 210.98, 253.311, 253.31, 0, 10],
    [253.032, 252.645, 385.658, 210.065, 10, 0],
    [210.588, 387.044, 252.854, 252.541, 0, -10]
    
])
#,[288.085, 205.51, 193.736, 429.549, 17, 9]
'''
data=np.array([
[27.835,27.8293,-20,-20],
[27.9199,27.922,-10,-10],
[24.9924,24.9939,0,0],
[22.0666,22.0848,10,10],
[22.1625,22.1737,20,20],
[22.1626,27.8235,-20,20],
[22.0809,27.917,-10,10],
[27.9244,22.0892,10,-10],
[27.838,22.1727,20,-20],
[24.9985,28.9576,-10,0],
[21.0351,25.003,0,10],
[24.9945,21.0382,10,0],
[28.9765,24.9982,0,-10],
[23.1637,30.2311,-17,9],
[26.8287,19.7633,17,-9]
])
#[23.1637,30.2311,17,9]

#testdata = np.genfromtxt('testdata.csv', delimiter=',')
testdata = np.genfromtxt('testcentroiddata.csv', delimiter=',')
print(testdata)

# Separate features (X) and target variable (y)
X = data[:, :-2]  # First four columns are input features
y = data[:, -2:]  # Last two columns are output features

print(X)
print("===============================")
print(y)

# Split the data into training and testing sets (80% train, 20% test)
#X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Instantiate the linear regression model
model = LinearRegression()

# Train the model on the training data
#model.fit(X_train, y_train)
model.fit(X, y)

# Make predictions on the testing data
y_pred = model.predict(testdata)
print("==================================")
print(y_pred)
bins=np.linspace(-100,100,1000)
#plt.hist2d(y_pred[:,0], y_pred[:,1],bins=bins)
plt.hist(y_pred[:,0],bins=500)
plt.hist(y_pred[:,1],bins=500)
plt.show()
np.savetxt("output.csv",y_pred)
# Evaluate the model
#mse = mean_squared_error(y_test, y_pred)
#print("Mean Squared Error:", mse)

