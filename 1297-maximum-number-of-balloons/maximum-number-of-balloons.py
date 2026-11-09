from collections import Counter

class Solution:
    def maxNumberOfBalloons(self, text):
        count = Counter(text)

        return min(
            count['b'],
            count['a'],
            count['l'] // 2,
            count['o'] // 2,
            count['n']
        )