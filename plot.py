#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from common import *

class bcolors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


SAMPLE_TIME = 83.0    # sample time in us
MAX_LEVEL = 20.0      # max level when trigger is reached
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

    print bcolors.GREEN + '  Max input value: ', str(max(result)) + bcolors.ENDC
    print bcolors.GREEN + '  Min input value: ', str(min(result)) + bcolors.ENDC

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
    print "  Trigger level is exceeded [%.2f A], time %.2f ms" % (MAX_LEVEL, t_time)

    print bcolors.GREEN + '  Max output value: ', str(max(result)) + bcolors.ENDC
    print bcolors.GREEN + '  Min ouput value: ', str(min(result)) + bcolors.ENDC

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
