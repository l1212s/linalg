import math 
import numpy as np

A = np.array([[1,-1],[-2,2],[2,-2]])
print "A:"
print A

AT = A.transpose()
ATA = AT.dot(A)
AAT = A.dot(AT)

print "ATA"
print ATA
print "AAT"
print AAT

v_val, v_vec = np.linalg.eigh(ATA)
u_val, u_vec = np.linalg.eigh(AAT)

print "v_val"
print v_val
print "v_vec"
print v_vec
print "u_val"
print u_val
print "u_vec"
print u_vec

sigma = np.zeros((A.shape))
sigma[0][0] = math.sqrt(18.0)
print "sigma"
print sigma

V = np.zeros((v_vec.shape))
U = np.zeros((u_vec.shape))
V[:,0] = v_vec[:,1]
V[:,1] = v_vec[:,0]

U[:,0] = u_vec[:,2]
U[:,1] = u_vec[:,1]
U[:,2] = u_vec[:,0]

print "V"
print V
print "U"
print U

A_svd = U.dot(sigma).dot(V.transpose())
print "A_svd"
print A_svd

AT = A_svd.transpose()
ATA = AT.dot(A_svd)
AAT = A_svd.dot(AT)

print "svd_ATA"
print ATA
print "svd_AAT"
print AAT


