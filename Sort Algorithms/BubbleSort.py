#Implementing Bubble Sort
import time
import random


def BubbleSort(list):
    n = len(list) #list of size n
    num_comp = 0 #comparisons
    num_swap = 0 #swaps

    #iterate through the whole list
    for i in range(n - 1):
        # the last i elements are already sorted
        for j in range(0, n-i-1):
            # iterate trough the list from 0 to n-i-1
            #there is a comparison everytime this loop iterates
            num_comp += 1
            if(list[j] > list[j+1]):
                list[j], list[j+1] = list[j+1], list[j] #this is a neat swap in one line that I found on geeksforgeeks
                num_swap += 1

    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    return list

def BubbleSortReverse(list):
    n = len(list) #list of size n
    num_comp = 0 #comparisons
    num_swap = 0 #swaps

    #iterate through the whole list
    for i in range(n - 1):
        # the last i elements are already sorted
        for j in range(0, n-i-1):
            # iterate trough the list from 0 to n-i-1
            #there is a comparison everytime this loop iterates
            num_comp += 1
            if(list[j] < list[j+1]):
                list[j], list[j+1] = list[j+1], list[j] #this is a neat swap in one line that I found on geeksforgeeks
                num_swap += 1

    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    return list

#Method for generating a large randomized list
def ListGenerator(size):
    randomList = []
    for i in range(0, size):
        n = random.randint(0, 99)
        randomList.append(n)
    return randomList


print("Statistics for BubbleSort")
for i in range(1, 2):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    print(randomList)
    randomList = BubbleSortReverse(randomList)
    print(randomList)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")
