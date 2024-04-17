#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
A school is trying to take an annual photo of all the students. The students are asked to stand in a
 single file line in non-decreasing order by height. Let this ordering be represented by the integer
 array expected where expected[i] is the expected height of the ith student in line.

You are given an integer array heights representing the current order that the students are standing in.
Each heights[i] is the height of the ith student in line (0-indexed).

Return the number of indices where heights[i] != expected[i].

Example 1:

Input: heights = [1,1,4,2,1,3]
Output: 3
Explanation:
heights:  [1,1,4,2,1,3]
expected: [1,1,1,2,3,4]
Indices 2, 4, and 5 do not match.

Example 2:

Input: heights = [5,1,2,3,4]
Output: 5
Explanation:
heights:  [5,1,2,3,4]
expected: [1,2,3,4,5]
All indices do not match.

Example 3:

Input: heights = [1,2,3,4,5]
Output: 0
Explanation:
heights:  [1,2,3,4,5]
expected: [1,2,3,4,5]
All indices match.

Constraints :
    1 <= heights.length <= 100
    1 <= heights[i] <= 100
*/

static int *sort(int *array, int length) {

    int middle, i, left_idx, right_idx, left_len, right_len;
    int *left, *right, *sorted;

    if (length == 1) {
        left = malloc(sizeof(int));
        assert(left != NULL);
        left[0] = array[0];
        return left;
    }

    // sort left and right buffers
    middle = length / 2;
    left_len = middle;
    right_len = length - middle;

    left = sort(array, middle);
    right = sort(&array[middle], right_len);

    // merge until one of 2 buffers is empty
    sorted = malloc(sizeof(int) * length);
    assert(sorted != NULL);

    for (i = 0, left_idx = 0, right_idx = 0; left_idx < left_len && right_idx < right_len; i++) {
        if (left[left_idx] < right[right_idx]) {
            sorted[i] = left[left_idx];
            left_idx++;
        } else {
            sorted[i] = right[right_idx];
            right_idx++;
        }
    }

    // clear left buffer
    for (; left_idx < left_len; left_idx++, i++) {
        sorted[i] = left[left_idx];
    }

    // clear right buffer
    for (; right_idx < right_len; right_idx++, i++) {
        sorted[i] = right[right_idx];
    }

    free(left);
    free(right);

    return sorted;
}

int heightChecker(int *heights, int heightsSize) {

    int i, num;
    int *sorted_heights = sort(heights, heightsSize);

    for (i = 0, num = 0; i < heightsSize; i++) {
        if (sorted_heights[i] != heights[i]) {
            num++;
        }
    }

    return num;
}

int main(void) {
    int sorted_heights[] = {
            3, 4, 5,
    };
    int length = sizeof(sorted_heights) / sizeof(int);

    int i;

    int *sorted = sort(sorted_heights, length);

    for (i = 0; i < length; i++) {
        printf("%d, ", sorted[i]);
    }
    puts("");

    //printf("heightChecker: %d\n", heightChecker(sorted_heights, length));

    return 0;
}
