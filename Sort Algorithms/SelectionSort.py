#Implementing Selection Sort
import time
import random
num_comp = 0
num_swap = 0

def findIndexOfMin(list, start):
    global num_comp
    global num_swap
    minsIndex = start
    index = 1
    while(index < len(list)):
        num_comp += 1
        if(list[index] < list[minsIndex]):
            num_swap += 1
            minsIndex = index
        index += 1
    return minsIndex

def findIndexOfMax(list, start):
    global num_comp
    global num_swap
    maxIndex = start
    index = 1
    while(index < len(list)):
        num_comp += 1
        if(list[index] > list[maxIndex]):
            num_swap += 1
            maxIndex = index
        index += 1
    return maxIndex

def SelectionSort(list):
    global num_comp
    global num_swap
    start = 0
    while(start < len(list) - 1):
        minsIndex = findIndexOfMin(list, start)
        list[start], list[minsIndex] = list[minsIndex], list[start]
        start += 1
    print("Number of Comparisons: ", num_comp)
    print("Number of Swaps: ", num_swap)
    return list

def SelectionSortReverse(list):
    global num_comp
    global num_swap
    for i in range(len(list)):
        maxIndex = i
        for j in range(i+1, len(list)):
            num_comp += 1
            if(list[maxIndex] < list[j]):
                num_swap += 1
                maxIndex = j
        list[i], list[maxIndex] = list[maxIndex], list[i]
    print("Number of Comparisons: ", num_comp)
    print("Number of Swaps: ", num_swap)
    return list

#Method for generating a large randomized list
def ListGenerator(size):
    randomList = []
    for i in range(0, size):
        n = random.randint(0, 99)
        randomList.append(n)
    return randomList


print("Statistics for SelectionSort")
for i in range(1, 2):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    print(randomList)
    randomList = SelectionSortReverse(randomList)
    print(randomList)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")
