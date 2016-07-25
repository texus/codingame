[letters, words] = input().split(': ')

def decode(word):
    if len(word) == 4 and word[1] == letters[2]:  return '0'
    if len(word) == 3 and word[0] == letters[18]: return '1'
    if len(word) == 3 and word[0] == letters[16]: return '2'
    if len(word) == 5 and word[0] == letters[16]: return '3'
    if len(word) == 4 and word[1] == letters[18]: return '4'
    if len(word) == 4 and word[0] == letters[6]:  return '5'
    if len(word) == 3 and word[0] == letters[22]: return '6'
    if len(word) == 5 and word[0] == letters[22]: return '7'
    if len(word) == 5 and word[0] == letters[2]:  return '8'
    if len(word) == 4 and word[3] == letters[7]:  return '9'
    
print(''.join(map(decode, words.split('-'))))
