class Solution(object):
    def climbStairs(self, n, costs):
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        for j in range(1, n + 1):
            for k in range(1, 4):
                if j - k >= 0:
                    dp[j] = min(dp[j], dp[j - k] + costs[j - 1] + k * k)
        return dp[n]
        