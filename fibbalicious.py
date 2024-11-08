def fibbalicious(n):
    if n == 0: return 1
    if n == 1: return 1
    if n == 2: return 2
    memo = [0] * n
    memo[0] = 1
    memo[1] = 1
    memo[2] = 2
    for i in range(3, n):
        memo[i] = memo[i-1] + 3*memo[i-2] - memo[i-3]
    return memo[n-1]

for i in range(10):
    print(fibbalicious(i))
