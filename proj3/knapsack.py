def knapsack(w, p, C, n):
    profit = [[0 for i in range(n + 1)] for j in range(C + 1)]

    for r in range(1, C + 1):
        for c in range(1, n + 1):
            profit[r][c] = profit[r][c-1]
            
            if w[c - 1] <= r:
                if profit[r][c] < profit[r-w[c-1]][c-1] + p[c-1]:
                    profit[r][c] = profit[r-w[c-1]][c-1] + p[c-1]

    print(profit)
    return profit[C][n]

def knapsack2(w, p, C, N):
    dp = [[0 for i in range(N + 1)] for j in range(C + 1)]
    hint = [[0 for i in range(N + 1)] for j in range(C + 1)]

    for i in range(N):
        dp[i][0] = 0
        dp[0][i] = 0

    for n in range(1,N+1):
        for c in range(1,C+1):
            #If the current item's weight exceeds the knapsack's capacity, skip it.
            if w[n-1] > c:
                dp[c][n] = dp[c][n-1]
            else:
                # Otherwise, consider the maximum of two options:
                # 1. Include the current item, adding its profit to the previous maximum profit.
                # 2. Exclude the current item, retaining the previous maximum profit.
                dp[c][n] = max(dp[c][n-1], dp[c-w[n-1]][n] + p[n-1])
                if (dp[c][n] != dp[c][n-1]):
                    hint[c][n] = c-w[n-1]
    obj=[]
    i = C 
    j = N
    while(1):
        if(i<0 | j<0):
            break
        if(hint[i][j]!=0):
            obj.append(j)
            i = hint[i][j] 
        else:
            if(j-1==0):
                break
            j = j-1
            
    print(obj)
    return dp[C][N]


def main():
    parta = knapsack2([5, 6, 8], [7, 6, 9], 14, 3)
    print(parta)

if __name__ == '__main__':
    main()


