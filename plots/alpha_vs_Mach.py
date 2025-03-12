### 
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import cmasher as cmr



### CONSTANTS
cs = 0.6209301549496956
t_cool_mix = 0.21648962
chi = 1000

def get_mass_ratio(path):
    data = np.loadtxt(path, comments="#")
    cold_mass = data[:, 13]
    cold_mass = cold_mass[cold_mass != 0]  
    return np.log(cold_mass[-1] / cold_mass[0])

#First calculating vturb using the turb box hst files
#paths
hst_Test_15_path = "/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_0.01/Turb/Turb.hst"
hst_Test_14_path = "/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_0.1/Turb/Turb.hst"
hst_Test_16_path = "/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_16/alpha_0.01/Turb/Turb.hst"

data_Test_15 = np.loadtxt(hst_Test_15_path, comments="#")
mass_Test_15 = data_Test_15[:, 2]
KE_Test_15 = data_Test_15[:, 6] + data_Test_15[:, 7] + data_Test_15[:, 8]
vturb_Test_15_array = np.sqrt(2 * KE_Test_15 / mass_Test_15)
vturb_Test_15 = np.mean(vturb_Test_15_array[-500:])
Mach_Test_15 = vturb_Test_15 / cs
r_cl_Test_15s = np.loadtxt("/u/ageorge/athena_fork_turb_box/M0.75_simulation_data.csv", delimiter=",", skiprows=1)[:-1,1]
t_cc_Test_15 = np.sqrt(chi) * r_cl_Test_15s / vturb_Test_15

mass_ratios_15 = [ get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_0.01/Cloud/Turb.hst"),
                   get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_0.1/Cloud/Turb.hst"),
                   get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_1/Cloud/Turb.hst"),
                   get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_10/Cloud/Turb.hst")]




data_Test_14 = np.loadtxt(hst_Test_14_path, comments="#")
mass_Test_14 = data_Test_14[:, 2]
KE_Test_14 = data_Test_14[:, 6] + data_Test_14[:, 7] + data_Test_14[:, 8]
vturb_Test_14_array = np.sqrt(2 * KE_Test_14 / mass_Test_14)
vturb_Test_14 = np.mean(vturb_Test_14_array[-500:])
Mach_Test_14 = vturb_Test_14 / cs
#r_cl_Test_14s = np.loadtxt("/u/ageorge/athena_fork_turb_box/M0.75_simulation_data.csv", delimiter=",", skiprows=1)[:-2,1]
r_cl_Test_14s = np.array([0.1062722, 0.01062722, 0.001062722])
t_cc_Test_14 = np.sqrt(chi) * r_cl_Test_14s / vturb_Test_14
#This is the wrong r_cl value inputted for test_14
mass_ratios_14 = [ get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_0.01/Cloud/Turb.hst"),
                   get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_0.1/Cloud/Turb.hst"),
                   get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_1/Cloud/Turb.hst")]
                   #get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_10/Cloud/Turb.hst")]




data_Test_16 = np.loadtxt(hst_Test_16_path, comments="#")
mass_Test_16 = data_Test_16[:, 2]
KE_Test_16 = data_Test_16[:, 6] + data_Test_16[:, 7] + data_Test_16[:, 8]
vturb_Test_16_array = np.sqrt(2 * KE_Test_16 / mass_Test_16)
vturb_Test_16 = np.mean(vturb_Test_16_array[-500:])
Mach_Test_16 = vturb_Test_16 / cs
r_cl_Test_16s = np.loadtxt("/u/ageorge/athena_fork_turb_box/M0.25_simulation_data.csv", delimiter=",", skiprows=1)[0,1] #Change slice with more sims
print
t_cc_Test_16 = np.sqrt(chi) * r_cl_Test_16s / vturb_Test_16
mass_ratios_16 = [ get_mass_ratio("/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_16/alpha_0.01/Cloud/Turb.hst")]

all_mass_ratios = mass_ratios_14 + mass_ratios_15 + mass_ratios_16
vmin, vmax = np.min(all_mass_ratios), np.max(all_mass_ratios)

plt.figure(figsize=(5, 4))

sc = plt.scatter(
                    np.concatenate([np.ones(len(r_cl_Test_15s)) * Mach_Test_15,
                                    np.ones(len(r_cl_Test_14s)) * Mach_Test_14, 
                                    np.array([Mach_Test_16])    ]),                             #Test_16 has one only element for now
                    np.concatenate([t_cool_mix / t_cc_Test_15,
                                     t_cool_mix / t_cc_Test_14,
                                     np.array([t_cool_mix / t_cc_Test_16])  ]),
                    c=np.concatenate([mass_ratios_15,
                                       mass_ratios_14,
                                        mass_ratios_16]),
                    cmap=cmr.prinsenvlag, 
                    vmin=vmin, vmax=vmax)


cbar = plt.colorbar(sc)
cbar.set_label(r"Log($M_{\rm final} / M_{\rm initial}$)", fontsize=14)

plt.xlabel(r"Mach Number ($\mathcal{M}$)", fontsize=14)
plt.ylabel(r"$\log(t_{\rm cool,mix} / t_{\rm cc})$", fontsize=14)
plt.yscale('log')
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, pos: f"{int(np.log10(x))}"))


plt.tight_layout()
plt.savefig("/u/ageorge/athena_fork_turb_box/plots/alpha_vs_Mach.png")