# Validate binary diffusion coefficients using Cantera
import math
import numpy as np
import cantera as ct

def get_binary_diff_coeff(specie1, specie2, T, p, mechanism='gri30.yaml'):
    gas = ct.Solution(mechanism)
    gas.TP = T, p
    i = gas.species_names.index(specie1)
    j = gas.species_names.index(specie2)
    Dij = gas.binary_diff_coeffs[i][j]
    return Dij

dat = np.loadtxt('binaryDiffusionCoefficientsPolynomial.dat')
rel_tol = 1e-4
N_failed = 0
for i in dat:
    p, T, Dij_OF = i
    Dij_cantera = get_binary_diff_coeff('H2', 'N2', T, p)

    if not math.isclose(Dij_OF, Dij_cantera, rel_tol=rel_tol):
        N_failed += 1
        print("ERROR! For T={} and p={}: Dij_OF={} and Dij_cantera={} are not within tolerance {}".format(T, p, Dij_OF, Dij_cantera, rel_tol))

if N_failed > 0:
    print("{}/{} tests failed!".format(N_failed, len(dat)))
else:
    print("All {} tests passed with reltol={}!".format(len(dat), rel_tol))
