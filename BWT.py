# -*- coding: utf-8 -*-
"""
Created on Tue Oct 22 14:48:15 2019

@author: 陈焯阳
"""

def rotations(t):
    tt = t * 2
    return [tt[i:i+len(t)] for i in range(0,len(t))]

def bwm(t):
    return sorted(rotations(t))

def bwtViaBwm(t):
    return ''.join(map(lambda x: x[-1], bwm(t)))

def rankBwt(bw):
    tots = dict()
    ranks = []
    for c in bw:
        if c not in tots:
            tots[c] = 0
        ranks.append(tots[c])
        tots[c] += 1
    return ranks, tots

def firstCol(tots):
    first = {}
    totc = 0
    for c, count in sorted(tots.items()):
        first[c] = (totc, totc + count)
        totc += count
    return first

def reverseBwt(bw):
    ranks, tots = rankBwt(bw)
    first = firstCol(tots)
    rowi = 0
    t = '$'
    while bw[rowi] != '$':
        c = bw[rowi]
        t = c + t
        rowi = first[c][0] + ranks[rowi]
    return t

t = 'abaaba$'
b = bwtViaBwm(t)
ranks, tots = rankBwt(b)
first = firstCol(tots)
reverseBwt(b)

