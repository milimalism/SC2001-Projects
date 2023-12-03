import random

"""
Best case graph
"""
def best_case(v):
    with open("graphs.txt", "a") as f:
        print(v-1, file = f)
        print(v, file = f)
        
    for i in range(1, v):
        if i+1 > v:
            break
        
        else:
            with open("graphs.txt", "a") as f:
                print("{} {} {}".format(i, i+1, random.randint(1,100)), file = f)
    
    with open("graphs.txt", "a") as f:
        print("-1", file = f)
        print("-2\n", file = f)
    
"""
Worst case graph
"""
def worst_case(v):
    with open("graphs.txt", "a") as f:
        print(v, file = f)
        print(v * (v-1), file = f)
        
    for i in range (1, v+1):
        for j in range(1, v+1):
            if j == i:
                continue
            
            else:
                with open("graphs.txt", "a") as f:
                    print("{} {} {}".format(i, j, random.randint(1,100)), file = f)

    with open("graphs.txt", "a") as f:
        print("-1", file = f)
        print("-2\n", file = f)

"""
Average case graph
"""
def average_case(v):
    with open("graphs.txt", "a") as f:
        print(v, file = f)
        
    edges = 0
        
    for i in range (1, v+1):
        for j in range(1, v+1):
            if j == i:
                continue
            
            elif random.getrandbits(1) == 0:
                continue
            
            else:
                edges += 1
                with open("graphs.txt", "a") as f:
                    print("{} {} {}".format(i, j, random.randint(1,100)), file = f)

    with open("graphs.txt", "a") as f:
        print("-1", file = f)
        print(edges, file = f)
        print("-2\n", file = f)
    
"""
Varying |V| from range 1 - 51
"""
def v_vary():
    for v in range(5, 11, 5):
        best_case(v)
        worst_case(v)
        average_case(v)

def main():
    v_vary()

if __name__ == '__main__':
    main()