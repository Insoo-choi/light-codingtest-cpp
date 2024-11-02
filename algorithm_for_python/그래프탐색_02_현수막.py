import sys
sys.setrecursionlimit(100000)

M, N = map(int, input().split())

graph = []
visited = [[0]*N for _ in range(M)]

for i in range(M):
    graph.append(list(map(int,input().split())))
    
    
dx = [-1,-1,0,1,1,1,0,-1]
dy = [0,1,1,1,0,-1,-1,-1]
    
def dfs(x,y,words):
    visited[x][y] = words
    
    for i in range(8):
        nx, ny = x + dx[i], y + dy[i]
        
        if nx < 0 or nx >= M or ny < 0 or ny >= N:
            continue
        
        if graph[nx][ny] == 1 and visited[nx][ny] == 0:
            dfs(nx,ny,words)
            

words = 0    
for x in range(M):
    for y in range(N):
        if graph[x][y] == 1 and visited[x][y] == 0:
            words += 1
            dfs(x,y,words)
            
print(words)