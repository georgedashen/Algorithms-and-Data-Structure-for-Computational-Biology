# -*- coding: utf-8 -*-
"""
Created on Sat Oct 26 15:56:29 2019

@author: Zhuoyang Chen
"""
## to transform fastq to pure fasta format of reads
def readFastq(filename):
    reads = []
    with open(filename) as f:
        while True:
            f.readline()
            seq = f.readline().rstrip()
            f.readline()
            f.readline()
            
            if len(seq) > 0:
                reads.append(seq)
            else:
                break
    return reads
## to get the complement strand sequence of a read
def reverseComplement(s):
    complement = {'A':'T', 'C':'G', 'T':'A', 'G':'C'}
    c = ''
    for i in s:
        c = complement[i] + c
    return c
## get a set of kmers and count their numbers
def kmers(reads, k):
    k -= 1 # k-1 mer
    nodes = {}
    for read in reads:
        for seq in read.split('N'): #get rid of character N
            if len(seq) > 0: #which N appears at the beginning or end of seq
                for i in range(len(seq)-k+1): #add k-1mer and its complement
                    kmer = seq[i:i+k]
                    rev_kmer = reverseComplement(seq)[i:i+k]
                    if kmer not in nodes:
                        nodes[kmer] = 1
                    else:
                        nodes[kmer] = nodes[kmer] + 1
                    if rev_kmer not in nodes:
                        nodes[rev_kmer] = 1
                    else:
                        nodes[rev_kmer] = nodes[rev_kmer] + 1

    return nodes
## to get the potential next k-1mer
def forward(string):
    symbols = 'ATCG'
    for c in symbols:
        yield string[1:] + c
## to get the potential previous k-1mer        
def backward(string):
    symbols = 'ATCG'
    for c in symbols:
        yield c + string[:-1]
## find the longest contig a k-1mer belongs to
def find_fw(nodes, kmer):
    contig = [kmer] #initiate with the first kmer
    # the idea here is only when the current edge's outdegree and the next edge's
    # indegree both equals to one can this two kmers be combined to a contig
    while True:
        hit_fw = 0
        for x in forward(contig[-1]): #interation begins at newly added kmer
            if x in nodes:
                hit_fw += 1 #counts hit
        if hit_fw != 1: #give up when the outdegree of current edge not equals 1
            break
        
        for x in forward(contig[-1]):# get the next edge
            if x in nodes: #have to exist in nodes
                next_kmer = x
                break
            
        if next_kmer in contig: #have been counted, rule out repeat
            break
        
        hit_bw = 0
        for y in backward(next_kmer):
            if y in nodes:
                hit_bw += 1
        if hit_bw != 1: #give up when the indegree of next edge not equals 1
            break
        
        contig.append(next_kmer) # add new kmers sequentially to get a set of kmers

    return contig
# assemble the set of kmers                
def assembleContig(nodes, kmer):
    contig_fw = find_fw(nodes, kmer) #find the set of kmers that after the current kmer
    contig_bw = find_fw(nodes, reverseComplement(kmer)) #find the set of kmers that before the current kmer
    
    if kmer in forward(contig_fw[-1]): #forming loop
        contigs = contig_fw
    else:
        contigs = contig_fw
        contig_bw = contig_bw[1:] # the first kmer in contig_bw is the same one in contig_fw
        for contig in contig_bw:
            contigs = [reverseComplement(contig)] + contigs
    
    string = contigs[0] + ''.join(x[-1] for x in contigs[1:]) #assemble kmers into contig by adding the last base of kmers
    
    return string, contigs

def DeBruijn(nodes):
    condensed = set() #record kmers that have been used
    edges = [] #record assembled contigs
    
    for kmer in nodes: #go through all the kmers
        if kmer not in condensed: #not be used yet
            string, contigs = assembleContig(nodes, kmer)
            for contig in contigs:
                condensed.add(contig)
                condensed.add(reverseComplement(contig))
            edges.append(string)
    ## after getting all the contigs, generate their complement seqs and store them
    size = len(edges)
    for i in range(size):
        rev_edge = reverseComplement(edges[i])
        if rev_edge not in edges:
            edges.append(rev_edge)
    
    return edges
