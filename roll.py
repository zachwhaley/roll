#!/usr/bin/env python

import random
import sys

# .---.
# | 6 |
# '---'
def printsquare(d):
    print ".---.\n| %d |\n'---'" % d

#   .
#  / \
# / 4 \
# `---'
#   ..
#  /  \
# / 20 \
# `----'
def printtriangle(d):
    if d < 10:
        print "  .\n / \\\n/ %d \\\n`---'" % d
    else:
        print "  ..\n /  \\\n/ %d \\\n`----'" % d

#   .
#  / \
# / 1 \
# `, ,'
#   '
#   ..
#  /  \
# / 10 \
# `,  ,'
#   ''
def printdiamond(d):
    if d < 10:
        print "  .\n,' ',\n\\ %d /\n `,'" % d
    elif d < 100:
        print "  ..\n /  \\\n/ %d \\\n`,  ,'\n  ''" % d
    else:
        print "  .\n,' ',\n\\%d/\n `,'" % d

#   .
# ,' ',
# \ 1 /
#  `-'
#   ..
# ,'  ',
# \ 12 /
#  `--'
def printpentagon(d):
    if d < 10:
        print "  .\n,' ',\n\\ %d /\n `-'" % d
    else:
        print "  ..\n,'  ',\n\\ %d /\n `--'" % d

def parsearg(arg):
    n = arg.find('d')
    cnt = int(arg[:n])
    die = int(arg[n+1:])
    return cnt, die

def processroll(cnt, die):
    if die == 4:
        printdice = printtriangle
    elif die == 6:
        printdice = printsquare
    elif die == 8:
        printdice = printtriangle
    elif die == 10:
        printdice = printdiamond
    elif die == 12:
        printdice = printpentagon
    elif die == 20:
        printdice = printtriangle
    elif die == 100:
        printdice = printdiamond
    else:
        # error, not a valid dice
        return 0

    result = 0
    sum = 0
    for i in range(cnt):
        result = random.randint(1, die)
        printdice(result)
        sum += result
    return result

"""main"""
sum = 0
for i in range(1, len(sys.argv)):
    cnt, die = parsearg(sys.argv[i])
    sum += processroll(cnt, die)
print '\n%d' % sum
