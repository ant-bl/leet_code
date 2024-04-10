#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

    '.' Matches any single character.​​​​
    '*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Constraints:

    1 <= s.length <= 20
    1 <= p.length <= 20
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
*/

int isMatch(char *s, char *p) {

    int r_idx;
    char pc;

    for (r_idx = 0; r_idx < strlen(p);) {

        pc = p[r_idx];

        if ((r_idx + 1) < strlen(p) && p[r_idx + 1] == '*') {
            while (*s != '\0' && (pc == '.' || pc == *s)) {
                if (isMatch(s, &p[r_idx + 2])) {
                    return 1;
                }
                s++;
            }
            r_idx += 2;
        } else {
            if (*s == '\0')
                return 0;

            if (pc == '.' || pc == *s) {
                s++;
                r_idx += 1;
            } else {
                return 0;
            }
        }
    }

    if (*s == '\0')
        return 1;

    return 0;
}

int main(void) {

    int m;

    /**/
    m = isMatch("", ".*");
    printf("%d\n", m);
    assert(m);

    m = isMatch("a", "a");
    printf("%d\n", m);
    assert(m);

    m = isMatch("aa", "a");
    printf("%d\n", m);
    assert(!m);

    m = isMatch("a", ".");
    printf("%d\n", m);
    assert(m);

    m = isMatch("aaaaaaaab", "a*b");
    printf("%d\n", m);
    assert(m);

    m = isMatch("mississippi", "mis*is*ip*.");
    printf("%d\n", m);
    assert(m);

    m = isMatch("aaa", "a*a");
    printf("%d\n", m);
    assert(m);

    return 0;
}
