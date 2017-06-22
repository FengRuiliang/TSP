// TSP.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
#define MINVALUE -1e6;
#define MAXVALUE 1E6;
int Num;
float* cost_[25][25];
float pencost[25];
struct CCustomer
{
	int id_;
	float x_;
	float y_;
};

float row,col, low_bound_;
bool SortBySelectd(const pair<int,bool> &v1, const pair<int,bool> &v2)
{
	return v1.second>v2.second;//Ωµ–Ú≈≈¡–  
}
int Sum(int array_[])
{
	int s = 0;
	for (int i=0;i<25;i++)
	{
		s += array_[i];
	}
}
int main()
{
	RowReduction(cost_);
	ColReduction(cost_);
	low_bound_ = row + col;
	int selected_[25] = { 0 };
	while (Sum(selected_)<25)
	{
		for (int i=0;i<Num;i++)
		{
			if (!selected_[i])
			{
				edgecost[i] = CheckBounds(k, i, cost_);
			}
		}
		float min_ = 1e6;
		for (int i=1;i<25;i++)
		{
			if (!selected_[i])
			{
				if (edgecost[i]<min_)
				{
					min_ = edgecost[i];
					k = i;
				}
			}
		}
		selected_[k] = 1;
		for (int p=1;p<25;p++)
		{
			*cost_[j][p] = 1e6;
		}
		for (int p=1;p<25;p++)
		{
			*cost_[p][k] = 1e6;
		}
		cost_[k][j] = 1e6;
		RowReduction(cost_);
		ColReduction(cost_);
	}
    return 0;
}

void LoadFile()
{
	fstream in_;
	vector<CCustomer> customers_;
	in_.open("tsp.txt");
	while (!in_.eof())
	{
		CCustomer c;
		in_ >> c.id_ >> c.x_ >> c.y_;
		customers_.push_back(c);
	}
	Num = customers_.size();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j)
			{
				*cost_[i][j] = 1e6;
			}
			else
			{
				*cost_[i][j] = sqrtf((customers_[i].x_ - customers_[j].x_)*(customers_[i].x_ - customers_[j].x_) +
					(customers_[i].y_ - customers_[j].y_)*(customers_[i].y_ - customers_[j].y_));
			}
		}
	}
}


float CheckBounds(int st,int des,float* cost_local_[25][25])
{
	pencost[0] = low_bound_;
	float* reduced_[25][25];

	for (size_t i = 0; i < 25; i++)
	{
		for (size_t j=0;j<25;j++)
		{
			*reduced_[i][j] = *cost_local_[i][j];
		}
	}
	for (size_t j=0;j<25;j++)
	{
		*reduced_[st][j] = 1e6;
	}
	for (size_t i=0;i<25;i++)
	{
		*reduced_[i][st] = 1e6;
	}
	
	*reduced_[des][st] = 1e6;
	RowReduction(reduced_);
	ColReduction(reduced_);
	pencost[des] = pencost[st] + row + col + *cost_[st][des];
	return pencost[des];
}
float RowMin(int i)
{
	float min_ = *cost_[i][0];
	for (size_t j;j<25;j++)
	{
		min_ = min_ < *cost_[i][j] ? min_ : *cost_[i][j];
	}
	return min_;
}
float ColMin(int j)
{
	float min_ = *cost_[0][j];
	for (size_t i; i < 25; i++)
	{
		min_ = min_ < *cost_[i][j] ? min_ : *cost_[i][j];
	}
	return min_;
}
void RowReduction(float* matrix_[25][25])
{
	row = 0;
	for (size_t i=0;i<25;i++)
	{
		float rmin_ = RowMin(i);
		if (rmin_!=1e6)
		{
			row = row + rmin_;
		}
		for (size_t j=0;j<25;j++)
		{
			if (*matrix_[i][j]!=1e6)
			{
				*matrix_[i][j] = *matrix_[i][j] - rmin_;
			}
		}
	}
}
void ColReduction(float* matrix_[25][25])
{
	col = 0;
	for (size_t j = 0; j < 25; j++)
	{
		float cmin_ = ColMin(j);
		if (cmin_ != 1e6)
		{
			col = col + cmin_;
		}
		for (size_t i = 0; i < 25; i++)
		{
			if (*matrix_[i][j] != 1e6)
			{
				*matrix_[i][j] = *matrix_[i][j] - cmin_;
			}
		}
	}
}
