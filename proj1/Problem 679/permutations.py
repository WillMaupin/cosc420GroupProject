dictionary1= {
	"FREE" : "1",
	"FREEF" : "14",
	"FREEFARE": "142",
	"FREEFAREA": "1423",
	"*" : "*"
}

dictionary2 = {
	"FARE" : "2",
	"FAREEF" : "24",
	"FAREA" : "23",
	"FAREEFREE" : "241",
	"*" : "*"
}

dictionary3 = {
	"AREA" : "3",
	"*" : "*"
}

dictionary4 = {
	"REEF" : "4",
	"REEFREE" : "41",
	"REEFARE" : "42",
	"REEFAREA" : "423",
	"*" : "*"
}

lengths = {
	"1" : 4,
	"14" : 5,
	"2" : 4,
	"24" : 6,
	"23" : 5,
	"423" : 8,
	"3" : 4,
	"4" : 4,
	"41" : 7,
	"42" : 7,
	"241" : 9,
	"142" : 8,
	"1423" : 9
}

'''
print(dictionary1)
print(dictionary2)
print(dictionary3)
print(dictionary4)
'''

arr = [0, 0, 0, 0]

sum = 0
index = 0
for a in dictionary1:
	arr[0] = dictionary1[a]
	for b in dictionary2:
		arr[1] = dictionary2[b]
		for c in dictionary3:
			arr[2] = dictionary3[c]
			for d in dictionary4:
				arr[3] = dictionary4[d]
				flag = 0
				for x in arr:
					for y in arr:
						if(x != y):
							for i in range(0,len(x)):
								for j in range(0,len(y)):
									if(i <= j):
										if(x[i] == y[j]):
											flag = 1
				if(flag == 0):
					flagA = 0
					flagB = 0
					flagC = 0
					flagD = 0
					for x in arr:
						for i in range(0, len(x)):
							if(x[i] == "1"):
								flagA = 1
							if(x[i] == "2"):
								flagB = 1
							if(x[i] == "3"):
								flagC = 1
							if(x[i] == "4"):
								flagD = 1
					if(flagA == 1 and flagB == 1 and flagC == 1 and flagD == 1):
						print(arr)

