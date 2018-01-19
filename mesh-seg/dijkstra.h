#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

class Dijkstra
{
public:
	void init(int size=100);//��ʼ��Ϊsize���㣬�߱����
	void work(int index);//��index��ʼ�ܵ�Դ���·
	void work(int startIndex,int endIndex); //��startIndex�����·���ܵ�endIndexΪֹ
	void add(int node1,int node2,double weight,bool flag=false);//���һ��node1��node2��ȨֵΪweight�ıߣ�flag=true���������
	double getDist(int node); //��ȡnode��dist
	int getFather(int node); //��ȡnode��father
private:
	struct node
	{
		int index;
		double dist;
		int father;
		bool operator < (const node &a) const
		{
			return dist>a.dist;
		}
		node(int index=-1,double dist=-1,int father=-1)
		{
			this->index = index;
			this->dist = dist;
			this->father = father;
		}
	};
	vector<vector<int> > v; //��
	vector<vector<double> > w; //��Ȩ
	priority_queue<node> pq;
	vector<double> dist;
	vector<int> father;
	int n;
};
#endif