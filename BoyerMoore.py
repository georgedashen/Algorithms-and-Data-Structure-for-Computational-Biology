# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 16:12:19 2019

@author: 陈焯阳
"""

def BoyerMoore(p, t):
    n = len(t)
    m = len(p)
    
    i = m - 1
    j = m - 1
    cur_t = m - 1
    pos = []
    
    while cur_t < n:
        while cur_t < n and p[j] != t[i]:
            shift = 1
            while shift <= j:
                if p[j-shift] != t[i]:
                    shift += 1
                else:
                    break
            cur_t += shift
            i = cur_t
            j = m - 1
            
        if j == 0:
            pos.append(i)
            cur_t += 1
            i = cur_t
            j = m - 1
        else:
            i -= 1
            j -= 1
    
    return pos

t = 'GCTTCTGCTACCTTTTGCGCGCGCGCGAA'
p = 'CCTTTTGC'
k = 'GC'
BoyerMoore(p, t)
