#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
import sys

#   .
#  / \
# / 4 \
# `---´
def printd4(d):
    print "\n  .\n / \\\n/ %d \\\n`---´\n" % d

# .---.
# | 6 |
# '---'
def printd6(d):
    print "\n.---.\n| %d |\n'---'\n" % d

#  /'\
# /___\
# \ 8 /
#  \./
def printd8(d):
    print "\n /'\\\n/___\\\n\\ %d /\n \\./\n" % d

#  ./\.
# //10\\
# ``--´´
def printd10(d):
    print "\n ./\\. \n//%02d\\\\\n``--´´\n" % d

#  .__.
# /\__/\
# \/12\/
#  `--´
def printd12(d):
    print "\n .__. \n/\\__/\\\n\\/%02d\\/\n `--´ \n" % d

#   __
#  /__\
# /\20/\
# \_\/_/
def printd20(d):
    print "\n  __  \n /__\\ \n/\\%02d/\\\n\\_\\/_/\n" % d

#   .
# .´ `.
# \100/
#  `-´
def printd100(d):
    print "\n  .\n.´ `.\n\\%03d/\n `-´\n" % d

def parsearg(arg):
    n = arg.find('d')
    cnt = int(arg[:n])
    die = int(arg[n+1:])
    return cnt, die

def processroll(cnt, die):
    if die == 4:
        printdice = printd4
    elif die == 6:
        printdice = printd6
    elif die == 8:
        printdice = printd8
    elif die == 10:
        printdice = printd10
    elif die == 12:
        printdice = printd12
    elif die == 20:
        printdice = printd20
    elif die == 100:
        printdice = printd100
    else:
        # error, not a valid dice
        return 0

    sum = 0
    for i in range(cnt):
        roll = random.randint(1, die)
        printdice(roll)
        sum += roll
    return sum

"""main"""
sum = 0
mods = 0
for i in range(1, len(sys.argv)):
    arg = sys.argv[i];
    if arg.find('d') != -1:
        cnt, die = parsearg(arg)
        sum += processroll(cnt, die)
    elif arg[0] == '-' or arg[0] == '+':
        mods += int(arg);

print "\nTotal modifiers: %d" % mods
sum += mods
        
print '\n%d' % sum
