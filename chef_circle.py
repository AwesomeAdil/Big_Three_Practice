n = int(input())

tastebuds = list(map(int, input().split()))
tastebuds_sum = sum(tastebuds)

cur_taste_sum = 0

# Initial Tastebud sum
for index, num in enumerate(tastebuds):
    cur_taste_sum += (index+1) * num

# Final Answer Initially
max_tastebuds = cur_taste_sum

# Want to rotate this via sliding window
# Idea: Subtract n * tastebud for certain chef and add by window to rotate
for chef in range(n-1, 0,-1):
    cur_taste_sum -= tastebuds[chef]*n
    cur_taste_sum += tastebuds_sum
    max_tastebuds = max(max_tastebuds, cur_taste_sum)

print(max_tastebuds)
