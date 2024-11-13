# Jonah Ebent, 11/8/24
def gcs(s1, s2):
    '''returns the longest common sequence of letters in the two strings'''
    memo = [[None] * (len(s2)+1) for _ in range(len(s1)+1)]
    return sub_gcs(memo, s1, s2, 0, 0)

def sub_gcs(memo, s1, s2, i, j):
    '''recursive helper function'''
    if memo[i][j] == None:
        if i == len(s1) or j == len(s2):
            memo[i][j] = ''
        elif s1[i] == s2[j]:
            memo[i][j] = s1[i] + sub_gcs(memo, s1, s2, i+1, j+1)
        else:
            down = sub_gcs(memo, s1, s2, i+1, j)
            right = sub_gcs(memo, s1, s2, i, j+1)
            if len(down) > len(right):
                memo[i][j] = down
            else:
                memo[i][j] = right
    return memo[i][j]