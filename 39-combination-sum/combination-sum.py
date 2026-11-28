from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        results: List[List[int]] = []
        path: List[int] = []

        def backtrack(start: int, remaining: int) -> None:
            if remaining == 0:
                results.append(path[:])
                return

            for i in range(start, len(candidates)):
                num = candidates[i]
                if num > remaining:
                    break 

                path.append(num)
                backtrack(i, remaining - num)
                path.pop()

        backtrack(0, target)
        return results