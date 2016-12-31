#include "node.hpp"

node::node(int *goal,int X = 0,int Y = 0,int cost = 1, int Pkey = 0)
{
	x = X;
	y = Y;
	
	gcost_ = cost + 1;
	
	setKey();
	getFcost(goal);
	pkey_ = Pkey;
}


void node::getFcost( int *goal) 
{
	int h1 = x - goal[0];
	int h2 = y - goal[1];
	int h =  int(fabs(h1) + fabs(h2));
	fcost = gcost_ + h;
}
void node::setKey()
{
	key_ = 100*x+y;
	//std::cout<<"the new node has key "<<key_<<" with x and y "<<x<<" "<<y<<std::endl;
}
void node::getSuccs(std::vector<node>& succsNode, int *goal,int& xlim, int& ylim)
{
	//std::cout<<gcost_<<" is the parent gcost"<<" and the parent key is "<<getKey()<<std::endl;
 	if(x+1<xlim){succsNode.push_back( node(goal,x+1,y,gcost_,getKey()));}
 	//std::cout<<succsNode[0].getKey()<< " is the child key "<<std::endl;
 	if(x-1 > 0){succsNode.push_back( node(goal,x-1,y,gcost_,getKey()));}
 	if(y+1<ylim){succsNode.push_back( node(goal,x,y+1,gcost_,getKey()));}
 	if(y-1>0){succsNode.push_back( node(goal,x,y-1,gcost_,getKey()));}
	
}
