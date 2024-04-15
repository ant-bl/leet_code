#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
You are given an integer array nums and two positive integers m and k.

Return the maximum sum out of all almost unique subarrays of length k of nums. If no such subarray exists, return 0.

A subarray of nums is almost unique if it contains at least m distinct elements.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [2,6,7,3,1,7], m = 3, k = 4
Output: 18
Explanation:
    There are 3 almost unique subarrays of size k = 4. These subarrays are [2, 6, 7, 3], [6, 7, 3, 1], and
    [7, 3, 1, 7]. Among these subarrays, the one with the maximum sum is [2, 6, 7, 3] which has a sum of 18.

Example 2:

Input: nums = [5,9,9,2,4,5,4], m = 1, k = 3
Output: 23
Explanation:
    There are 5 almost unique subarrays of size k. These subarrays are [5, 9, 9], [9, 9, 2], [9, 2, 4], [2, 4, 5],
    and [4, 5, 4]. Among these subarrays, the one with the maximum sum is [5, 9, 9] which has a sum of 23.

Example 3:

Input: nums = [1,2,1,2,1,2,1], m = 3, k = 3
Output: 0
Explanation:
    There are no subarrays of size k = 3 that contain at least m = 3 distinct elements in the given array
    [1,2,1,2,1,2,1]. Therefore, no almost unique subarrays exist, and the maximum sum is 0.
*/

#define MAX(X, Y)((X)<(Y) ? (Y) : (X))

#define MAP_SIZE 1000

struct node {
    int num;
    int counter;
    struct node *next;
};

struct map {
    struct node *table[MAP_SIZE];
    int num;
    int num_unique;
};

static int put(struct map *m, struct node *n) {

    int idx = n->num % MAP_SIZE;
    if (m->table[idx] == NULL) {
        m->table[idx] = n;
        n->next = NULL;
        n->counter = 1;
        m->num_unique++;
        return 1;
    } else {
        struct node *iter = m->table[idx];
        struct node **prev = &m->table[idx];

        while (iter != NULL) {
            // still present: inc
            if (iter->num == n->num) {
                iter->counter++;
                return 0;
            }

            // add sorted
            if (iter->num > n->num) {
                n->next = iter;
                n->counter = 1;
                m->num_unique++;
                *prev = n;
                return 1;
            }

            //
            prev = &iter->next;
            iter = iter->next;
        }

        // add on tail
        n->counter = 1;
        n->next = NULL;
        m->num_unique++;
        *prev = n;
        return 1;
    }
}

static struct node *del(struct map *m, int num) {

    int idx = num % MAP_SIZE;
    assert (m->table[idx] != NULL);

    struct node *iter = m->table[idx];
    assert (iter != NULL);
    struct node **prev = &m->table[idx];

    while (1) {
        if (iter->num == num) {
            break;
        } else {
            prev = &iter->next;
            iter = iter->next;
            assert (iter != NULL);
        }
    }
    assert(iter->num == num);

    iter->counter--;
    if (iter->counter == 0) {
        *prev = iter->next;
        m->num_unique--;
        return iter;
    } else {
        return NULL;
    }
}

static void print(struct map *m) {

    int idx;
    struct node *iter;

    for (idx = 0; idx < MAP_SIZE; idx++) {
        iter = m->table[idx];
        printf("[%2d] ", idx);
        while (iter != NULL) {
            printf("%d %d -> ", iter->num, iter->counter);
            iter = iter->next;
        }
        puts("");
    }

}

long long maxSum(int *nums, int numsSize, int m, int k) {

    struct map *map;
    struct node const *head;
    struct node *heap;
    int i, left, right;
    long long cur_max = 0, max = 0;

    if (numsSize < k)
        return 0;

    map = calloc(1, sizeof(struct map));
    assert(map != NULL);

    heap = calloc(k, sizeof(struct node));
    assert(heap != NULL);

    head = heap;
    for (i = 1; i < k; i++) {
        heap[i - 1].next = &heap[i];
    }
    heap[k - 1].next = NULL;

    //printf("numsSize = %d\n", numsSize);

    for (right = 0; right < k; right++) {
        int num = nums[right];
        assert(heap != NULL);
        struct node *n = heap;
        heap = heap->next;
        n->num = num;
        if (put(map, n) == 0) {
            n->next = heap;
            heap = n;
        }

        cur_max += num;
    }

    //printf("num_unique : %d\n", num_unique);
    //printf("cur_max: %d\n", cur_max);

    if (map->num_unique >= m) {
        max = MAX(cur_max, max);
    }

    left = 0;
    while (right < numsSize) {
        struct node *n = NULL;
        int num;

        // Delete left
        num = nums[left];
        cur_max -= num;
        n = del(map, num);
        if (n != NULL) {
            n->next = heap;
            heap = n;
        }
        left++;

        // add right
        num = nums[right];
        cur_max += num;
        assert(heap != NULL);
        n = heap;
        heap = heap->next;
        n->num = num;
        if (put(map, n) == 0) {
            n->next = heap;
            heap = n;
        }

        if (map->num_unique >= m) {
            max = MAX(cur_max, max);
        }

        right++;
    }

    free(head);
    free(map);

    return max;
}

int main(void) {


    /*
     *
    struct map * m;
    struct node * n;

    m = calloc(1, sizeof(struct map));
    puts("===========");
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 3;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 2;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 3;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 4;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 5;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);

    puts("++++++++++++");
    printf("%p\n", del(m, 3));
    print(m);

    puts("++++++++++++");
    printf("%p\n", del(m, 3));
    print(m);

    n = calloc(1, sizeof(struct node));
    n->num = 3;
    puts("===========");
    printf("put => %d\n", put(m, n));
    print(m);
    */

    int max = 0;

    int array1[] = {2, 6, 7, 3, 1, 7};
    max = maxSum(array1, sizeof(array1) / sizeof(int), 3, 4);
    printf("max: %d\n", max);
    assert(max == 18);

    int array2[] = {5, 9, 9, 2, 4, 5, 4};
    puts("== maxSum ==");
    max = maxSum(array2, sizeof(array2) / sizeof(int), 1, 3);
    printf("max: %d\n", max);
    assert(max == 23);

    int array3[] = {1, 2, 1, 2, 1, 2, 1};
    puts("== maxSum ==");
    max = maxSum(array3, sizeof(array3) / sizeof(int), 3, 3);
    printf("max: %d\n", max);
    assert(max == 0);

    int array5[] = {
            996021492, 996021492, 973489433, 66259330, 554129007, 713784351, 646092981,
            328987029, 469368828, 685679486, 66259330, 165954500, 731567840, 595800464,
            552439059, 14673238, 157622945, 521321042, 386913607, 733723177, 330475939,
            462727944, 69696035, 958945846, 648914457, 627088742, 363551051, 50748590,
            400980660, 674779765, 439950964, 613843311, 385212079, 725525766, 813504429,
            385212079, 66563232, 578031878, 935017574, 554725813, 456892672, 245308625,
            626768145, 270964388, 554725813, 768296675, 676923124, 939689721, 115905765,
            625193590, 717796816, 27972217, 277242430, 768296675, 480860474, 659230631,
            570682291, 601689140, 955632265, 767424000, 251696645, 675750691, 767424000,
            251696645, 767424000, 675750691, 675750691, 251696645
    };
    puts("== maxSum ==");
    max = maxSum(array5, sizeof(array5) / sizeof(int), 8, 8);
    printf("max: %d\n", max);

    return 0;
}
