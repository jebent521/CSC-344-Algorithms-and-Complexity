#   s t r 1
# s 0 0 0 0 0
# t 0 0 0 0 0
# r 0 0 0 0 0
# 2 0 0 0 0 0
#   0 0 0 0 0

def gcs(s1, s2):
    memo = [[-1] * (len(s2)+1) for _ in range(len(s1)+1)]
    print(f(memo, s1, s2, 0, 0))
    [print(*row, sep='\t') for row in memo]

def f(memo, s1, s2, i, j):
    # print(i, j)
    # [print(row) for row in memo]

    if memo[i][j] == -1:
        if i == len(s1) or j == len(s2):
            memo[i][j] = 0
        elif s1[i] == s2[j]:
            memo[i][j] = 1 + f(memo, s1, s2, i+1, j+1)
        else:
            memo[i][j] = max(f(memo, s1, s2, i+1, j), f(memo, s1, s2, i, j+1))
    return memo[i][j]

gcs('ace', 'abcde')