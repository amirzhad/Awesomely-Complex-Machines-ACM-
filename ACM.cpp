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
int N, C, D;
int a[100][4];
int profit[100];
int case_number = 0;
int read_case()
{
	//reads each case and corresponding N C D and also the machines details to array a
	string line;
	input >> N >> C >> D;
	for (int i = 0; i < N; i++)
	{
		input >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
	}
	return 1;
}

int count_highest_profit()
{
	//computes the primary highest profit based on the machines details and available dollars (C)
	for (int i = 0; i < N; i++)
	{
		if (C < a[i][1])
			profit[i] = 0;
		else
			profit[i] = C - a[i][1] + a[i][2] + (D-a[i][0])*a[i][3];
	}

	return 1;
}
int find_best_profit()
{
	// finds the highest profit machine
	int max = 0;
	int max_index = -1;
	for (int i = 0; i < N; i++)
	{
		if (profit[i] > max)
		{
			max = profit[i];
			max_index = i;
		}
	}
	return max_index;
}

int coming_profit(int current_machine_index)
{
	int buget = C - a[current_machine_index][1] + a[current_machine_index][2];
	// computes the profit if we choose other machines
	for (int i = 0; i < N; i++)
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
int max_profit()
{
	//finds the most accessable profit
	if (N == 0)
		return C; //if there is not machine, we simply save the amout we have
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		if (profit[i] > max)
			max = profit[i];
	}
	if (C > max)
		return C;
	return max;
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
		int chosen_machine = find_best_profit();
		coming_profit(chosen_machine);

		cout << "Case " << ++case_number << ": " << max_profit() << "\n";
	}		
	
	input.close();
	cout << "Finished, please press Enter...";
	getchar();
	return 0;
}
