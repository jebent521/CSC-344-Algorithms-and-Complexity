'''
Jonah Ebent, 12/4/24, CSC 344 Algorithms and Complexity
Implementation and testing of Kruskal's and Prim's algorithms

Inputs to visualize graph with https://csacademy.com/app/graph_editor/ 
Graph G
0 1 4
0 2 1
0 3 3
1 2 4
1 3 4
2 3 2
2 5 4
3 5 6
4 5 5

Graph from homework problem (H)
0 1 4
0 3 4
0 6 6
1 2 1
1 3 2
1 4 4
2 4 2
2 5 4
3 6 6
3 7 5
3 4 6
4 5 5
4 7 2
4 8 6
5 8 3
6 9 4
6 7 5
7 9 5
7 10 4
7 8 2
8 10 2
8 11 1
10 11 1
9 10 3
'''

import heapq
import timeit

class Graph:
    def __init__(self, size: int, edges: list[tuple[int, int, int]]):
        self.size = size
        self.edges = edges
        self.matrix = [[None] * size for _ in range(size)]
        for u, v, w in edges:
            self.matrix[u][v] = w
            self.matrix[v][u] = w

    def adjacent_edges(self, v: int, for_heap=False):
        '''returns a list of the edges `v` is connected to'''
        if for_heap:
            return [(self.matrix[v][u], v, u) for u in range(self.size) if self.matrix[v][u] != None] 
        return [(v, u, self.matrix[v][u]) for u in range(self.size) if self.matrix[v][u] != None] 

    def kruskal(self):
        # equivalent to makeset(u) for u in V
        parent = [i for i in range(self.size)]
        rank = [0] * self.size

        def find(x):
            '''finds the root of the set x is in'''
            if x != parent[x]:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            '''combines the two trees x and y are part of'''
            rx = find(x)
            ry = find(y)
            if rx == ry: return
            if rank[ry] > rank[rx]:
                parent[rx] = ry
            else:
                parent[ry] = rx
                if rank[rx] == rank[ry]:
                    rank[rx] += 1

        mst = []
        self.edges.sort(key=lambda x: x[2])
        for u,v,w in self.edges:
            if find(u) != find(v):
                mst.append((u, v, w))
                union(u, v)
        return mst

    def prim(self):
        visited = [0]
        mst = []
        edges = self.adjacent_edges(0, True)
        heapq.heapify(edges)
        for _ in range(self.size-1):
            w, u, v = heapq.heappop(edges)
            while (u in visited) == (v in visited):
                w, u, v = heapq.heappop(edges)
            if v in visited: v, u = u, v
            mst.append((u, v, w))
            visited.append(v)
            for e in self.adjacent_edges(v, True):
                heapq.heappush(edges, e)
        return mst
    
    def total_weight(self, edges=None):
        if edges == None: edges = self.edges
        return sum(e[2] for e in edges)

g_edges = [(0, 1, 4),
         (0, 2, 1),
         (0, 3, 3),
         (1, 2, 4),
         (1, 3, 4),
         (2, 3, 2),
         (2, 5, 4),
         (3, 5, 6),
         (4, 5, 5)]

h_edges = [(0, 1, 4),
           (0, 3, 4),
           (0, 6, 6),
           (1, 2, 1),
           (1, 3, 2),
           (1, 4, 4),
           (2, 4, 2),
           (2, 5, 4),
           (3, 6, 6),
           (3, 7, 5),
           (3, 4, 6),
           (4, 5, 5),
           (4, 7, 2),
           (4, 8, 6),
           (5, 8, 3),
           (6, 9, 4),
           (6, 7, 5),
           (7, 9, 5),
           (7, 10, 4),
           (7, 8, 2),
           (8, 10, 2),
           (8, 11, 1),
           (10, 11, 1),
           (9, 10, 3)]

g = Graph(6, g_edges)
h = Graph(12, h_edges)

print('MST of graph G')
print("Output of Kruskal's algorithm (copy and paste into the online graph editor):")
for e in g.kruskal():
    print(*e)
print("Running Kruskal's algorithm 1000000 times takes", timeit.timeit("g.kruskal()", 'from __main__ import g'), 'seconds.')
print("Output of Prim's algorithm (copy and paste into the online graph editor):")
for e in g.prim():
    print(*e)
print("Running Prim's algorithm 1000000 times takes", timeit.timeit("g.prim()", 'from __main__ import g'), 'seconds.')
print()
print('MST of graph H')
print("Output of Kruskal's algorithm (copy and paste into the online graph editor):")
for e in h.kruskal():
    print(*e)
print("Output of Prim's algorithm (copy and paste into the online graph editor):")
for e in h.prim():
    print(*e)
