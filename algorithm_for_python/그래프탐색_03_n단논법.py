N = int(input())

graph = {}

for i in range(26):
    graph[i] = []

for _ in range(N):
    p, _, n = input().split()
    
    p = ord(p) - ord('a')
    n = ord(n) - ord('a')
    
    graph[p].append(n)
    
def dfs(s, e):    
    visited[s] = 1
    if s == e:
        return True
    
    for node in graph[s]:
        if visited[node] == 0:
            if dfs(node,e) == True:
                return True
    
    return False
    
M = int(input())

for _ in range(M):
    start, _, end = input().split()
    
    start = ord(start) - ord('a')
    end = ord(end) - ord('a')
    
    visited = [0]*26
    if dfs(start,end) == True:
        print("T")
    else:
        print("F")