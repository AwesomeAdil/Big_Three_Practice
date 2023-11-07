n, q = list(map(int, input().split()))
amts = list(map(int, input().split()))
fruits = list(map(int, input().split()))
grundys = []

def search(f, a):
    if (f%(a+1))%2 == 0:
        if f%(a+1) == a:
            return 2
        else:
            return 0
    else:
        return 1

for g in zip(fruits, amts):
    grundys.append(search(g[0], g[1]))


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
