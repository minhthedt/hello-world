#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

#define MAX_LINE		(256)
#define MAX_ERROR		(3)
#define ONE_SIDE_TH		(MAX_ERROR+1)
#define MAX_SET_COUNT	(ONE_SIDE_TH * 2)
#define MIN_VALUE		(-100000000)
#define MAX_VALUE		(100000000)

typedef struct {
	int x;
	int y;
}POINT;


FILE* pin = NULL;
FILE* pout = NULL;

vector<POINT> point_vector;
list<multimap<int,int> > max_x_list;
list<multimap<int,int> > max_y_list;
list<multimap<int,int> > min_x_list;
list<multimap<int,int> > min_y_list;

bool comp_less(const int a,const int b)
{
	return a > b;
}

bool comp_larger(const int a, const int b)
{
	return a < b;
}

typedef bool (*COMP)(const int a, const int b);

void push_to_list(list<multimap<int,int> >& l,int idx,bool bX,COMP f)
{
	// x축 혹은 y축에서 최대 혹은 최소값에 해당하는 값을 4개까지 기억한다.
	int point_value = 0;
	int another_value = 0;
	if(bX)
	{
		point_value = point_vector[idx].x;
		another_value = point_vector[idx].y;
	}
	else
	{
		point_value = point_vector[idx].y;
		another_value = point_vector[idx].x;
	}

	list<multimap<int,int> >::iterator it = l.begin();
	
	for(;it!=l.end();it++)
	{
		int point_vector_index = (*(*it).begin()).second;
		int point_target_value = 0;
		if(bX)
		{
			point_target_value = point_vector[point_vector_index].x;
		}
		else
		{
			point_target_value = point_vector[point_vector_index].y;
		}

		if( point_target_value == point_value)
		{
			(*it).insert(multimap<int,int>::value_type(another_value,idx));
			if( (*it).size() > MAX_SET_COUNT)
			{
				int i=0;
				multimap<int,int>::iterator m_it = (*it).begin();
				for(;m_it!=(*it).end();m_it++,i++)
				{
					if(i==ONE_SIDE_TH)
					{
						(*it).erase(m_it);
						break;
					}
				}
			}
			return;
		}
		else if( f(point_target_value, point_value) )
		{
			multimap<int,int> m;
			m.insert(multimap<int,int>::value_type(another_value,idx));
			l.insert(it,m);
			break;
		}
	}
	if(it==l.end() && l.size()<4)
	{
		multimap<int,int> m;
		m.insert(multimap<int,int>::value_type(another_value,idx));
		l.push_back(m);
	}
	else if(l.size()>4)
	{
		l.pop_back();
	}
}

void push_max_x(int idx)
{
	push_to_list(max_x_list,idx,true,comp_larger);
}


void push_max_y(int idx)
{
	push_to_list(max_y_list,idx,false,comp_larger);
}

void push_min_x(int idx)
{
	push_to_list(min_x_list,idx,true,comp_less);
}


void push_min_y(int idx)
{
	push_to_list(min_y_list,idx,false,comp_less);
}

void push(int idx)
{
	// 상하,좌우로 각각 최소값 혹은 최대값을 4개씩 기억한다. 
	push_max_x(idx);
	push_max_y(idx);
	push_min_x(idx);
	push_min_y(idx);
}

void clear_vector()
{
	point_vector.clear();
	max_x_list.clear();
	max_y_list.clear();
	min_x_list.clear();
	min_y_list.clear();
}

void merge_to_set(set<int>& s,list<multimap<int,int> >& l)
{
	list<multimap<int,int> >::iterator it;
	for(it=l.begin();it!=l.end();it++)
	{
		multimap<int,int>::iterator m_it;
		for(m_it=(*it).begin();m_it!=(*it).end();m_it++)
		{
			s.insert((*m_it).second);
		}
	}
}

