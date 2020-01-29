# -*- coding: utf-8 -*-
"""
Created on Tue Dec  3 13:28:40 2019

@author: 陈焯阳
"""

import random
import queue

class Node(object):
    
    def __init__(self, name, is_sink = False):
        self.name = name
        self.is_sink = is_sink


class Edge(object):
    
    def __init__(self, start, end, capacity):
        self.start = start
        self.end = end
        self.capacity = capacity


class Graph(object):
    
    def __init__(self):
        self.nodes = {}
        self.edges = {}
    
    def add_node(self, node):
        self.nodes[node.name] = node
        self.edges[node.name] = []
        
    def add_edge(self, edge):
        self.edges[edge.start].append(edge.end)
        self.edges[edge.end].append(edge.start)
        
    def get_edges(self, node_name):
        return self.edges[node_name]
    
    def __getitem__(self, key):
        return self.nodes[key]
    
    def __str__(self):
        return "Nodes: " + str(self.nodes.keys()) + "\n" + "Edges: " + str(self.edges)


def bfs(graph, start):
    visited = set()
    q = queue.Queue()
    q.put((start, 0))
    while not q.empty():
        vertex, length = q.get()
        if vertex not in visited:
            yield (vertex, length)
            visited.add(vertex)
            for to in graph.get_edges(vertex):
                if to not in visited:
                    q.put((to, length + 1))
                          

def dfs(graph, start):
    visited, stack = set(), [start]
    while stack:
        vertex = stack.pop()
        if vertex not in visited:
            visited.add(vertex)
            stack.extend(set(graph.get_edges(vertex)) - visited)
    return visited

def dfs_path(graph, start, end):
    visited = set()
    #pred = {}
    stack = [(start, [start])]
    while stack:
        (vertex, current_path) = stack.pop()        
        if vertex not in visited:
            if vertex == end:
                yield current_path
            visited.add(vertex)
            temp = graph.get_edges(vertex)
            random.shuffle(temp)
            for next_v in temp: 
                stack.append((next_v, current_path + [next_v]))
'''
g = Graph()

g.add_node(Node("A"))
g.add_node(Node("B"))
g.add_node(Node("C"))
g.add_node(Node("D"))
g.add_node(Node("E"))

g.add_edge(Edge("A", "B", 1))
g.add_edge(Edge("B", "C", 1))
g.add_edge(Edge("C", "D", 1))
g.add_edge(Edge("D", "A", 1))

d = dfs(g,"A")
b = bfs(g, "A")
gen = dfs_path(g, "A", "C")
'''