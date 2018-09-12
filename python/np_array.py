import numpy as np
import time

print("************* CREATION 1D")
# list python
a = [1,3,6]
type(a)

# ndarray de numpy
b = np.array([1,2,3])
type(b)
print(b)



#### TAB 2D
print("************* CREATION 2D")
a = np.zeros( (4,6), dtype=int )
print("tab2D a="+str(a))
print("size="+str(a.size))
print("shape="+str(a.shape))



################ SLICING
print("************* SLICING")
a = np.array([127, 25, 34, 561, 87,6, 123])
print(a)
b = a[1:3]          # sous tableau des cases 1 à 3 non inclus
print("sous partie de la case 1 à la case 3 non incluse : "+str(b))

b=a[3:]             # sous tableau de a des cases de 4 à la fin
print("sous partie de 3 à la fin : "+str(b))
b[0] = 111          # b est une sorte de vue sur a, si on change b, on change aussi a. b[0] et a[3] "pointe" vers la même valeur
b[1] = 112
print("b[0] et b[1] sont changés, a l'est donc aussi a="+str(a))

b *= 2
print("b *= 2 => b="+str(b))
print("a est changé également : a="+str(a))

b = b*2
print("b = b*2 => b="+str(b))
print("a n'est pas changé, b pointe maintenant sur des nouvelles données : a="+str(a))



################ COMPTER
print("************* COMPTER")

a = (np.random.random( 10000000  )*150).astype(int)
print(a)

t0 = time.time()
ni = ((25 < a) & (a < 50)).sum()
print("nb 25<n<50="+str(ni))
duree = time.time()-t0
print("ni = ((25 < a) & (a < 50)).sum()\n chrono="+str(duree))

t0 = time.time()
ni = np.count_nonzero((25 < a) & (a < 50))
print("nb 25<n<50="+str(ni))
duree = time.time()-t0
print("ni = np.count_nonzero((25 < a) & (a < 50))\n chrono="+str(duree))

t0 = time.time()
ni = a[(25 < a) & (a < 50)].size
print("nb 25<n<50="+str(ni))
duree = time.time()-t0
print("ni = a[(25 < a) & (a < 50)].size\n chrono="+str(duree))

t0 = time.time()
ni = len([x for x in a.ravel() if 25 < x < 50])
print("nb 25<n<50="+str(ni))
duree = time.time()-t0
print("ni = len([x for x in a.ravel() if 25 < x < 50])\n chrono="+str(duree))

t0 = time.time()
ni = sum(1 for i in a.ravel() if 25 < i < 50)
print("nb 25<n<50="+str(ni))
duree = time.time()-t0
print("ni = sum(1 for i in a.ravel() if 25 < i < 50)\nchrono="+str(duree))


# A faire. Compter les nombres impairs
t0 = time.time()
ni = np.count_nonzero( a%2 == 1)
print("nb impair="+str(ni))
duree = time.time()-t0
print("ni = np.count_nonzero( a%2 == 1)\nchrono="+str(duree))



print("************* APPLY") # faire +& à tous les nombres impaires
# A faire. +1 à tous les impairs

# SOL1 : VECTORIZE
aa = a.copy()

print("nb impair avant="+str(np.count_nonzero( a%2==1)))
t0 = time.time()
def inc_imp(x):
    if x%2==1:
        return x+1
    else:
        return x
vfunc = np.vectorize(inc_imp)
a=vfunc(a) 
duree = time.time()-t0
print("apply_along_axis. chrono="+str(duree))
print("nb impair apres="+str(np.count_nonzero( a%2==1)))

#SOL 2 LAMBDA
a = aa.copy()
print("\nnb impair avant="+str(np.count_nonzero( a%2==1)))
t0 = time.time()
inc_impair = lambda x: x+1 if x%2==1 else x
a = inc_impair(a.all())
duree = time.time()-t0
print("lambda inc_impair. chrono="+str(duree))
print("nb impair apres="+str(np.count_nonzero( a%2==1)))




print("************* PEFORMANCE")
# Remplissez un tableau de NP patients comportants NT relevés de températures. Témpérature comprise entre 36 et 39 tirée au hasard.
t0 = time.time()
p = 36 + (np.random.random(  (5000,10000) ))*(39-36)
print("shape="+str(p.shape))
# Calculez la température moyenne des 5 patients et la ranger dans un nouveau tableau t
t = np.empty( p.shape[0], dtype=float )
for i in range(p.shape[0]):
    t[i] = p[i].sum() / p.shape[1]
#print("temperatures moyennes="+str(t))
print(t.shape)
duree = time.time()-t0
print("chrono="+str(duree))
