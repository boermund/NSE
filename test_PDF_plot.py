from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

# Put x and y values into an array

A = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/xval.txt')
B = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/yval.txt')

# first derivation /dx

# Put numerical and analytical calculated arrays in an array
Z = np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/new_p.txt')
W =  np.loadtxt('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Pragrammteile geschrieben/p_ana.txt')

plt.rc("font", family="serif")
plt.rc('xtick',labelsize=16)
plt.rc('ytick',labelsize=16)

fig = plt.figure(1)
ax = fig.gca(projection='3d')
#ax._axis3don = False

X = A
Y = B
X, Y = np.meshgrid(X, Y)
 
surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis,
                      linewidth=0, antialiased=False)
#surf = ax.plot_surface(X, Y, W, cmap=cm.plasma,
 #                 linewidth=0, antialiased=False) 

#ax.set_xlabel('x', fontsize = 16)
#ax.set_ylabel('y', fontsize = 16)
#ax.set_zlabel('z', fontsize = 16)

ax.set_xticks([0.0, 0.5, 1, 1.5])        
ax.set_yticks([0.0, 0.5, 1,1.5])        
ax.set_zticks([0.0, 0.5, 1]) 



ax.view_init(10, 55)

plt.show()

with PdfPages('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Barriere_0_01.pdf') as pdf:
  pdf.savefig(fig)


#with PdfPages('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/BilderSOR-Test/analytische_lsg.pdf') as pdf:
 #  pdf.savefig(fig)

   