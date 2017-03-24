#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from common import *

t = []
t = range(256)

# read in data file
def read_indata(fileName):
    print fileName + ' read as input data'
    l = [line.rstrip('\n') for line in open(fileName)]
    n = sum(1 for line in open(fileName))
    return l, n


###################################################################
print 20*'-'
data1, numberOfLines1 = read_indata('realdata.txt')
data2, numberOfLines2 = read_indata('filtered_realdata.txt')


# make space for the curve
plt.ylim(float(min(data1))*1.5, float(max(data1))*1.5)

# set window title
plt.gcf().canvas.set_window_title('Filter test')

alpha = 0.001
plt.text(max(t)*0.8, max(data1), 'alpha: '+str(alpha), font)

plt.plot(t, data1, color="blue", linewidth=1, label='realdata')
plt.plot(t, data2[11:], color="red", linewidth=1, label='filtered_realdata')

#legends
plt.legend(loc='upper right', frameon=False)

plt.xlabel('sample number')

plt.grid(True)
plt.show()