## format edges information
def displace_dbg(edges):
    for i,x in enumerate(edges):
        print(">edge%d\tlength: %d\tcoverage: %f\n%s" %(i, len(x), avg_k_cvrg[i], x))
## compute the average kmer coverage of edges
def average_kmer_coverage(edges, nodes, k):
    avg_k_cvrg = []
    k -= 1
    
    for edge in edges:
        kmer_coverage = 0
        for i in range(len(edge)-k+1):
            kmer = edge[i:i+k]
            kmer_coverage += nodes[kmer]
        
        avg_k_cvrg.append(kmer_coverage/(len(edge)-k+1))
    
    return avg_k_cvrg

# Begin
reads = readFastq('s_6.first1000.fastq')
#reads information, count number of reads and notes, and get a ratio of nodes/reads
'''
length={}
for read in reads:
    if len(read) not in length:
        length[len(read)] = 1
    else:
        length[len(read)] = length[len(read)] + 1

valid = 0
for l in length:
    if l >= 54:
        valid += length[l]
ratio = valid / len(reads)
'''
nodes = kmers(reads, 55)
edges = DeBruijn(nodes)
avg_k_cvrg = average_kmer_coverage(edges, nodes, 55)

## output edges information into fasta file
import sys
orig_stdout = sys.stdout
f = open('edges.fasta','w')
sys.stdout = f
displace_dbg(edges)
sys.stdout = orig_stdout
f.close()

## get number of overalp between two kmers
def overlap(a, b, min_length=20):
    start = 0
    
    while True:
        start = a.find(b[:min_length], start)
        if start == -1:
            return 0
        if b.startswith(a[start:]):
            return len(a)-start
        start += 1
## generate and format the .dot file
def diagrahG(edges, k, avg_k_cvrg):
    print("digragh dbg {\n")
    for i in range(len(edges)):
        for j in range(i,len(edges)):
            if i == j:
                if overlap(edges[i], edges[j]) != len(edges[i]) and overlap(edges[i], edges[j]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(i, j, len(edges[i]), avg_k_cvrg[i]))
            else:
                if overlap(edges[i], edges[j]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(i, j, len(edges[i]), avg_k_cvrg[i]))
                if overlap(edges[j], edges[i]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(j, i, len(edges[j]), avg_k_cvrg[j]))
    print("\n}")

## output .dot file
orig_stdout = sys.stdout
f = open('edges.dot','w')
sys.stdout = f
diagrahG(edges, 55, avg_k_cvrg)
sys.stdout = orig_stdout
f.close()

## Algorithm1 to simply the graph by removing short and low coverage edges at tip
def GetLinkDegree(edges, k, avg_k_cvrg1):
    degree = {}
    link = {}
    sides = []
    for i in range(len(edges)):
        link[i] = []
    for i in range(len(edges)):
        for j in range(i,len(edges)):
            if i == j:
                if overlap(edges[i], edges[j]) != len(edges[i]) and overlap(edges[i], edges[j]) > 0:
                    if i not in degree:
                        degree[i] = (1, 0)
                    else:
                        degree[i] = (degree[i][0] + 1, degree[i][1])
                    if j not in degree:
                        degree[j] = (0, 1)
                    else:
                        degree[j] = (degree[i][0], degree[j][1]+1)
                    link[i].append(j)
                    sides.append((i,j))
            else:
                if overlap(edges[i], edges[j]) > 0:
                    if i not in degree:
                        degree[i] = (1, 0)
                    else:
                        degree[i] = (degree[i][0] + 1, degree[i][1])
                    if j not in degree:
                        degree[j] = (0, 1)
                    else:
                        degree[j] = (degree[i][0], degree[j][1]+1)
                    link[i].append(j)
                    sides.append((i,j))
                if overlap(edges[j], edges[i]) > 0:
                    if i not in degree:
                        degree[i] = (0, 1)
                    else:
                        degree[i] = (degree[i][0], degree[i][1]+1)
                    if j not in degree:
                        degree[j] = (1, 0)
                    else:
                        degree[j] = (degree[j][0] + 1, degree[j][1])
                    link[j].append(i)
                    sides.append((j,i))
    return degree, link, sides

