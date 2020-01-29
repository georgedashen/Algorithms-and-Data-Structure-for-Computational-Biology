# -*- coding: utf-8 -*-
"""
Created on Mon Oct 21 12:54:48 2019

@author: 陈焯阳
"""
import numpy as np
maxsize = 10000

def global_align(s, t):
    m = len(s) + 1
    n = len(t) + 1
    if m-1 > maxsize or n-1 > maxsize:
        print("String is longer than max size!")
        return None
    
    gap = -2
    max_score = 0
    A = np.zeros((m,n), dtype = int)
    
    for i in range(1, m):
        for j in range(1, n):
            match = 0
            if s[i-1] == t[j-1]:
                match = 1
            else:
                match = -2
            A[i][j] = max(A[i-1][j-1]+match, A[i-1][j]+gap, A[i][j-1]+gap)
                
    max_score = A[m-1][n-1]
    
    return max_score, A

def local_align(s, t):
    m = len(s) + 1
    n = len(t) + 1
    if m-1 > maxsize or n-1 > maxsize:
        print("String is longer than max size!")
        return None
    
    gap = -2
    max_score = 0
    A = np.zeros((m,n), dtype = int)
    
    for i in range(1, m):
        for j in range(1, n):
            match = 0
            if s[i-1] == t[j-1]:
                match = 1
            else:
                match = -2
            A[i][j] = max(A[i-1][j-1]+match, A[i-1][j]+gap, A[i][j-1]+gap, 0)
            if A[i][j] > max_score:
                max_score = A[i][j]
                row_idx = i
                col_idx = j
    
    return max_score, row_idx, col_idx, A

f = open('local s.txt')
s = f.read()
f.close()
f = open('local t.txt')
t = f.read()
f.close()

max_score, row_idx, col_idx, A = local_align(s, t)
print("max score %d at A[%d][%d]" %(max_score, row_idx, col_idx))

i = row_idx
j = col_idx
m = len(s)+1
n = len(s)+1
while i < m-1 and j < n-1:
    step_max = max(A[i+1][j], A[i][j+1], A[i+1][j+1])
    if A[i+1][j+1] == step_max:
        i += 1
        j += 1
    elif A[i+1][j] == step_max:
        i += 1
    else:
        j += 1

row_end = i
col_end = j #something wrong with this, should without -1

m = row_end
n = col_end
while m and n:
    if A[m][n] == A[m-1][n]-2:
        m -= 1
    elif A[m][n] == A[m][n-1]-2:
        n -= 1
    else:
        m -= 1
        n -= 1

row_start = m
col_start = n

s_suffix = s[row_start:]
t_prefix = t[:col_end]#in python the last index is not included
max_score, A = global_align(s_suffix, t_prefix)
print("max score %d" %max_score)

s_track = []
t_track = []
m = len(s_suffix)
n = len(t_prefix)
while m and n:
    if m == 0:
        t_track.append(t_prefix[n-1])
        s_track.append("-")
        n -= 1
    elif n == 0:
        s_track.append(s_suffix[m-1])
        t_track.append("-")
        m -= 1
    elif A[m][n] == A[m-1][n]-2:
        s_track.append(s_suffix[m-1])
        t_track.append("-")
        m -= 1
    elif A[m][n] == A[m][n-1]-2:
        t_track.append(t_prefix[n-1])
        s_track.append("-")
        n -= 1
    else:
        t_track.append(t_prefix[n-1])
        s_track.append(s_suffix[m-1])
        m -= 1
        n -= 1

s_track.reverse()
print(''.join(s_track))
print('\n\n')
t_track.reverse()
print(''.join(t_track))

