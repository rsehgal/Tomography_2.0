import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
import sys
from matplotlib import pyplot as plt
#from helpers import *
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler(feature_range=(0, 1))

df = pd.read_csv(sys.argv[1],names=['incomingX','incomingY','incomingZ','outgoingX','outgoingY','outgoingZ','meanX','meanY','meanZ'])
x=df[['incomingX','incomingY','incomingZ','outgoingX','outgoingY','outgoingZ']]
y=df[['meanX']]#,'meanY','meanZ']]

x_train,x_test,y_train,y_test=train_test_split(x,y,test_size=0.75)
x_train = x_train.to_numpy()
x_test = x_test.to_numpy()
y_train = y_train.to_numpy()
y_test = y_test.to_numpy()
#x_train_scaled = scaler.fit_transform(x_train)
#x_train = pd.DataFrame(x_train_scaled)
#
#x_test_scaled = scaler.fit_transform(x_test)
#x_test = pd.DataFrame(x_test_scaled)

from sklearn import neighbors
from sklearn.metrics import mean_squared_error 
from math import sqrt
rmse_val = [] #to store rmse values for different k
K=5
x_val = []
for K in range(3):
	K = K+1
	model = neighbors.KNeighborsRegressor(n_neighbors = K)
	x_val.append(K)

	model.fit(x_train, y_train)  #fit the model
	pred=model.predict(x_test) #make prediction on test set
	error = sqrt(mean_squared_error(y_test,pred)) #calculate rmse
	rmse_val.append(error) #store rmse values
	print("Error for K = ",K," is : ",error)
	#print('RMSE value for k= ' , K , 'is:', error)

print("X size : ",len(x_val)," : rmse_val size : ",len(rmse_val))
#curve = pd.DataFrame(rmse_val) #elbow curve 
#curve.plot()
print((x_val,rmse_val))
plt.scatter(x_val,rmse_val,marker="+",color="red");
#plt.show()

y_test_pred = model.predict(x_test)
print(type(y_test_pred))
print(y_test_pred.shape)
supList=[]
for i in range(y_test_pred.shape[0]):
	subList=[]
	subList.append(y_test[i][0])
	subList.append(y_test_pred[i][0])
	supList.append(subList)

supArr = np.array(supList)
print((supArr))

np.savetxt("output.txt",supArr)
'''
if int(sys.argv[3])==1:
	df = pd.read_csv(sys.argv[1],names=['start11','start2','ins1','ins2','end1','end2','ins3'])
	x=df[['start11','start2','ins1','ins2','end1','end2','ins3']]
	y=df[['ins3']]
else:
	df = pd.read_csv(sys.argv[1],names=['start','inspected_xz','end','inspected_zx'])
	x=df[['start','inspected_xz','end']]
	y=df['inspected_zx']
'''

#create_polynomial_regression_model(x,y,int(sys.argv[2]))
