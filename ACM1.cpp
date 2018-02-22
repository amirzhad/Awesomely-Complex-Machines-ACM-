/*
Author:
    Amir Zhad
    2018-02-21
Description:
    The director of Awesomely Complex Machines (ACM) whose task is to maximize the amount of money that ACM makes during the restructuring.
Source:
    https://github.com/amirzhad/Awesomely-Complex-Machines-ACM-.git
Compile: (Ubuntu)
    g++ -std=gnu++11 ACM.cpp -o CPP.exe
Run: (Windows)
    ACM.exe
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <strstream>
#include <ostream>

using namespace std;
ifstream input("input.txt");
long long N, C, D;
long long a[100000][4];
long long profit[100000];
int case_number = 0;
long long chosen_machine;

int read_case()
{
	//reads each case and corresponding N C D and also the machines details to array a
	string line;
	input >> N >> C >> D;
	for (long long i = 0; i < N; i++)
	{
		input >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
	}
	return 1;
}

int count_highest_profit()
{
	//computes the primary highest profit based on the machines details and available dollars (C)
	for (long long i = 0; i < N; i++)
	{
		if (C < a[i][1])
			profit[i] = 0;
		else
			profit[i] = C - a[i][1] + a[i][2] + (D-a[i][0])*a[i][3];
	}

	return 1;
}

long long find_best_profit()
{
	// finds the highest profit machine
	long long max = 0;
	long long max_index = -1;
	for (long long i = 0; i < N; i++)
	{
		if (profit[i] > max)
		{
			max = profit[i];
			max_index = i;
		}
	}
	return max_index;
}

int coming_profit(long long current_machine_index)
{
	long long buget = C - a[current_machine_index][1] + a[current_machine_index][2];
	// computes the profit if we choose other machines
	for (long long i = 0; i < N; i++)
	{
		if (a[i][0] <= a[current_machine_index][0])
		{
			continue;
		}
		if (((a[i][0] - a[current_machine_index][0] - 1)*a[current_machine_index][3] + buget) >= a[i][1]) // can we buy it?
		{
			profit[i] = (a[i][0] - a[current_machine_index][0] - 1)*a[current_machine_index][3] + buget + (D-a[i][0])*a[i][3] + a[i][2] - a[i][1];
		}		
	}
	return 1;
}
long long max_profit()
{
	//finds the most accessable profit
	if (N == 0 || chosen_machine==-1)
		return C; //if there is not machine, we simply save the amout we have
	long long max = 0;
	for (long long i = 0; i < N; i++)
	{
		if (profit[i] > max)
			max = profit[i];
	}
	if (C > max)
		return C;
	return max;
}

long long find_better()
{
	long long buget = C - a[chosen_machine][1] + a[chosen_machine][2];
	long long tmp;
	for (long long i = 0; i < chosen_machine; i++)
	{
		tmp = C - a[i][1] + a[i][2] + (a[chosen_machine][0] - a[i][0])*a[chosen_machine][3];
		if (tmp > max_profit())
			profit[chosen_machine] = tmp;
	}
	return 1;
}

int main()
{
	int exit_condition = 0;
	while (!exit_condition)
	{
		read_case();
		if (N == 0 && C == 0 && D == 0)
		{
			exit_condition = 1;
			continue;
		}
		
		count_highest_profit();
		chosen_machine = find_best_profit();
		find_better();
		coming_profit(chosen_machine);

		cout << "Case " << ++case_number << ": " << max_profit() << "\n";
	}		
	
	input.close();
	cout << "Finished, please press Enter...";
	getchar();
	return 0;
}
