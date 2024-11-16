def cashiers_algorithm(x: int, coins: list[int]) -> list[int]:
    '''returns a list of the coins used to make up `x`, using a greedy algorithm'''
    change = []
    while x > 0:
        coin = max([c for c in coins if c <= x])
        change.append(coin)
        x -= coin
    return change

def test_coins(coins: list[int], start=0, end=100):
    '''returns a list of the number of coins required to make the values from 1 to 99, using the cashier's algorithm with the given set of coins'''
    return [len(cashiers_algorithm(i, coins)) for i in range(start, end)]