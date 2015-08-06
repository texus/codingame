x,y,X,Y=map(int,input().split())
while 1:Y,v=(((Y,''),(Y-1,'N'))[y<Y],(Y+1,'S'))[y>Y];X,h=(((X,''),(X-1,'W'))[x<X],(X+1,'E'))[x>X];print(v+h)
