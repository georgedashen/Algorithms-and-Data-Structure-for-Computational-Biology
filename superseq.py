# -*- coding: utf-8 -*-
"""
Created on Mon Oct 21 12:01:55 2019

@author: 陈焯阳
"""
import numpy as np

def supereq(s, t):
    m = len(s) + 1
    n = len(t) + 1
    
    A = np.zeros((m,n), dtype=np.int)
    
    for i in range(1, m):
        for j in range(1, n):
            match = 0
            if s[i-1] == t[j-1]:
                match = 1
            A[i][j] = max(A[i-1][j-1]+match, A[i-1][j], A[i][j-1])

    m -= 1
    n -= 1
    track = []
    while n or m:
        if m == 0:
            track.append(t[n-1])
            n -= 1
        elif n == 0:
            track.append(s[m-1])
            m -= 1
        elif A[m][n] == A[m-1][n]:
            track.append(s[m-1])
            m -= 1
        elif A[m][n] == A[m][n-1]:
            track.append(t[n-1])
            n -= 1
        elif A[m][n] == A[m-1][n-1] + 1:
            track.append(s[m-1])
            m -= 1
            n -= 1
        else:
            print("Error!")
    
    track.reverse()
    for i in range(len(track)):
        print(track[i], end = "")

s = "ACGTC"
t = "ATAT"
supereq(s, t)