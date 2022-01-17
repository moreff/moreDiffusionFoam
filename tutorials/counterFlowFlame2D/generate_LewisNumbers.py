import matplotlib.pyplot as plt
import numpy as np
import cantera as ct

path_dict = 'constant/LewisNumbersDict'
path_img  = 'Le_1d_premixed.png'

p     = ct.one_atm  # [Pa]  - pressure
Tin   = 300.0       # [K]   - unburned gas temperature
width = 0.03        # [m]   - width of the domain
fuel  = "H2"
oxidizer = "O2:0.21,N2:0.79"

gas = ct.Solution('gri30.yaml')
gas.TP = Tin, p
gas.set_equivalence_ratio(1, fuel, oxidizer)
f = ct.FreeFlame(gas, width=width)

f.transport_model = 'Multi'
f.solve(0)



thermal_diff = f.thermal_conductivity/f.cp_mass/f.density_mass

fig, ax = plt.subplots(figsize=[12,8])
fo = open(path_dict, "w")
print_entry = "{:8} {:1.7f}          {:1.7f}         {}"
write_entry = "{:8} {};\n"
print('Specie      Le     Delta b/w fresh and burnt  Rel deviation [%]')
for i, specie in enumerate(gas.species_names):
    Lewis_flame = thermal_diff / f.mix_diff_coeffs[i]
    Le = (Lewis_flame[0] + Lewis_flame[-1]) / 2
    delta_Le = np.abs(Lewis_flame[0]-Lewis_flame[-1])
    print(print_entry.format(specie, Le, delta_Le, delta_Le/Le*100))
    fo.write(write_entry.format(specie, Le))
    ax.plot(f.grid, Lewis_flame, label=specie)
fo.close()
print('Lewis numbers were written to ' + path_dict)

ax.legend(ncol=2)
ax.set_xlabel('x, m')
ax.set_ylabel('Le')
fig.savefig(path_img)
print('Validation image of 1d premixed flame was written to ' + path_img)
