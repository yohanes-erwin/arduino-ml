# -*- coding: utf-8 -*-
"""
Created on Sat Feb 15 17:29:07 2020

@author: Erwin Ouyang
"""

# === Step 1: import libraries ================================================
# import library
import numpy as np
import matplotlib.pyplot as plt

# === Step 2: create data set =================================================
# train set
x_train = np.array([[16, 15, 16, 10, 16, 13,  9, 19, 10, 12, 15, 10, 16, 26, 18, 16, 20, 15,
                     10, 25, 17,  9, 21,  7,  8, 13, 18,  7, 12, 18, 19, 19, 11, 12, 19, 21,
                     21, 19, 16, 10, 13, 20,  7,  8, 15, 13, 11, 14, 16, 21, 15, 12, 17, 24,
                     17, 21, 17, 14, 24, 12, 15, 16, 17, 18, 24, 16, 15, 23, 23, 21, 13,  9,
                     13, 11,  8, 15, 16, 12, 14, 21]])
y_train = np.array([[40, 52, 48, 37, 48, 37, 37, 40, 38, 29, 42, 38, 52, 57, 47, 46, 53, 32,
                     43, 63, 44, 35, 43, 43, 37, 35, 45, 37, 40, 54, 40, 51, 39, 44, 43, 49,
                     62, 60, 45, 34, 49, 44, 35, 26, 45, 42, 43, 40, 49, 52, 42, 35, 43, 51,
                     41, 51, 52, 44, 54, 38, 48, 45, 37, 50, 62, 57, 41, 47, 49, 52, 32, 33,
                     44, 43, 31, 43, 42, 42, 47, 61]])
# test set
x_test = np.array([[13,  5, 17, 15, 10, 23, 18, 12, 22, 14,  9, 14, 14, 20, 11, 19, 10, 13, 11, 16]])
y_test = np.array([[44, 23, 47, 38, 32, 48, 40, 45, 50, 36, 37, 48, 46, 57, 42, 50, 44, 42, 45, 46]])

# === Step 3: plot data set ===================================================
# plot train set and test set
plt.scatter(x_train, y_train, label='Train set')
plt.scatter(x_test, y_test, label='Test set')
plt.xlim(0, 30)
plt.ylim(0, 100)
plt.title('Correlation between temperature and bike rentals')
plt.xlabel('Temperature $[^{\circ}C]$')
plt.ylabel('Bike-sharing users')
plt.legend()

# === Step 4: build the model =================================================
# parameters
theta_0 = 0
theta_1 = 0
# define the hypothesis function
def hypothesis(x):
    return theta_0 + theta_1*x
