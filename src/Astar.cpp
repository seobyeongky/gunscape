//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Astar.cpp
//
// ����: Astar�˰���
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <list>
#include "Astar.h"
#include "map_make.h"

searchnode** astar_node = NULL;

int PathCost(const coord_int& start,const coord_int&  goal)
{
	return abs(start.x - goal.x)+abs(start.y - goal.y);
}


void priqueue_push(list<searchnode*>& queues,searchnode* data)
{
	list<searchnode*>::iterator it;
	for(it = queues.begin();it != queues.end();it++)
	{
		if((*it)->tc>data->tc)
			break;
	}
	queues.insert(it,data);
	data->opcl |= 1;
}

bool list_search(list<searchnode*>& queues,searchnode* data)
{
	list<searchnode*>::iterator it;
	for(it = queues.begin();it != queues.end();it++)
	{
		if((*it)->pos == data->pos)
			return true;
	}
	return false;
}

bool PathSearch(const coord_int& start,const coord_int& goal, stack<coord_int>& will_move, Mini_Map& map, int limit_)
{
	coord_int ano_goal = start;
	bool is_move = map.isMove(goal.x,goal.y);
	if(!(is_move))
	{
		return false;
	}

	{
		bool not_good = true;
		rect_iterator it(goal,1,1);
		for(;!it.end();it++)
		{
			if((*it) ==	goal)
				continue;
			if(map.isMove(it->x,it->y))
			{
				not_good = false;
				break;
			}
		}
		if(not_good)
			return false;
	}

	int heuristic = 10;
	list<searchnode*> Open;
	for(int x=0;x<DG_MAX_X;x++)
	{
		for(int y=0;y<DG_MAX_Y;y++)
		{
			astar_node[x][y].opcl = 0;
		}
	}

	priqueue_push(Open,astar_node[start.x][start.y].Set(start,0,PathCost(start,goal),NULL));//��ŸƮ������ ���� Ǫ��

	int move_ = 0;//������ Ƚ��.(�̰��� limit_�� ������ ������ �����. ���� ���� Ž���� ���н� �����̴°� �ƿ� �����Ѵ�.
	while(!Open.empty())
	{
		searchnode* node = Open.front();
		Open.pop_front();
		node->opcl &= ~1;
		node->opcl |= 2;
		if(limit_ == move_) //ã�� ����(�Ѱ� �����Ӻ��� �Ÿ��� �� �־���.
			break;
		if(node->pos == goal) //����
		{
			searchnode* path = node;
			while(path && path->pos != start)
			{
				will_move.push(path->pos);
				path = path->parent;
			}
			return true;
		}
		else //���ο� ������ ����
		{
			rect_iterator it(node->pos,1,1);
			for(;!it.end();it++)
			{
				if(it->x<0 || it->x>= DG_MAX_X || it->y<0 || it->y>= DG_MAX_Y)
					continue;

				if((*it) == node->pos)
					continue;
				if(it.isdiagonal())
					continue;
				searchnode* newnode = &astar_node[it->x][it->y];
				int newcost = node->cfs+1;
				bool is_open = (newnode->opcl & 1);
				int is_close = (newnode->opcl & 2);
				bool is_move = map.isMove(it->x,it->y);
				if(!is_move)
				{
					continue;
				}
				else if((is_open || is_close) && (newnode->cfs <= newcost))
				{
					continue;
				}
				//else
				{	
					move_++;
					newnode->Set(coord_int(it->x,it->y),newcost, heuristic*PathCost(coord_int(it->x,it->y),goal),node);
					if(is_close)
					{
						newnode->opcl &= ~2;
					}
					if(is_open)
					{
						Open.remove(newnode);
						priqueue_push(Open,newnode);
					}
					else
					{
						priqueue_push(Open,newnode);
					}
				}
			}
		}
	}
	return false;
}




