import matplotlib.pyplot as pyplot
import pandas as pd



fc_data = pd.read_csv("/mnt/c/dev/qspice_circuits/fc_4level_data.csv")
ode_data = pd.read_csv("./fc_4level_tb.dat", sep='\s+')

pyplot.plot(ode_data["time"],ode_data["B_u1"]-1)
pyplot.plot(fc_data["Time"],fc_data["V(vout)"])

pyplot.plot(ode_data["time"],ode_data["B_u4"])
pyplot.plot(fc_data["Time"],fc_data["V(vdc)"])

pyplot.plot(ode_data["time"],ode_data["B_u3"])
pyplot.plot(fc_data["Time"],fc_data["V(fc2p,fc2n)"])

pyplot.plot(ode_data["time"],ode_data["B_u2"])
pyplot.plot(fc_data["Time"],fc_data["V(fc1p,fc1n)"])

pyplot.plot(ode_data["time"],ode_data["T_i0"])
pyplot.plot(fc_data["Time"],fc_data["I(L1)"])

pyplot.show()
