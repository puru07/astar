#include "include/astar.hpp"
#include <queue>

#include <algorithm>
class searchNode
{
public: 
	searchNode ( int& KeyToSearch)
	: _key(KeyToSearch)
	{}
	bool operator()( node& TheNode)
	{
		return _key == TheNode.getKey();
	}
private:
	int _key;

};

bool operator<(const node& a, const node& b) 
{
	
	return a.fcost > b.fcost;
}
class Comparator {
public:
    bool operator()(const node* a, const node* b)
    {
        return (a->fcost > b->fcost);
    }
};
astar::astar(int * Start, int * Goal, int* Arena, int Weight = 1)
{
	start = Start;
	goal = Goal;
	weight = Weight;
	xlim = Arena[0];
	ylim = Arena[1];
}

int astar::findPath( std::vector<node>& path)
{
	
	//std::priority_queue<node *, std::vector<node *>, Comparator> pq;
	std::priority_queue<node> pq;
	std::vector<int> openlist;
	std::vector<int>::iterator itOpen;
	
	node startNode = node(goal,0,0,0,0);
	pq.push(startNode);
	openlist.push_back(startNode.getKey());
	
	node * currNode ;//=  &startNode;
	std::vector<node> closedlist;
	int goalCheck = 0; 

	//for successors
	std::vector<node> succs;
	while(pq.size() != 0)
	{
		currNode = new node(goal, pq.top().x, pq.top().y, pq.top().gcost_, pq.top().pkey_);
		pq.pop();
		//std::cout<<currNode->x<<" "<<currNode->y<<" "<<currNode->getPkey()<<std::endl;
		//checking if goal is reached
		if ((currNode->x == goal[0]) && (currNode->y == goal[1]))
			{
				std::cout<<"goal reached!!"<<std::endl;
				std::cout << "total cost is "<<std::endl;
				goalCheck = 1;
				break;
			}

		// getting the successors
		
		currNode->getSuccs(succs,goal, xlim,ylim);
		
		for (std::vector<node>::iterator itSuccs = succs.begin(); itSuccs != succs.end(); ++itSuccs)
		{
			int currKey = itSuccs->getKey();
			//searching in open list
			itOpen = std::find(openlist.begin(), openlist.end(),currKey);
			if (itOpen != openlist.end())
			{
			//	std::cout<<"copy" <<std::endl;
				continue;
			}
			//searching in the closed list
			std::vector<node>::iterator searchIt = std::find_if(closedlist.begin(), closedlist.end(),searchNode(currKey));
			if (searchIt != closedlist.end()) 
			{
			//	std::cout<<"copy cl" <<std::endl;
				continue;
			}
			pq.push(*itSuccs);
			//std::cout<<"it is about to be pushed in "<<itSuccs->x<<" "<<itSuccs->y<<" key "<<itSuccs->getKey()<<std::endl;
			//std::cout<<*(&(*itSuccs))->x<<" "<<*(&(*itSuccs))->y<<std::endl;
			openlist.push_back(itSuccs->getKey());
		}

		succs.clear();
		// pushing it in closed list :
		closedlist.push_back(*currNode);
		//deleting it from openlist
		openlist.erase(remove(openlist.begin(), openlist.end(), currNode->getKey()), openlist.end());
		delete currNode;
	}
	std::cout<<"size of closed list "<<closedlist.size()<<std::endl;
	if (goalCheck == 1)
	{
		getPath(path, *currNode,closedlist);
		std::vector<node>::iterator row;

		int temp[2];
		int i = 0;
		std::cout<<path.size()<<std::endl;
		for (row = path.begin();row != path.end();++row)
		{
			std::cout<<"--------"<<++i<<"---------"<<std::endl;
			std::cout<<row->x<<" "<<row->y<<std::endl;
		}
	}
	else
	{
		std::cout<<"goal not found"<<std::endl;
	}
	
	std::cout<<"done!!!"<<std::endl;
	return goalCheck;
}

void astar::getPath(std::vector<node>& path,node& fNode,std::vector<node>& cList)
{
	 path.push_back(fNode);
	 std::cout<<"getting the path "<<std::endl;
	 int i = 0;
	 while (1)
	 {
	 	int pkey = fNode.getPkey();
	 	//std::cout<<"the parent key ---> "<<pkey<<std::endl;
	 	if (pkey == 0){break;}
	 	std::vector<node>::iterator searchIt = std::find_if(cList.begin(),cList.end(),searchNode(pkey));
	 	fNode = *searchIt;

	 	path.push_back(fNode);

	 }
	
}