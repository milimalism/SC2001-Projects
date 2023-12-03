def knapsack(weights, profits, capacity):
    table = [0 for i in range(capacity + 1)]
    
    for i in range(len(weights)):
        for j in range(1, capacity + 1):
            if (weights[i] <= j):
                table[j] = max(table[j], profits[i] + table[j - weights[i]])

    print(table)
    return table[capacity]


def main():
    print(knapsack([4, 6, 8], [7, 6, 9], 14))
    print(knapsack([5, 6, 8], [7, 6, 9], 14))

if __name__ == "__main__":
    main()