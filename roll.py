#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function
import random
import sys

#   .    /'\          .__.    __     .
#  / \  /___\  ./\.  /\__/\  /__\  .´ `.
# / 4 \ \ 8 / //10\\ \/12\/ /\20/\ \100/
# `---´  \./  ``--´´  `--´  \_\/_/  `-´

dmap = {
    4:   ["   .  ", "  / \ ", " / %d \\", " `---´"],
    6:   ["      ", " .---.", " | %d |", " '---'"],
    8:   ["  /'\ ", " /___\\", " \ %d /", "  \./ "],
    10:  ["       ", "  ./\. ", " //%02d\\\\", " ``--´´"],
    12:  ["  .__. ", " /\__/\\", " \/%02d\/", "  `--´ "],
    20:  ["   __  ", "  /__\ ", " /\\%02d/\\", " \_\/_/"],
    100: ["   .  ", " .´ `.", " \\%03d/", "  `-´ "],
    }

def parseroll(arg):
    n = arg.find('d')
    if n == -1:
        raise ValueError('Bad argument: %s' % arg)
    cnt = int(arg[:n])
    die = int(arg[n+1:])
    return cnt, die

def processroll(cnt, die):
    res = []
    for i in range(cnt):
        roll = random.randint(1, die)
        res.append((roll, die))
    return res

def printdice(dice):
    for ln in range(4):
        for r, d in dice:
            l = dmap[d]
            s = l[ln] if ln != 2 else l[ln] % r
            print(s, end='')
        print() # print new line

def main():
    if len(sys.argv) < 2:
        raise ValueError('No dice')

    sum = 0
    mods = 0
    dice = []
    for i in range(1, len(sys.argv)):
        arg = sys.argv[i];
        if arg[0] == '-' or arg[0] == '+':
            mods += int(arg);
        else:
            cnt, die = parseroll(arg)
            dice += processroll(cnt, die)
    printdice(dice)

    print('\nTotal modifiers: %d' % mods)
    sum += mods

    for roll, die in dice:
        sum += roll
    print('\n%d' % sum)

if __name__ == '__main__':
    try:
        main()
    except ValueError as e:
        print(str(e), file=sys.stderr)
        sys.exit(-1)
