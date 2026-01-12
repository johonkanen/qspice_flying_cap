import matplotlib.pyplot as pyplot
import pandas as pd

fc_data = pd.read_csv("./fc_4level_data.csv")
ode_data = pd.read_csv("./fc_4level_tb.dat", sep='\s+')

fig1, (axT, axB) = pyplot.subplots(2,1,sharex=True,constrained_layout=True)

ode_data.plot(ax=axT , x="time" , y="T_i0"   , label="ode current")
fc_data.plot(ax=axT  , x="Time" , y="I(L1)" , label="QSPICE current")

ode_data.plot(ax=axB , x="time" , y="B_u4"   , label="ode Udc")
fc_data.plot(ax=axB  , x="Time" , y="V(vdc)" , label="QSPICE Udc")

ode_data.plot(ax=axB , x="time" , y="B_u1"   , label="ode Vout")
fc_data.plot(ax=axB  , x="Time" , y="V(vout)" , label="QSPICE Vout")

ode_data.plot(ax=axB , x="time" , y="B_u3"   , label="ode Fc2")
fc_data.plot(ax=axB  , x="Time" , y="V(fc2p,fc2n)" , label="QSPICE Fc2")

ode_data.plot(ax=axB , x="time" , y="B_u2"   , label="ode Fc1")
fc_data.plot(ax=axB  , x="Time" , y="V(fc1p,fc1n)" , label="QSPICE Fc1")

pyplot.show()
