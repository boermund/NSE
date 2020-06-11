
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

omega = [0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9]
zeit = [525,168,83,51,34,28,15,10,5,2]
it = [326248,97305,51516,31892,20990,17174,9247,5723,3024,869]


plt.rc("font", family="serif")
plt.rc('xtick',labelsize=16)
plt.rc('ytick',labelsize=16)
#plt.rc('xlabel',fontsize=12) # using a size in points
#plt.rc('ylabel',fontsize=12) # using a size in points

plt.plot(omega, zeit,color = 'yellowgreen')
plt.xticks(np.arange(0.1, 2.0,step = 0.2))
plt.xlim(0,2)
plt.ylim(0,550)
plt.xlabel('$\omega$', fontsize=16)
plt.ylabel('t $[s]$', fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Omega_Zeit.pdf')
plt.show()



plt.plot(omega, it,color = 'darkgoldenrod')
plt.xticks(np.arange(0.1, 2.0,step = 0.2))
plt.xlim(0,2)
plt.ylim(0,330000)
plt.yticks( [300000,250000,200000,150000,100000,50000],
            [300,250,200,150,100,50])
plt.xlabel('$\omega$',fontsize=16)
plt.ylabel('Anzahl Iterationen  $[10^3]$', fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Omega_Iterationen.pdf')
plt.show()





anzahlgitterpunkte = ['60x60','70x70','100x100','200x200','300x300','400x400','500x500','600x600']

gitterpunkte = [3600,4900,10000,40000,90000,160000,250000,360000]
gitterpunkte = np.array(gitterpunkte)
gitterpunktelog = np.log10(gitterpunkte)
zeit = [0.02,0.02,0.08,0.58,3.02,9.62,23.35,48.28]
zeit  = np.array(zeit)
zeitlog = np.log10(zeit)

Iterationen = [1055,1451,3024,12356,27904,49648,77583,111710]

gitterpunkteit = [4900,10000,40000,90000,160000,250000,360000,490000,1000000]
zeitit = [1,2,3.2,6.9,11.2,19.8,27.7,38.3,79]

func = []
for i in gitterpunkteit:
    func.append(2*i)
print(func)


plt.plot(gitterpunkte, zeit,color = 'yellowgreen')

plt.xticks( [10000,40000,90000,160000,250000,360000],
            [ 1, 4, 9,16,25,36])
plt.xlim(0,380000)
plt.ylim(0,50)
plt.xlabel('Anzahl der Gitterpunkte $[10^4]$',  fontsize=16)
plt.ylabel('t $[min]$', fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Aufloesung_Zeit.pdf')
plt.show()


plt.plot(gitterpunkte, Iterationen,color = 'darkgoldenrod')
 
plt.xticks( [10000,40000,90000,160000,250000,360000],
            [ 1, 4, 9,16,25,36])
plt.yticks( [20000,40000,60000,80000,100000],
            [ 2,4,6,8,10])
plt.xlim(0,380000)
plt.ylim(0,116000)
plt.xlabel('Anzahl der Gitterpunkte  $[10^4]$', fontsize=16)
plt.ylabel('Anzahl Iterationen $[10^4]$',  fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Aufloesung_Iterationen.pdf')
plt.show()


plt.plot(gitterpunktelog, zeitlog,color = 'darkgoldenrod')
 
#plt.xticks( [10000,40000,90000,160000,250000,360000],
     #       [ 1, 4, 9,16,25,36])
#plt.yticks( [20000,40000,60000,80000,100000],
      #      [ 2,4,6,8,10])
#plt.xlim(0,380000)
#plt.ylim(0,116000)
plt.grid()
plt.xlabel('Anzahl der Gitterpunkte logarithmisch', fontsize=16)
plt.ylabel(' Zeit logarithmisch',  fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Aufloesung_zeit_log.pdf')
plt.show()




plt.plot(gitterpunkteit,zeitit,color = 'darkgoldenrod')
#plt.plot(gitterpunkteit, ,color = 'darkgoldenrod')
plt.xlim(0,1010000)
plt.ylim(0,82) 
plt.xticks( [40000,90000,160000,250000,360000, 490000,1000000],
            [ 4, 9,16,25,36,49,100])

plt.xlabel('Anzahl der Gitterpunkte  $[10^4]$', fontsize=16)
plt.ylabel('t $[s]$',  fontsize=16)
plt.tight_layout() 
plt.savefig('C:/Users/Anna Rockstroh/Documents/Studium/1 Physik/3 F-Praktikum/CP Navier Stokes/Auswertung SOR/Aufloesung_Zeit_IT.pdf')
plt.show()

