#   s t r 1
# s 0 0 0 0 0
# t 0 0 0 0 0
# r 0 0 0 0 0
# 2 0 0 0 0 0
#   0 0 0 0 0

def gcs(s1, s2):
    memo = [[None] * (len(s2)+1) for _ in range(len(s1)+1)]
    print(f(memo, s1, s2, 0, 0, ''))
    [print(*row, sep='\t') for row in memo]

def f(memo, s1, s2, i, j, sub):
    if memo[i][j] == None:
        if i == len(s1) or j == len(s2):
            memo[i][j] = (0, '')
        elif s1[i] == s2[j]:
            next = f(memo, s1, s2, i+1, j+1, sub)
            memo[i][j] = (1 + next[0], s1[i] + next[1])
        else:
            down = f(memo, s1, s2, i+1, j, sub)
            right = f(memo, s1, s2, i, j+1, sub)
            if down[0] > right[0]:
                memo[i][j] = down
            else:
                memo[i][j] = right
    return memo[i][j]

gcs('ace', 'abcde')