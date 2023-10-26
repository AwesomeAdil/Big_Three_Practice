# Let dp[i] be the min number of deletions needed to make nice, start backwards with dp[n] = 0 for empty list

for _ in range(int(input())):
    n = int(input())
    nums = list(map(int, input().split()))
    dp = {}
    dp[n] = 0
    for i in range(n-1, -1, -1):
        dp[i] = dp[i+1] + 1
        if i + nums[i] < n:
            dp[i] = min(dp[i+nums[i]+1], dp[i])
    print(dp[0])
