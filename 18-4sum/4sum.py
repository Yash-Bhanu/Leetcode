from typing import List

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        n = len(nums)
        if n < 4:
            return []

        nums.sort()
        res = []
        max2 = nums[-2] + nums[-1]
        max3 = nums[-3] + max2

        for i in range(n - 3):
            a = nums[i]

            if i > 0 and a == nums[i - 1]:
                continue
            if a + nums[i + 1] + nums[i + 2] + nums[i + 3] > target:
                break
            if a + max3 < target:
                continue

            for j in range(i + 1, n - 2):
                b = nums[j]

                if j > i + 1 and b == nums[j - 1]:
                    continue
                ab = a + b

                if ab + nums[j + 1] + nums[j + 2] > target:
                    break
                if ab + max2 < target:
                    continue

                left, right = j + 1, n - 1
                rem = target - ab

                while left < right:
                    two_sum = nums[left] + nums[right]
                    if two_sum < rem:
                        left += 1
                    elif two_sum > rem:
                        right -= 1
                    else:
                        res.append([a, b, nums[left], nums[right]])
                        left += 1
                        right -= 1
                        while left < right and nums[left] == nums[left - 1]:
                            left += 1
                        while left < right and nums[right] == nums[right + 1]:
                            right -= 1

        return res