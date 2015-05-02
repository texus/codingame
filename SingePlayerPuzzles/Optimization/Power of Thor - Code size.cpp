#include<iostream>
#define O(x)std::cout<<(x);
int main(){int x,y,X,Y,E;std::cin>>x>>y>>X>>Y;while(1){std::cin>>E;O(y>Y?(Y+=1,"S"):y<Y?(Y-=1,"N"):"")O(x>X?(X+=1,"E"):x<X?(X-=1,"W"):"")O("\n")}}
