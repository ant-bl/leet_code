from typing import List


# Given n non-negative integers representing an elevation map where the width of each bar is 1,
# compute how much water it can trap after raining.

class Solution:
    def trap(self, height: List[int]) -> int:

        if len(height) <= 1:
            return 0

        left = 0
        count = 0

        # find a left idx with an height > 0
        while height[left] == 0:
            left += 1
            if left == len(height):
                return 0

        right = left + 1

        while True:

            right_tmp = right

            # looking for the right idx
            while True:
                # find an height higher or equal than left
                if height[right_tmp] >= height[left]:
                    right = right_tmp
                    break

                # Update the right with the highest height currently found
                if height[right_tmp] > height[right]:
                    right = right_tmp

                # out of bound
                if right_tmp + 1 == len(height):
                    break
                right_tmp += 1

            # print(f"LEFT: {left} => {height[left]}")
            # print(f"RIGHT: {right} => {height[right]}")

            max_height = min(height[left], height[right])

            left = left + 1

            while left < right:
                diff = max_height - height[left]
                # print("diff")
                # print(diff)
                if diff > 0:
                    count += diff
                # print(f"COUNT {count}")

                left += 1

            assert left == right

            right += 1
            if right >= len(height):
                break

        return count


def test():
    res = Solution().trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1])
    assert res == 6

    res = Solution().trap([4, 2, 0, 3, 2, 5])
    assert res == 9


if __name__ == "__main__":
    test()
