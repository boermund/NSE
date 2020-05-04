from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

# Put x and y values into an array

A = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/xval.txt')
B = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/yval.txt')

# first derivation /dx

# Put numerical and analytical calculated arrays in an array
Z = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/new_p.txt')
W =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/p_ana.txt')

fig = plt.figure(1)
ax = fig.gca(projection='3d')

X = A
Y = B
X, Y = np.meshgrid(X, Y)
 
surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, W, cmap=cm.plasma,
                       linewidth=0, antialiased=False)  
plt.show()