#from BubbleSort import *
#from InsertionSort import *
#from SelectionSort import *
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

def SelectionSort(list):
    global num_comp
    global num_swap
    start = 0
    while(start < len(list) - 1):
        minsIndex = findIndexOfMin(list, start)
        list[start], list[minsIndex] = list[minsIndex], list[start]
        start += 1
    # print("Number of Comparisons: ", num_comp)
    # print("Number of Swaps: ", num_swap)
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
    # print("Number of Comparisons: ", num_comp)
    # print("Number of Swaps: ", num_swap)
    return list


#Main operation, inserting an element into a sorted list
def InsertKey(list, end, key):
    global num_comp
    global num_swap
    backward = end
    while (backward >= 0 and list[backward] > key):
        num_comp += 1
        list[backward + 1] = list[backward]
        backward -= 1
    num_swap += 1
    list[backward + 1] = key
    return list

def InsertionSort(list):
    global num_comp
    global num_swap
    forward = 1
    while(forward < len(list)):
        list = InsertKey(list, forward - 1, list[forward])
        forward += 1
    # print("Number of Comparisons: ", num_comp)
    # print("Number of Swaps: ", num_swap)
    return list


#Main operation, inserting an element into a sorted list
def InsertKeyReverse(list, end, key):
    global num_comp
    global num_swap
    backward = end
    while (backward >= 0 and list[backward] < key):
        num_comp += 1
        list[backward + 1] = list[backward]
        backward -= 1
    num_swap += 1
    list[backward + 1] = key
    return list

def InsertionSortReverse(list):
    global num_comp
    global num_swap
    forward = 1
    while(forward < len(list)):
        list = InsertKeyReverse(list, forward - 1, list[forward])
        forward += 1
    # print("Number of Comparisons: ", num_comp)
    # print("Number of Swaps: ", num_swap)
    return list


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

    # print("Number of comparisons: ", num_comp)
    # print("Number of swaps: ", num_swap)
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

    #print("Number of comparisons: ", num_comp)
    #print("Number of swaps: ", num_swap)
    return list


#Method for generating a large randomized list
def ListGenerator(size):
    randomList = []
    for i in range(0, size):
        n = random.randint(0, 99)
        randomList.append(n)
    return randomList



print("-=-=-=Statistics for BubbleSort=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = BubbleSort(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")


print("-=-=-=Statistics for BubbleSort in reverse order=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = BubbleSortReverse(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")



print("-=-=-=Statistics for InsertionSort=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = InsertionSort(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")


print("-=-=-=Statistics for InsertionSort in reverse order=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = InsertionSort(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")



print("-=-=-=Statistics for SelectionSort=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = SelectionSort(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")


print("-=-=-=Statistics for SelectionSort in reverse order=-=-=-")
num_comp = 0
num_swap = 0
for i in range(1, 6):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    randomList = SelectionSortReverse(randomList)
    print("Number of comparisons: ", num_comp)
    print("Number of swaps: ", num_swap)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")
