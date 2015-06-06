#include<iostream>
#define O(x)std::cout<<(x);
main(){int x,y,X,Y;std::cin>>x>>y>>X>>Y;while(1){O(y>Y?(Y++,"S"):y<Y?(Y--,"N"):"")O(x>X?(X++,"E"):x<X?(X--,"W"):"")O("\n")}}
