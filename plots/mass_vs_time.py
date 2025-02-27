import numpy as np
import matplotlib.pyplot as plt

t_corrs_15 = [0.274, 27.4, 2.74, 27.3, 2.73, 0.273, 0.0273]

paths = ['/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_0.01/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_0.1/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_1/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_15/alpha_10/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_0.1/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_0.01/Cloud/Turb.hst',
         '/u/ageorge/athena_fork_turb_box/Turb_v2_init/Test_14/alpha_1/Cloud/Turb.hst'  
        ]


def mass_change(path):
    data = data = np.loadtxt(path, comments="#")
    cold_mass = data[:, 13]
    cold_mass =cold_mass[cold_mass !=0 ]

    time = data[:len(cold_mass), 0]
    return (cold_mass/cold_mass[0]), time
    
plt.figure(figsize=(8, 6))
for i in range(len(t_corrs_15)):
    cold_mass, time = mass_change(paths[i])
    plt.plot(time/t_corrs_15[i], cold_mass)

    
plt.yscale('log')
plt.xscale('log')
plt.xlabel(r"$t / t_{\rm eddy}$", fontsize=14)
plt.ylabel(r"$m / m(t=0)$", fontsize=14)
plt.tight_layout()
plt.savefig("/u/ageorge/athena_fork_turb_box/plots/m_vs_t.png")
