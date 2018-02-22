#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <strstream>
#include <ostream>

using namespace std;
ifstream input("input.txt");
long long N, C, D;
long long a[100000][4];
long long b[100000][4];
int case_number = 0;
long long chosen_machine;

long long max(long long v1, long long v2)
{
	// returns the maximume value between 2 values
	if (v1 > v2)
		return v1;
	else
		return v2;
}

long long f_recursive(long long cash, long long i, long long i_chosen, int e)
{
	if (i == N - 1)
	{
		if (e == 0) //we dont buy the current machine
		{
			return (cash + (D-b[i][0]+1)*b[i_chosen][3] );
		}
		else //e==1 and we will buy the current machine
		{
			if (cash < b[i][1]) //we cant buy it
			{
				if (i_chosen == -1)
					return cash;
				else
					return (cash + (D - b[i][0] + 1)*b[i_chosen][3]);
			}
			cash = cash - b[i][1] + b[i][2];
			return (cash + (D - b[i][0])*b[i][3]);
		}
	}

	if (e == 1) //we are going to buy the machine
	{
		if (cash < b[i][1])
		{
			//we cant buy it so we keep the current cash and go to next machine
			return max(f_recursive(cash, i + 1, i_chosen, 1), f_recursive(cash, i + 1, i_chosen, 0));
		}
		cash = cash - b[i][1] + b[i][2] + (b[i + 1][0] - b[i][0] - 1)*b[i][3];
		return max(f_recursive(cash, i + 1, i, 1), f_recursive(cash, i + 1, i, 0));
	}
	else // e==0 and we wont buy the machnie
	{
		if (i_chosen == -1) // if we did not buy any machine before (we still own no machine)
		{
			return max(f_recursive(cash, i + 1, i_chosen, 1), f_recursive(cash, i + 1, i_chosen, 0));
		}
		cash = cash + (b[i + 1][0] - b[i][0])*b[i_chosen][3];
		return max(f_recursive(cash, i + 1, i_chosen, 1), f_recursive(cash, i + 1, i_chosen, 0));
	}
}

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

int sort_a()
{
	long long checked[100000];
	for (long long i = 0; i < N; i++)
	{
		long long max = 999999999999999999;
		long long j_chosen;
		for (long long j = 0; j < N; j++)
		{
			if (a[j][0] <= max && checked[j]!=1)
			{
				max = a[j][0];
				j_chosen = j;
			}
		}
		b[i][0] = a[j_chosen][0];
		b[i][1] = a[j_chosen][1];
		b[i][2] = a[j_chosen][2];
		b[i][3] = a[j_chosen][3];
		checked[j_chosen] = 1;
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

		if (N==0) // there is no machine, so simply output the dollar we have
			cout << "Case " << ++case_number << ": " << C << "\n";
		else
		{
			sort_a();
			cout << "Case " << ++case_number << ": " << max(f_recursive(C, 0, -1, 0), f_recursive(C, 0, -1, 1)) << "\n";
		}
	}		
	
	input.close();
	cout << "Finished, please press Enter...";
	getchar();
	return 0;
}
