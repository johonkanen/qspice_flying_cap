from PyQSPICE import clsQSPICE as pqs

import pandas as pd

fname = "fc_4level"

run = pqs(fname)

run.InitPlot()

run.qsch2cir()
run.cir2qraw()
run.setNline(49999)  # add enough plot points

df = run.LoadQRAW(["V(vout)", "V(fc2p,fc2n)", "V(fc1p,fc1n)", "I(L1)", "V(vdc)"])
df.to_csv("fc_4level_data.csv", index=False)
