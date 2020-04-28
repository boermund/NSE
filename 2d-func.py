#C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/testfunc_u.txt'
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


#Erste Ableitungen
fig = plt.figure()
ax = fig.gca(projection='3d')

A = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_values.txt')
B = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_values.txt')
Z = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_der_first.txt')
W =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_der_ana_first.txt')

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_der_first.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_der_ana_first.txt')
# print(np.shape(W)) Zeilen und Spaltenlänge

W = W[:,0:-1] # schneidet die letzte spalte ab

X = A[0:-1] 
Y = B

print(len(X))
print(len(Y))

print(np.shape(W))
print(np.shape(Z))

X, Y = np.meshgrid(X, Y)


#W = np.cos(X)*np.sin(Y)*3

surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, W, cmap=cm.viridis,
                       linewidth=0, antialiased=False)  
plt.show()

X = A
Y = B[0:-1]
X, Y = np.meshgrid(X, Y)


V = V[0:-1,:]


print(len(X))
print(len(Y))

print(np.shape(U))
print(np.shape(V))

fig = plt.figure()
ax = fig.gca(projection='3d')

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.viridis,
                       linewidth=0, antialiased=False)

plt.show()

#Zweite Ableitungen

# x
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_sec_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_sec_der_ana.txt')

fig = plt.figure()
ax = fig.gca(projection='3d')

V = V[:,1:-1]
print(np.shape(V))

X = A[1:-1]
Y = B
X, Y = np.meshgrid(X, Y)

print(len(X))
print(len(Y))

print(np.shape(U))
print(np.shape(V))

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.viridis,
                       linewidth=0, antialiased=False)

plt.show()



# y

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_sec_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_sec_der_ana.txt')

fig = plt.figure()
ax = fig.gca(projection='3d')

V = V[1:-1,:]
print(np.shape(V))

X = A
Y = B[1:-1]
X, Y = np.meshgrid(X, Y)

print(len(X))
print(len(Y))

print(np.shape(U))
print(np.shape(V))

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.viridis,
                       linewidth=0, antialiased=False)

plt.show()



