
"""
IDEA: We know that inorder to find out how many pigs are neccessary is just the ceiling of the log
of the number of buckets, essentially using pigs to split the cases in half such that every combination of pig death
denotes a different bucket: Here is an example for 8 buckets and 3 pigs:
     
 bucket #   0 1 2 3 4 5 6 7
            . . . . . . . . 
              1   1   1   1  Denoting the ones binary digit
                2 2     2 2  Denoting the twos binary digit
                    4 4 4 4  Denoting the fours binary digit

Note how we are smartly using 1/2 the number of buckets for each pig so that each pig death (or survival) splits the graph in half.

Now if we have multiple attempts with the pigs we want to see split up the graph best so that in later attempts we have fewer buckets to check,
but if a pig dies early on we wont be able to check the same amount of buckets. Thus we need our division so that if a pig dies, we know that
the subsection that a pig was eating is coverable by the other pigs. 

Let dp[(i, j)] denote the amount of buckets that i pigs can conver with j attempts. 
- From the first idea: dp[(i,1)] = 2**i.
- Trivially we can see that: dp[(1, j)] = j+1; This is because we can check check each grass one by one (if the pig dies and we checked multiple we have no pigs left to check)
- Finally dp[(i, j)] = (i+1) * dp[(i-1, j-1)] + dp[(i, j-1)]

we know that i * dp[(i-1, j-1)] can be covered by dividing into i portions of whatever amount can be covered with i-1 pigs and if any of those pigs die we know we can
find a specific location

the spot where a single dp[(i, j-1)] can come from is where none of the pigs die

and the extra factor comes from accounting for multiple pig deaths at once.


"""




import math
class Solution:
    def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
        if buckets == 1:
            return 0
        numFit = (minutesToTest//minutesToDie)
        if numFit >= buckets:
            return 1
        dp = {}
        n = math.ceil(math.log(buckets, 2)) + 1
        min_seen = n
        for i in range(n):
            dp[(i, 1)] = 2**i
            if dp[(i,1)] >= buckets:
                min_seen = min(min_seen, i)

        for j in range(1, numFit+1):
            dp[(1,j)] = j+1
            if dp[(1,j)] >= buckets:
                return 1
        
        for j in range(2, numFit + 1):
            for i in range(2, min_seen):
                dp[(i,j)] = (i+1)*dp[(i-1, j-1)] + dp[(i, j-1)]
                if dp[(i, j)] >= buckets:
                    min_seen = min(min_seen, i)
        return min_seen
