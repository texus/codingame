minHours = '99'
minMins = '99'
minSecs = '99'

n = int(input())
for i in range(n):
    t = input()
    index = t.find(':')
    hours = t[0:index]
    index2 = t.find(':', index+1)
    mins = t[index+1:index2]
    secs = t[index2+1:]
    
    if hours < minHours or (hours == minHours and mins < minMins) or (hours == minHours and mins == minMins and secs < minSecs):
        minHours = hours
        minMins = mins
        minSecs = secs

print(str(minHours) + ':' + str(minMins) + ':' + str(minSecs))
