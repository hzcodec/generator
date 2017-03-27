#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from common import *

SAMPLE_TIME = 83.0    # sample time in us
MAX_LEVEL = 40.0      # max level when trigger is reached
EXPAND_WINDOW = 1.1   # expand matplot window
X_POS = 0.2           # x-position of alpha print out
Y_POS = 0.6           # y-position of alpha print out
SPACE = 11

t = []

# read in data file
def read_indata(fileName):
    print "\"" + fileName + '" read as input data'
    l = [line.rstrip('\n') for line in open(fileName)]

    # convert to float
    result = map(float, l)

    # number of lines
    n = sum(1 for line in open(fileName))

    print '  Max input value: ', max(result)
    print '  Min input value: ', min(result)

    return result, n

def read_filtered_indata(fileName):
    print "\"" + fileName + '" read as input filtered data'
    l = [line.rstrip('\n') for line in open(fileName)]

    # number of lines
    n = sum(1 for line in open(fileName))

    # convert to float
    result = map(float, l[SPACE:])

    no = 0
    # check when level is above MAX_LEVEL
    for i in range(0, n-SPACE):
        if (result[i] > MAX_LEVEL):
	    no += 1

    t_time = float(no)*SAMPLE_TIME / 1000.0  # in [ms]
    print "  Trigger time %.2f ms" % t_time

    print '  Max output value: ', max(result)
    print '  Min ouput value: ', min(result)

    # get alpha value
    a = l[7]

    return result, n, a


###################################################################
def main():

    data1, numberOfLines1 = read_indata(sys.argv[1])
    data2, numberOfLines2, alpha = read_filtered_indata(sys.argv[2])
    
    t = range(numberOfLines1)
   
    # make space for the curve
    plt.ylim(float(min(data1))*EXPAND_WINDOW, float(max(data1))*EXPAND_WINDOW)
    
    # set window title
    plt.gcf().canvas.set_window_title('Filter test')
    plt.title(str(alpha))
    
    # get filname without extension
    sys.argv[1][:-4]
    sys.argv[2][:-4]

    plt.plot(t, data1, color="blue", linewidth=1, label=sys.argv[1][:-4])
    plt.plot(t, data2, color="red", linewidth=1, label=sys.argv[2][:-4])
    
    #legends
    plt.legend(loc='upper left', frameon=False)
    
    plt.xlabel('sample number')
    
    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