def constructDP(node,link,dp):
    if len(link[node])!=0:
        for i in link[node]:
            dp[i] = max(dp[i],dp[node]+1)
            constructDP(i,link,dp)

def findpos(dp,idx):
    pos = []
    for i in range(len(dp)):
        if dp[i] == idx:
            pos.append(i)
    return pos

def path(dp,sides):
    m = max(dp)
    paths = [findpos(dp,m)][0]
    m -= 1
    while len(findpos(dp,m))>0:
        for i in findpos(dp,m):
            if (i,paths[-1]) in sides:
                paths.append(i)
        m -= 1
    return paths

def GraphSimplify1(edges, k, avg_k_cvrg1):
    D, L, sides = GetLinkDegree(edges, 55, avg_k_cvrg1)
    dp1 = [0]*len(edges)
    dp2 = [0]*len(edges)
    constructDP(0,L,dp1)
    constructDP(3,L,dp2)
    p1 = path(dp1, sides)
    p2 = path(dp2, sides)
    
    print("digragh dbg {\n")
    for i in range(len(p1)):
        for j in range(i,len(p1)):
            if p1[i] == p1[j]:
                if overlap(edges[p1[i]], edges[p1[j]]) != len(edges[p1[i]]) and overlap(edges[p1[i]], edges[p1[j]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p1[i], p1[j], len(edges[p1[i]]), avg_k_cvrg1[p1[i]]))
            else:
                if overlap(edges[p1[i]], edges[p1[j]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p1[i], p1[j], len(edges[p1[i]]), avg_k_cvrg1[p1[i]]))
                if overlap(edges[p1[j]], edges[p1[i]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p1[j], p1[i], len(edges[p1[j]]), avg_k_cvrg1[p1[j]]))
    for i in range(len(p2)):
        for j in range(i,len(p2)):
            if p2[i] == p2[j]:
                if overlap(edges[p2[i]], edges[p2[j]]) != len(edges[p2[i]]) and overlap(edges[p2[i]], edges[p2[j]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p2[i], p2[j], len(edges[p2[i]]), avg_k_cvrg1[p2[i]]))
            else:
                if overlap(edges[p2[i]], edges[p2[j]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p2[i], p2[j], len(edges[p2[i]]), avg_k_cvrg1[p2[i]]))
                if overlap(edges[p2[j]], edges[p2[i]]) > 0:
                    print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(p2[j], p2[i], len(edges[p2[j]]), avg_k_cvrg1[p2[j]]))
    print("\n}")

GraphSimplify1(edges, 55, avg_k_cvrg)

## Algorithm2 to simply the graph by removing short and low coverage edges beforehand
def GraphSimplify2(edges, k, avg_k_cvrg2):
    for i, edge in enumerate(edges):
        if len(edge) < 100 and avg_k_cvrg2[i] < 30:
            avg_k_cvrg2[i] = 0
            
    print("digragh dbg {\n")
    for i in range(len(edges)):
        for j in range(i,len(edges)):
            if avg_k_cvrg2[i] > 0 and avg_k_cvrg2[j] > 0:
                if i == j:
                    if overlap(edges[i], edges[j]) != len(edges[i]) and overlap(edges[i], edges[j]) > 0:
                        print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(i, j, len(edges[i]), avg_k_cvrg2[i]))
                else:
                    if overlap(edges[i], edges[j]) > 0:
                        print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(i, j, len(edges[i]), avg_k_cvrg2[i]))
                    if overlap(edges[j], edges[i]) > 0:
                        print('\t%d -> %d [label="L:%d \\nA_cvg:%f"]' %(j, i, len(edges[j]), avg_k_cvrg2[j]))
    print("\n}")

GraphSimplify2(edges, 55, avg_k_cvrg)
