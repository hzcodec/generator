#!/usr/bin/env python
import sys
import matplotlib.pyplot as plt
from common import *

data = []
skip = 0
t = []

# read in data file
def read_indata(fileName):
    print fileName + ' read as input data'
    l = [line.rstrip('\n') for line in open(fileName)]
    n = sum(1 for line in open(fileName))
    return l, n


###################################################################
data1, numberOfLines1 = read_indata('realdata.txt')
data2, numberOfLines2 = read_indata('filtered_realdata.txt')

t = range(256)

# make space for the curve
plt.ylim(float(min(data1))*1.5, float(max(data1))*1.5)
print max(data1)
print max(t)

# set window title
plt.gcf().canvas.set_window_title('Filter test')

alpha = 0.001
#plt.text(0.2*numberOfLines1, plt.ypos+4, alpha, fontdict=font)
plt.text(max(t)*0.8, max(data1), 'alpha: '+str(alpha), font)

plt.plot(t, data1, color="blue", linewidth=1, label='realdata')
plt.plot(t, data2[11:], color="red", linewidth=1, label='filtered_realdata')

#legends
plt.legend(loc='upper right', frameon=False)

plt.grid(True)
plt.show()

#try:
#    sel = sys.argv[1]
#except IndexError:
#    print 'Error! You must enter a parameter ./plot [1-2]'
#    sys.exit()


#if (sel == '1'):
#    print 'Ramp samples read\n'
#    lines1 = [line.rstrip('\n') for line in open('ramp_samples.txt')]
#    num_lines = sum(1 for line in open('ramp_samples.txt'))
#    print 'Filtered ramp read\n'
#    lines2 = [line.rstrip('\n') for line in open('filtered_ramp.txt')]
#    fig = gcf()
#    fig.canvas.set_window_title('Filter test - simulated indata')
#
#if (sel == '2'):
#    print 'Real filtered samples read\n'
#    lines1 = [line.rstrip('\n') for line in open('realdata.txt')]
#    num_lines = sum(1 for line in open('realdata.txt'))
#    lines2 = [line.rstrip('\n') for line in open('filtered_realdata.txt')]
#    fig = gcf()
#    fig.canvas.set_window_title('Filter test - real indata')
#    skip=1
#
#try:
#    if (skip != 1):
#        t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)
#    else:
#        t = arange(0, num_lines, 1)
#
#except NameError:
#    print 'Error! Incorrect choise, only between 1-6'
#    sys.exit()
#
## calculate total time and convert to ms
#totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0
#
## just make a copy of the list except the header info
#if (skip != 1):
#    data = lines1[11:num_lines]
#    data2 = lines2[11:num_lines]
#    alpha = lines1[7]
#else:
#    data = lines1[:]
#    data2 = lines2[1:num_lines+1]
#    alpha = lines2[0]
#
#
## find max y value, used to place text
#ypos = 1.5 * float(max(data))
#
#
##plot(t, data, marker='o', linestyle='-.', color='b')
#plot(t, data)
#plot(t, data2)
#
### get input type string
#inputType = lines1[1]
#riseTime = lines1[8]
#delayTime = lines1[9]
#
#if (skip != 1):
#    plt.text(0.5*num_lines, ypos, inputType, fontdict=font)
#    plt.text(0.5*num_lines, ypos-2, alpha, fontdict=font)
#    plt.text(0.5*num_lines, ypos-4, riseTime, fontdict=font)
#    plt.text(0.5*num_lines, ypos-6, delayTime, fontdict=font)
#else:
#    plt.text(0.2*num_lines, ypos+4, alpha, fontdict=font)
#
#
#xlabel('samples')
#ylabel('i')
#
#title(str(lines1[ALPHA_POS])+',  Total time:'+str(totTime)+' ms')
#
#grid(True)
#show()
#
