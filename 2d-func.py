#C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/testfunc_u.txt'
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

fig = plt.figure()
ax = fig.gca(projection='3d')

XY = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_and_y.txt')
Z = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/testfunc_u.txt')

X = XY[0]
Y = XY[1]

X, Y = np.meshgrid(X, Y)
#W = np.cos(X)*np.sin(Y)*3

surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis,
                       linewidth=0, antialiased=False)                       

plt.show()