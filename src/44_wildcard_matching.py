import functools

# Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
#    '?' Matches any single character.
#    '*' Matches any sequence of characters (including the empty sequence).

# The matching should cover the entire input string (not partial).

@functools.cache
def is_match(s, p):

    if len(s) == 0 and len(p) == 0:
        return True
    
    if len(s) > 0 and len(p) == 0:
        return False

    if p[0] == '*':
        next_sub_pattern = ""
        for sp in p[1:]:
            if sp not in ["*", "?"]:
                next_sub_pattern += sp
            else:
                break

        for i in range(0, len(s) + 1):
            if next_sub_pattern is None or s[i:].startswith(next_sub_pattern):
                if is_match(s[i:], p[1:]):
                    return True
        return False

    if len(s) == 0:
        return False

    if p[0] == '?':
        return is_match(s[1:], p[1:])
    else:
        if p[0] == s[0]:
            return is_match(s[1:], p[1:])
        else:
            return False

class Solution:
    def isMatch(self, s: str, p: str) -> bool:

        if len(p) > 0:
            cleaned_p = p[0]
            for c in p[1:]:
                if c == "*" and cleaned_p[-1] == "*":
                    continue
                cleaned_p += c
        else:
            cleaned_p = p

        return is_match(s, cleaned_p)

def test():

    s = "aa"
    p = "a"
    res = is_match(s, p)
    assert not res

    s = "aa"
    p = "*"
    res = is_match(s, p)
    assert res

    s = "cb"
    p = "?a"
    res = is_match(s, p)
    assert not res

    s = ""
    p = "******"
    res = is_match(s, p)
    assert res

    s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba"
    p = "a*******b"
    res = Solution().isMatch(s, p)
    assert not res

    p = "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a"
    s = "babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb"
    res = Solution().isMatch(s, p)
    assert not res
    
if __name__ == "__main__":
    test()

