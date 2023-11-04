"""Obvious floyd warshals idea from small constraints and All paths shortest distance"""


n = int(input())
nums = list(map(int, input().split()))
adj_mat = []
for i in range(n):
    adj_mat.append([])
    for j in range(n):
        adj_mat[-1].append(1000000000000)

for i in range(n-1):
    a, b, c = map(int, input().split())
    a-=1
    b-=1
    #Bi-directional
    adj_mat[a][b] = c
    adj_mat[b][a] = c

#Diagonal (self)
for i in range(n):
    adj_mat[i][i] = 0

for k in range(n):
    for i in range(n):
        for j in range(n):
            if i != j:
                adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k]+adj_mat[k][j])

#Convert to scores
for i in range(n):
    for j in range(n):
        adj_mat[i][j] = nums[j]/(adj_mat[i][j]+1)

best_spot = -1
best_score = -1
#Find best score
for i in range(n):
    score = 0
    for j in range(n):
        score += adj_mat[i][j]
    if score > best_score:
        best_spot = i+1
        best_score = score

print(best_spot)
print(best_score)
