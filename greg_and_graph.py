n = int(input())
adjmat = [list(map(int, input().split())) for i in range(n)]
order = list(map(int, input().split()))
order.reverse()
ans = []
allowed = [False]*n
for k in order:
    allowed[k-1] = True
    part = 0
    for i in range(n):
        for j in range(n):
            x = i+1
            y = j+1
            adjmat[i][j] = min(adjmat[i][j], adjmat[i][k-1]+adjmat[k-1][j])
            if x!=y and (allowed[i] and allowed[j]):
                part += adjmat[i][j]
    ans.append(part)
ans.reverse()
print(' '.join(list(map(str, ans))))
