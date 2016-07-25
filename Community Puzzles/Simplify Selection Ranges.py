numbers = sorted(map(int, input()[1:-1].split(',')))
lastNum = float('inf')
rangeStart = float('inf')
rangeEnd = float('inf')
output = []
for n in numbers:
    if n == lastNum+1:
        rangeEnd = n
    else:
        if rangeStart != float('inf'):
            if rangeEnd - rangeStart >= 2:
                output.append(str(rangeStart) + '-' + str(lastNum))
            elif rangeEnd - rangeStart == 1:
                output.append(str(rangeStart))
                output.append(str(rangeEnd))
            else:
                output.append(str(rangeStart))
        
        rangeStart = n
        rangeEnd = n
    
    lastNum = n

if rangeEnd - rangeStart >= 2:
    output.append(str(rangeStart) + '-' + str(lastNum))
elif rangeEnd - rangeStart == 1:
    output.append(str(rangeStart))
    output.append(str(rangeEnd))
else:
    output.append(str(rangeStart))

print(','.join(output))
