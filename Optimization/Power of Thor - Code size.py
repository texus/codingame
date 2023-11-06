a,b,x,y=map(int,input().split())
while 1:
 print((""if y==b else"NS"[y<b])+(""if x==a else"EW"[x>a]))
 y,x=y-(y>b)+(y<b),x-(x>a)+(x<a)
