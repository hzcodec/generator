#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from common import *

SAMPLE_TIME = 83.0    # sample time in us
MAX_LEVEL = 40.0      # max level when trigger is reached
EXPAND_WINDOW = 1.1   # expand matplot window
X_POS = 0.2           # x-position of alpha print out
Y_POS = 0.6           # y-position of alpha print out

t = []
t = range(512)

# read in data file
def read_indata(fileName):
    print fileName + ' read as input data'
    l = [line.rstrip('\n') for line in open(fileName)]

    # convert to float
    result = map(float, l)

    # number of lines
    n = sum(1 for line in open(fileName))

    print 'Max input value: ', max(result)
    print 'Min input value: ', min(result)

    return result, n

def read_filtered_indata(fileName):
    print fileName + ' read filtered as input data'
    l = [line.rstrip('\n') for line in open(fileName)]

    # convert to float
    result = map(float, l[11:])

    no = 0
    # check when level is above MAX_LEVEL
    for i in range(0, 512):
        if (result[i] > MAX_LEVEL):
	    no += 1
            print i, result[i]

    t_time = float(no)*SAMPLE_TIME / 1000.0  # in [ms]
    print "Trigger time %.2f ms" % t_time

    print 'Max output value: ', max(result)
    print 'Min ouput value: ', min(result)

    # number of lines
    n = sum(1 for line in open(fileName))

    # get alpha value
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
