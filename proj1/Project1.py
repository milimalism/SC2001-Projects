import random
import numpy as np
import time as t
import pandas as pd

S = [16,17,18, 19]#[20,5,10,15,,22,24,26,28,30,35]
SIZE1 = [2,3,4,5]
SIZE = [300000, 100000, 600000, 1000000]
NO_OF_ARRAYS =  1
X = 10000000

#lists i used for testing, can ignore
LIST1 = [4444, 1232, 3000, 2198, 5223, 9000,1248,871,9190, 1430, 4422]
LIST = [567,3,22,6,78,1,33,567,9,10,22, 2, 4 ,3, 667767]
LIST0 = [9,1,8888888,0]
comparisons = 0


def arrays(m):
    inputList = []
    for i in range (NO_OF_ARRAYS):
        c = np.random.randint(1, X, size=m)
        c = c.tolist()
        inputList.append(c)
        #print("\n:", i+1, " : " , c, "\n")
    
    return inputList

def insertionsort(list):
    global comparisons
    for i in range(1, len(list)):
        j = i
        while j > 0:
            comparisons= comparisons+1
            #print("comparisons: " , comparisons, "\n")
            if list[j] < list[j-1]:
                list[j], list[j-1] = list[j-1], list[j]
                j -= 1
            else:
                break
        i += 1

    return list

            
def mergesort(list,S):
    global comparisons
    if len(list) > S:
        half = (len(list)+1) // 2
        left = list[:half]
        right = list[half:]
        
        mergesort(left,S)
        mergesort(right,S)
        
        i = j = k = 0
        
        while i < len(left) and j < len(right):
            comparisons= comparisons+1
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
        return insertionsort(list)
        
            
    return list

#just a method to check if the list is sorted, used only for self-checking
def sorted_check(list):
    for i in range (len(list)-1):
        if(list[i]>list[i+1]):
            print("ERROR YOURE FAILING")
        
def main():

    global comparisons
    fullData = [["Array Size","Array", "Key Comparisons", "Time taken", "S","Key Best","Time Best"]]

    #generating list of lists
    #unchanged = arrays()
    
    #first run of method to prevent discrepancies in timing due ot caching etc 
    initial = t.perf_counter_ns()
    mergesort(LIST1, 5)
    final = t.perf_counter_ns() 
    print("time = " , final-initial, " ", comparisons)

    #running mergesort for each list in inputList
    for size in SIZE:
        for s in S:  
            inputList = arrays(size)
            for i in range (NO_OF_ARRAYS):
                comparisons = 0
                initial = t.perf_counter_ns()
                #sorted = mergesort(inputList[i]) 
                sorted = mergesort(inputList[i], s)
                final = t.perf_counter_ns()
                #print("time elapsed : ", final-initial)
                #print("comparisons :" ,comparisons)
                avg_comp = comparisons
                avg_time = final-initial
                comparisons = 0
                initial = t.perf_counter_ns()
                #sorted = mergesort(inputList[i]) 
                sorted = mergesort(inputList[i], s)
                final = t.perf_counter_ns()
                #storing the data generated per run of mergesort
                data = [size,0, avg_comp, avg_time, s, comparisons, final-initial]
                #data = [SIZE,j, comparisons, final-initial, S,]
                fullData.append(data)
        

    print(fullData)


    #SAVING THE GENERATED DATA (STORED IN fullData) TO AN EXCEL FILE
    # Convert the 2D list to a pandas DataFrame
    new_data = pd.DataFrame(fullData[1:], columns=fullData[0])

    # Specify the Excel file name
    excel_file = "partc_2.xlsx"

    # Load the existing Excel file into a DataFrame
    existing_df = pd.read_excel(excel_file)

    # Append the new data to the existing DataFrame
    updated_df = existing_df.append(new_data, ignore_index=True)

    # Save the updated DataFrame back to the Excel file without overwriting
    updated_df.to_excel(excel_file, index=False)

    #check = mergesort(inputList[0])
    #sorted_check(check)
    #print(b-a)
    #print(arraygenerator())
    #print(comparisons)

main()
