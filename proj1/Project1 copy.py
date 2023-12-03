import random

S = 10
X = 9999
LIST = [4, 1, 3, 2, 5, 9]

def arraygenerator():
    inputlist = []
    for i in range(1, 5):
        temp = []
        for j in range(i):
            temp.append(random.randint(1, X))
            j += 1
        inputlist.append(temp)
    
    return inputlist

def insertionsort(list):
    for i in range(1, len(list)):
        j = i
        while j > 0:
            if list[j] < list[j-1]:
                list[j], list[j-1] = list[j-1], list[j]
                j -= 1
            else:
                break
        i += 1

    return list
            
            
def mergesort(list):
    if len(list) > S:
        half = len(list) // 2
        left = list[:half]
        right = list[half:]
        
        mergesort(left)
        mergesort(right)
        
        i = j = k = 0
        
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                list[k] = left[i]
                i += 1
            else:
                list[k] = right[j]
                j += 1
            k += 1
 
        while i < len(left):
            list[k] = left[i]
            i += 1
            k += 1
 
        while j < len(right):
            list[k] = right[j]
            j += 1
            k += 1
    
    else:
        insertionsort(list)
            
    return list
        
def main():
    print(mergesort(LIST))
    arraygenerator()

if __name__ == "__main__":
    main()
