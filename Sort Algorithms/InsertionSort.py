#Implementing Insertion Sort
import time
import random
num_comp = 0
num_swap = 0

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


print("Statistics for InsertionSort")
for i in range(1, 2):
    print("Sorting list of size:", 10**i)
    start_time = time.time()
    randomList = ListGenerator(10**i)
    print(randomList)
    randomList = InsertionSort(randomList)
    print(randomList)
    print("--- %s seconds ---" % (time.time() - start_time))
    print("------------------------------")
