#TJ 27.10.19

import matplotlib.pyplot as plt
from matplotlib import pyplot, cm
import csv
import numpy as np
import pandas as pd

uspeed      = np.array([])
vspeed      = np.array([])
pressure    = np.array([])
y=[]
x_unit= "mA"
y_unit= "mW"



with open ('uspeed.csv','r') as csvfile:
    csv_reader = csv.reader(csvfile, delimiter=',')
    for row in csv_reader:
        x=len(row)-1
        uspeed  = np.append([uspeed],([(row[0:-2])]))
with open ('vspeed.csv','r') as csvfile:
    csv_reader = csv.reader(csvfile, delimiter=',')
    for row in csv_reader:
        vspeed  = np.append([vspeed],([(row[0:-2])]))
with open ('pressure.csv','r') as csvfile:
    csv_reader = csv.reader(csvfile, delimiter=',')
    for row in csv_reader:
        pressure  = np.append([pressure],([(row[0:-2])]))

y=len(uspeed)
uspeed=np.asfarray(uspeed,float)
uspeed=np.reshape(uspeed,([x,int(y/x)]))
vspeed=np.asfarray(vspeed,float)
vspeed=np.reshape(vspeed,([x,int(y/x)]))
pressure=np.asfarray(pressure,float)
pressure=np.reshape(pressure,([x,int(y/x)]))

print(uspeed,vspeed,pressure)

uspeed      = np.flipud(uspeed*0.1)
vspeed      = np.flipud(vspeed*-0.1)
pressure    = np.flipud(pressure)

print(uspeed,vspeed,pressure)

a= np.linspace(0,x,int(y/x))
b= np.linspace(0,int(y/x),x)
X ,Y= np.meshgrid(a,b)

fig = pyplot.figure(figsize=(11, 7), dpi=100)
pyplot.contourf(X, Y, pressure, alpha=0.5, cmap=cm.viridis)
pyplot.colorbar()
pyplot.contour(X, Y, pressure, cmap=cm.viridis)
pyplot.quiver(X, Y, uspeed, vspeed)
pyplot.xlabel('X')
pyplot.ylabel('Y')
pyplot.axis([-2,x+2,-2,int(y/x)+2])
pyplot.show()
"""
fig2 = pyplot.figure(figsize=(11, 7), dpi=100)
pyplot.contourf(X, Y, pressure, alpha=0.5, cmap=cm.viridis)
pyplot.colorbar()
pyplot.contour(X, Y, pressure, cmap=cm.viridis)
pyplot.streamplot(X, Y, uspeed, vspeed)
pyplot.xlabel('X')
pyplot.ylabel('Y')
pyplot.show()
"""