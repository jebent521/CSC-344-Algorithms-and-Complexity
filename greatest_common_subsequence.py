def gcs(s1: str, s2: str, i=0, j=0, memo=None):
    '''Returns the greatest common subsequence of characters between s1 and s2.

    Initial call: `gcs(s1, s2)`'''
    if memo == None:
        memo = [[None] * (len(s2)+1) for _ in range(len(s1)+1)]

    if memo[i][j] == None:
        if i == len(s1) or j == len(s2):
            memo[i][j] = ''
        elif s1[i] == s2[j]:
            memo[i][j] = s1[i] + gcs(s1, s2, i+1, j+1, memo)
        else:
            down = gcs(s1, s2, i+1, j, memo)
            right = gcs(s1, s2, i, j+1, memo)
            if len(down) > len(right):
                memo[i][j] = down
            else:
                memo[i][j] = right
    return memo[i][j]