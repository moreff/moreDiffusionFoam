import math
import numpy as np
import cantera as ct

# gas = ct.Solution('constant/foam/mech.cti')
gas = ct.Solution('gri30.yaml')

N_SP = len(gas.species_names)
entry = """{} {{
    type binaryDiffusionCoefficientsPolynomial;
    polynomialCoeffs ({});
}}
"""

f = open("constant/binaryDiffusionCoefficientsPolynomialDict", "w")

for i in range(N_SP):
    for j in range(N_SP):
        if (j>i):
            continue
        pair = gas.species_names[i] + "-" + gas.species_names[j]
        # coeff = str(gas.binary_diff_coeffs[i, j])
        coeff = str(gas.get_binary_diff_coeffs_polynomial(i,j))[1:-1]
        f.write(entry.format(pair, coeff))

f.close()
print('Binary diffusion coefficients were written to constant/binaryDiffusionCoefficientsPolynomialDict')
