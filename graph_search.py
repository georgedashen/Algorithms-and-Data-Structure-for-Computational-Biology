# -*- coding: utf-8 -*-
"""
Created on Thu Nov  7 08:47:37 2019

@author: 陈焯阳
"""

class Graph():
    def __init__(self,nodes,sides):
        self.sequence = {}
        self.side = []
        for node in nodes:
            for side in sides:
                u, v = side
                if node == u:
                    self.side.append(v)
            self.sequence[node] = self.side
            self.side = []
            
    def display(self):
        print(self.sequence)
    
    def DFS(self,node0):
        queue, order = [], []
        queue.append(node0)
        while queue:
            v = queue.pop()
            order.append(v)
            for w in self.sequence[v]:
                if w not in order and w not in queue:
                    queue.append(w)
                    
        return order
    
    def BFS(self,node0):
        queue, order = [], []
        queue.append(node0)
        order.append(node0)
        while queue:
            v = queue.pop()
            for w in self.sequence[v]:
                if w not in order:
                    order.append(w)
                    queue.append(w)
        return order

nodes = [i for i in range(14)]
sides = [(0,2),(3,1),(4,1),(1,9),(6,2),(2,8),(2,12),(3,4),(5,9),(9,7),(8,10),\
         (8,11),(9,13),(11,10)]
G = Graph(nodes,sides)

G.display()
print(G.DFS(0))
print(G.BFS(0))

print(G.DFS(6))
print(G.DFS(3))
        
            