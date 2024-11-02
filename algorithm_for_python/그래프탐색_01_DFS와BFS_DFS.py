N,M,V = map(int,input().split())

graph = {}

for i in range(1,N+1):
    graph[i] = []
    
for _ in range(M):
    a, b = map(int,input().split())
    
    graph[a].append(b)
    graph[b].append(a)
    
 
visited = [0]*(N+1)
path = []

def dfs(n):
    visited[n] = 1
    path.append(n)
    
    for node in graph[n]:
        if visited[node] == 0:
            
            dfs(node)
            
    return

dfs(V)

print(*path)