void merge_to_vector(vector<int>& v,set<int> s)
{
	v.resize(s.size());
	
	int i=0;
	for(set<int>::iterator it = s.begin();it!=s.end();it++,i++)
	{
		v[i] = *it;
	}

	//printf("\t%d\n",v.size());
}

int max_dist_from_set(set<int> s)
{
	// 주어진 set에서 수직 혹은 수평의 최대 거리를 구한다.
	int max_x = MIN_VALUE;
	int min_x = MAX_VALUE;
	int max_y = MIN_VALUE;
	int min_y = MAX_VALUE;

	int i = 0;

	for(set<int>::iterator it = s.begin();it!=s.end();it++,i++)
	{
		int x = point_vector[(*it)].x;
		int y = point_vector[(*it)].y;

		if(max_x<x)
			max_x = x;
		if(min_x>x)
			min_x = x;
		if(max_y<y)
			max_y = y;
		if(min_y>y)
			min_y = y;
	}
	
	if(max_x-min_x>max_y-min_y)
		return max_x-min_x;
	return max_y-min_y;
}

int brute_force_solve()
{
	// merge to set
	set<int> s;
	merge_to_set(s,max_x_list);
	merge_to_set(s,min_x_list);
	merge_to_set(s,max_y_list);
	merge_to_set(s,min_y_list);

	vector<int> v;

	merge_to_vector(v,s);

	int min_dist = MAX_VALUE * 2;

	// 각각의 조합을 제거하고 정사각형을 구하고 그 중 최소를 취한다.
	for(unsigned int i=0;i<v.size()-2;i++)
	{
		for(unsigned int j=0;j<v.size()-1;j++)
		{
			for(unsigned int k=0;k<v.size();k++)
			{
				set<int> temp_set = s;
				temp_set.erase(v[i]);
				temp_set.erase(v[j]);
				temp_set.erase(v[k]);

				int res = max_dist_from_set(temp_set);

				if(min_dist>res)
					min_dist = res;
			}
		}
	}

	return min_dist;
}

void print_list(list<multimap<int,int> >& l)
{
	list<multimap<int,int> >::iterator it;

	for(it=l.begin();it!=l.end();it++)
	{
		multimap<int,int>::iterator m_it;
		int n=0;
		for(m_it=(*it).begin();m_it!=(*it).end();m_it++,n++)
		{
			int idx = (*m_it).second;
			//printf("%d : [%d] %d %d\n",n,idx, point_vector[idx].x, point_vector[idx].y);
			fprintf(pout,"%d : [%d] %d %d\n",n,idx, point_vector[idx].x, point_vector[idx].y);
		}
	}
}

int main(int __argc,char* __argv[])
{
	int T = 0;
	int N = 0;
	char* input_file_name = "C-large.in";

	if (2 <= __argc)
	{
		input_file_name = __argv[1];
	}

	char line[MAX_LINE] = { 0 };
	int nCount = 0;
	pin = fopen(input_file_name, "r");
	pout = fopen("out.txt", "w");

	fscanf(pin,"%d\n",&T);

	while(T--)
	{
		//printf("%d\n",T);
		int N = 0;
		fscanf(pin,"%d\n",&N);
		clear_vector();
		point_vector.resize(N);
		// 주어진 입력에서 가능한 최소한의 point만을 취하고,
		for(int i=0;i<N;i++)
		{
			POINT p;
			fscanf(pin,"%d %d\n",&p.x,&p.y);
			point_vector[i] = p;

			push(i);
		}

		
		//fprintf(pout,"max_x_list\n");
		//print_list(max_x_list);
		//
		//fprintf(pout,"min_x_list\n");
		//print_list(min_x_list);
		//
		//fprintf(pout,"max_y_list\n");
		//print_list(max_y_list);
		//
		//fprintf(pout,"min_y_list\n");
		//print_list(min_y_list);

		// brute force로 결과를 계산한다.
		int res = brute_force_solve();
		fprintf(pout,"%d\n",res);
		printf("%d\n",res);
	}

	fclose(pin);
	fclose(pout);
}
