n, q = list(map(int, input().split()))
amts = list(map(int, input().split()))
fruits = list(map(int, input().split()))
grundys = []
dp = {}

def search(f, a):
    if f == 0:
        return 0
    if (f,a) in dp:
        return dp[(f,a)]
    excludents = set()
    change = a
    best = search(f-1,a)
    excludents.add(best)
    while f >= a and a!=1:
        amt = search(f-a,change)
        best = max(best, amt)
        excludents.add(amt)
        a*=change
    if 0 not in excludents:
        dp[(f,change)] = 0
        return 0
    else:
        for i in range(1, best+2):
            if i not in excludents:
                dp[(f,change)] = i
                return i
    return dp[(f,change)]




for g in zip(fruits, amts):
    grundys.append(search(g[0], g[1]))
    print(grundys[-1])


### PREFIX XOR
xg = [0]
for i in grundys:
    xg.append(xg[-1]^i)


for _ in range(q):
    l,r = list(map(int, input().split()))
    if xg[r]^xg[l-1]!=0:
        print('Ivan')
    else:
        print('Isabel')
