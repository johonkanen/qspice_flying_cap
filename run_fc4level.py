from PyQSPICE import clsQSPICE as pqs

import re
import math
import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt

fname = "fc_4level"

run = pqs(fname)

run.InitPlot()

run.qsch2cir()
run.cir2qraw()

df = run.LoadQRAW(["V(vout)", "V(fc2p,fc2n)", "V(fc1p,fc1n)", "I(L1)", "V(vdc)"])
df.to_csv("fc_4level_data.csv", index=False)
