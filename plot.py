#!/usr/bin/env python
import sys
from pylab import *

NUMBER_OF_FIELDS = 11
ALPHA_POS = 2
SAMPLING_TIME = 83.0 # us

font = {'family': 'monospace',
        'color':  'black',
        'weight': 'bold',
        'size': 12,
        }

data = []
skip = 0

try:
    sel = sys.argv[1]
except IndexError:
    print 'Error! You must enter a parameter ./plot [1-2]'
    sys.exit()


if (sel == '1'):
    print 'Ramp samples read\n'
    lines1 = [line.rstrip('\n') for line in open('ramp_samples.txt')]
    num_lines = sum(1 for line in open('ramp_samples.txt'))
    print 'Filtered ramp read\n'
    lines2 = [line.rstrip('\n') for line in open('filtered_ramp.txt')]
    fig = gcf()
    fig.canvas.set_window_title('Filter test - simulated indata')

if (sel == '2'):
    print 'Real filtered samples read\n'
    lines1 = [line.rstrip('\n') for line in open('filtered_realdata.txt')]
    num_lines = sum(1 for line in open('filtered_realdata.txt'))
    fig = gcf()
    fig.canvas.set_window_title('Filter test - real indata')
    skip = 1


try:
    t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)
except NameError:
    print 'Error! Incorrect choise, only between 1-6'
    sys.exit()


# calculate total time and convert to ms
totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0

# just make a copy of the list except the header info
data = lines1[11:num_lines]
if (skip != 1):
    data2 = lines2[11:num_lines]

# find max y value, used to place text
ypos = 1.5 * float(max(data))


#plot(t, data, marker='o', linestyle='-.', color='b')
plot(t, data)
if (skip != 1):
    plot(t, data2)


# get input type string
inputType = lines1[1]
alpha = lines1[7]
riseTime = lines1[8]
delayTime = lines1[9]

plt.text(0.5*num_lines, ypos, inputType, fontdict=font)
plt.text(0.5*num_lines, ypos-2, alpha, fontdict=font)
plt.text(0.5*num_lines, ypos-4, riseTime, fontdict=font)
plt.text(0.5*num_lines, ypos-6, delayTime, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

