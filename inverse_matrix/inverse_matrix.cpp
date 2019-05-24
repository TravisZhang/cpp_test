#include <bits/stdc++.h>

using namespace std;

#define INFI 10000000000

// s = 0 swap row, s = 1, swap coln
void swap(vector<double>& current_list, int i, int j, int s)
{
	int n = sqrt(current_list.size());
	if(s == 0)
	{
		double temp = 0;
		for(int m = 0;m < n;++m)
		{
			// temp = current_list[i*n+m];
			// current_list[i*n+m] = current_list[j*n+m];
			// current_list[j*n+m] = temp;
			std::iter_swap(current_list.begin() + i*n+m, current_list.begin() + j*n+m);
		}
	}
	else
	{
		double temp = 0;
		for(int m = 0;m < n;++m)
		{
			// temp = current_list[m*n+i];
			// current_list[m*n+j] = current_list[m*n+i];
			// current_list[m*n+i] = temp;
			std::iter_swap(current_list.begin() + m*n+i, current_list.begin() + m*n+j);
		}
	}
}

int gause_inverse(vector<double>& input_list, vector<double>& output_list)
{
	// input : square matrix
	int n = sqrt(input_list.size());
	output_list.resize(n*n,0);

	// output : initialized as identity matrix
	for(int i = 0;i < n;++i)
	{
		output_list[i*n+i] = 1;
	}

	for(int i = 0;i < n;++i)
	{
		// step 1: find pivot element (max abs value in coln)
		int p = i;
		double p_e = input_list[p*n+p];
		for(int j = i+1;j < n;++j)
		{
			if(fabs(input_list[j*n+i]) > fabs(p_e))
			{
				p = j;
				p_e = input_list[j*n+i];
			}
		}

		// if pivot == 0, no inverse matrix exists
		if(p_e == 0)
		{
			return 0;
		}

		// if pivot not at i, swap two rows
		if(p != i)
		{
			swap(input_list, i, p, 0);
			swap(output_list, i, p, 0);
		}

		// eliminate other elements in this coln
		double factor = input_list[i*n+i];
		for(int j = 0;j < n;++j)
		{
			input_list[i*n+j] /= factor;
			output_list[i*n+j] /= factor;
		}

		for(int j = 0;j < n;++j)
		{
			if(j != i)
			{
				factor = input_list[j*n+i];
				for(int k = 0;k < n;++k) // pay special attention to k = 0, because we need all elemets in row to change!!!!
				{
					input_list[j*n+k] -= factor * input_list[i*n+k];
					output_list[j*n+k] -= factor * output_list[i*n+k];
				}
			}
		}
	}

	return 1;
}


void print_matrix(vector<double>& m)
{
	cout << "----- printing matrix -----" << endl;
	int n = sqrt(m.size());

	for(int i = 0;i < n;++i)
	{
		for(int j = 0;j < n;++j)
		{
			int index_temp = i*n+j;
			printf(" %.8f ",m[index_temp]);
		}
		cout<<endl;
	}

	cout << "done !!!" << endl;
}

int main(void)
{
	vector<double> A,B;
	int n = 5;

	A.resize(n*n);
	B.resize(n*n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int index_temp = i*n+j;
			/* generate random number between 1 and 10: */
			A[index_temp] = rand() % 10 + 1;
			// B[index_temp] = rand() % 10 + 1;
		}
	}

	print_matrix(A);

	int result = gause_inverse(A,B);
	cout << "result is " << result << endl;

	print_matrix(B);
	print_matrix(A);

	return 0;
}
