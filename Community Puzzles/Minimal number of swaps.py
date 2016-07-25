nums = []

n = int(input())
for i in input().split():
    nums.append(i)

l = 0
r = len(nums)-1
turns = 0
while l < r:
    if nums[l] == '0':
        while True:
            r -= 1
            if l >= r:
                break
            if nums[r+1] == '1':
                turns += 1
                break
    
    l += 1

print(turns)
