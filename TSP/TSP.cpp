// TSP.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#define MINVALUE -1e6;
#define MAXVALUE 1E6;
float cost_matrix_[25][25];
struct customer
{
	int id_;
	float x_;
	float y_;
};
int Compute_Upbound(int v, int j, int len)
{
	if (j == 25) return len + graph[v][1];
	int minlen = INF, pos;
	for (int i = 1; i <= n; i++)
	{
		//采用贪心算法取权值最小的边  
		if (used[i] == 0 && minlen > graph[v][i])
		{
			minlen = graph[v][i];
			pos = i;
		}
	}
	used[pos] = 1;
	return get_up_helper(pos, j + 1, len + minlen);
}
int main()
{
	fstream in_;
	vector<customer> customers_;
	in_.open("tsp.txt");
	while (!in_.eof())
	{
		customer c;
		in_ >> c.id_ >> c.x_ >> c.y_;
		customers_.push_back(c);
	}
	
	for (int i=0;i<25;i++)
	{
		for (int j=0;j<25;j++)
		{
			if (i == j)
			{
				cost_matrix_[i][j] = 1e6;
			}
			else
			{
				cost_matrix_[i][j] = sqrtf((customers_[i].x_ - customers_[j].x_)*(customers_[i].x_ - customers_[j].x_) +
					(customers_[i].y_ - customers_[j].y_)*(customers_[i].y_ - customers_[j].y_));
			}
		}
	}
    return 0;
}

