#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from common import *

EXPAND_WINDOW = 1.1
X_POS = 0.2
Y_POS = 0.6

t = []
t = range(512)

# read in data file
def read_indata(fileName):
    print fileName + ' read as input data'
    l = [line.rstrip('\n') for line in open(fileName)]
    result = map(float, l)
    n = sum(1 for line in open(fileName))
    print 'Max input value: ', max(result)
    print 'Min input value: ', min(result)
    return result, n

def read_filtered_indata(fileName):
    print fileName + ' read filtered as input data'
    l = [line.rstrip('\n') for line in open(fileName)]
    result = map(float, l[11:])
    print 'Max output value: ', max(result)
    print 'Min ouput value: ', min(result)
    n = sum(1 for line in open(fileName))
    a = l[7]
    return result, n, a


###################################################################
def main():
    print 20*'-'
    data1, numberOfLines1 = read_indata('realdata.txt')
    data2, numberOfLines2, alpha = read_filtered_indata('filtered_realdata.txt')
    
    
    # make space for the curve
    plt.ylim(float(min(data1))*EXPAND_WINDOW, float(max(data1))*EXPAND_WINDOW)
    
    # set window title
    plt.gcf().canvas.set_window_title('Filter test')
    
    plt.text(max(t)*X_POS, max(data1)*Y_POS, str(alpha), font)
    
    plt.plot(t, data1, color="blue", linewidth=1, label='realdata')
    plt.plot(t, data2, color="red", linewidth=1, label='filtered_realdata')
    
    #legends
    plt.legend(loc='upper left', frameon=False)
    
    plt.xlabel('sample number')
    
    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
