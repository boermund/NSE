
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

# Plot the numerical calculated derivates in comparison to the analytical, to check if the derivates look same



# Put x and y values into an array

A = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_values.txt')
B = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_values.txt')

# first derivation /dx

# Put numerical and analytical calculated arrays in an array
Z = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_der_first.txt')
W =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_der_ana_first.txt')

fig = plt.figure(1)
ax = fig.gca(projection='3d')

X = A[0:-1] 
Y = B
X, Y = np.meshgrid(X, Y)

# make the analytical one shorter to get the same sizes
W = W[:,0:-1] 


surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, W, cmap=cm.plasma,
                       linewidth=0, antialiased=False)  
plt.show()

# first derivation /dy
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_der_first.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_der_ana_first.txt')

fig = plt.figure(2)
ax = fig.gca(projection='3d')

X = A
Y = B[0:-1]
X, Y = np.meshgrid(X, Y)

V = V[0:-1,:]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

#second derivations /dx

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_sec_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_sec_der_ana.txt')

fig = plt.figure(3)
ax = fig.gca(projection='3d')

X = A[1:-1]
Y = B
X, Y = np.meshgrid(X, Y)

V = V[:,1:-1]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

#second derivations /dy

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_sec_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_sec_der_ana.txt')

fig = plt.figure(4)
ax = fig.gca(projection='3d')

X = A
Y = B[1:-1]
X, Y = np.meshgrid(X, Y)

V = V[1:-1,:]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

# non linear quadratic function u^2 /dx

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_nl2_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_nl2_der_ana.txt')

fig = plt.figure(5)
ax = fig.gca(projection='3d')

X = A[1:-1]
Y = B
X, Y = np.meshgrid(X, Y)

V = V[:,1:-1]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

# non linear quadratic function u^2 /dy

U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_nl2_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_nl2_der_ana.txt')

fig = plt.figure(6)
ax = fig.gca(projection='3d')

X = A
Y = B[1:-1]
X, Y = np.meshgrid(X, Y)

V = V[1:-1,:]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                      linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

'''
# testfunction v
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/testfunc_v.txt')
#V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_nl2_der_ana.txt')


fig = plt.figure()
ax = fig.gca(projection='3d')
X = A
Y = B
X, Y = np.meshgrid(X, Y)
surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
#surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
 #                      linewidth=0, antialiased=False)

plt.show()

'''
# testfunction uv
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/uv_test.txt')

fig = plt.figure(7)
ax = fig.gca(projection='3d')

X = A
Y = B
X, Y = np.meshgrid(X, Y) 

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)

plt.show()

# non linear u*v /dx
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_nluv_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/x_nluv_der_ana.txt')

fig = plt.figure(8)
ax = fig.gca(projection='3d')

X = A[1:-1]
Y = B[1:len(B)]
X, Y = np.meshgrid(X, Y)

V = V[0:-1,1:-1]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()

# non linear u*v /dy
U = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_nluv_der.txt')
V =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/y_nluv_der_ana.txt')


fig = plt.figure(9)
ax = fig.gca(projection='3d')

X = A[1:len(B)]
Y = B[1:-1]
X, Y = np.meshgrid(X, Y)

V = V[1:-1,0:len(B)-1]

surf = ax.plot_surface(X, Y, U, cmap=cm.viridis,
                       linewidth=0, antialiased=False)
surf = ax.plot_surface(X, Y, V, cmap=cm.plasma,
                       linewidth=0, antialiased=False)

plt.show()


