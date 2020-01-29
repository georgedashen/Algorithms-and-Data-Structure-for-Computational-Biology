# -*- coding: utf-8 -*-
"""
Created on Sun Oct 20 20:44:28 2019

@author: 陈焯阳
"""

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
    
class LinkedList:
    def __init__(self):
        self.head = None
    
    def append(self, data):
        new_node = Node(data)
        
        if self.head is None:
            self.head = new_node
            return
        
        last_node = self.head
        while last_node.next:
            last_node = last_node.next
        last_node.next = new_node
    
    def prepend(self, data):
        new_node = Node(data)
        
        new_node.next = self.head
        self.head = new_node
    
    def print_list(self):
        cur_node = self.head
        while cur_node:
            print(cur_node.data)
            cur_node = cur_node.next
        print('\n')
    
    def insesrt_after_node(self, prev_node, data):
        if not prev_node:
            print("Previous node is not in the list")
            return
        
        new_node = Node(data)
        
        new_node.next = prev_node.next
        prev_node.next = new_node
    
    def delete_node(self, key):
        cur_node = self.head
        #case 1: The node to be deleted is the head, no prev_node exist
        if cur_node and cur_node.data == key:
            self.head = cur_node.next
            cur_node = None
            return
        
        prev_node = None
        while cur_node and cur_node.data != key:
            prev_node = cur_node
            cur_node = cur_node.next
        
        if cur_node is None:
            return
        
        prev_node.next = cur_node.next
        cur_node = None
    
    def delete_node_at_pos(self, pos):
        cur_node = self.head
        
        if pos == 0:
            self.head = cur_node.next
            cur_node = None
            return
        
        prev_node = None
        count = 1
        while cur_node and count != pos:
            prev_node = cur_node
            cur_node = cur_node.next
            count += 1
        
        if cur_node is None:
            return
        
        prev_node.next = cur_node.next
        cur_node = None
    
    def len_iter(self):
        count = 0
        cur_node = self.head
        
        while cur_node:
            count += 1
            cur_node = cur_node.next
        
        return count
    
    def len_recr(self, node):
        if node is None:
            return 0
        
        return 1 + self.len_recr(node.next)

list = LinkedList()
list.append("A")
list.append("B")
list.append("C")
list.print_list()
list.insesrt_after_node(list.head.next, "E")
list.prepend("D")
list.print_list()
list.delete_node("D")
list.delete_node_at_pos(3)
list.print_list()
print(list.len_iter())
print(list.len_recr(list.head))