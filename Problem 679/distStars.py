#arr = [0, 0, 0, 0, 0]

'''
Calculates the distribution of stars, does not permute them
'''


leftovers = 14
stars = 5

arr = []
for i in range(0, stars):
    arr.append(0)

arr[0] = leftovers
print(arr)

flag = 0
while(flag == 0):
    index = stars - 2
    while(arr[index] < 2):
        index -= 1
    arr[index] -= 1
    sum = 0

    for i in range (0, index + 1):
        sum += arr[i]
    if(index == 0):
        arr[index+1] = leftovers - arr[index]
    else:
        arr[index + 1] = leftovers - sum
    for i in range(index+2, stars):
        arr[i] = 0


    printflag = 0
    for i in range(0, stars-1):
        if( arr[i] < arr[i+1]):
            printflag = 1
    if(printflag == 0):
        print(arr)


    flag = 1
    if(stars > 2):
        for i in range(0, stars - 2):
            if(arr[i] != 1):
                flag = 0
    else:
        if(arr[0] > arr[1]):
            flag = 0
