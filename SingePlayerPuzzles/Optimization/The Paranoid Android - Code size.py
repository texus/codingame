_,_,_,F,P,_,_,e=map(int,input().split());elevators=dict(map(int,input().split())for x in range(e))
while 1:f,p,d=input().split();f=int(f);p=int(p);t=(elevators.get(f,0),P)[f==F];print(('WAIT','BLOCK')[(t>p and d=='LEFT')or(t<p and d=='RIGHT')])
