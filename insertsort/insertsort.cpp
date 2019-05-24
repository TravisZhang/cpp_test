#include <bits/stdc++.h>

using namespace std;

#define INFI 10000000000

// A: array; p,q,r: index, p <= q < r
void merge(vector<float>& A, int p, int q, int r)
{
	vector<float> L(q-p+1+1);
	vector<float> R(r-q+1);

	for(int i = 0;i < L.size()-1;++i)
		L[i] = A[p+i];
	L[q-p+1] = INFI;

	for(int i = 0;i < R.size()-1;++i)
		R[i] = A[q+i+1];
	R[r-q] = INFI;

	int i = 0,j = 0;
	for(int k = p;k <= r;++k)
		if(L[i] <= R[j])
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}
}

// with out INFI sentry
void merge1(vector<float>& A, int p, int q, int r)
{
	vector<float> L(q-p+1);
	vector<float> R(r-q);

	for(int i = 0;i < L.size();++i)
		L[i] = A[p+i];

	for(int i = 0;i < R.size();++i)
		R[i] = A[q+i+1];

	int i = 0, j = 0;
	bool flag1 = 0, flag2 = 0;
	for(int k = p;k <= r;++k)
	{
		if(i == q-p+1)
		{
			
			A[k] = R[j];
			++j;
			continue;
		}
		else if(j == r-q)
		{
			
			A[k] = L[i];
			++i;
			continue;
		}

		if(L[i] <= R[j])
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}

	}
}

void merge_sort(vector<float>& A, int p, int r)
{
	if(p < r)
	{
		int q = floor((p+r)/2);
		merge_sort(A,p,q);
		merge_sort(A,q+1,r);
		merge1(A,p,q,r);
	}
}

vector<float> my_sort(vector<float> input_list, int type)
{

	cout << "input_list before: ";
	for(int i = 0;i < input_list.size();++i)
	{
		cout << input_list[i] << " ";
	}
	cout << endl;

	// big >> small
	if(type == 0)
	{
		cout << "insert sort big >> small" << endl;
		int i,j;
		for(j = input_list.size()-2;j >= 0;--j)
		{
			float key = input_list[j];
			i = j+1;
			while((i <= input_list.size()-1) && key < input_list[i])
			{
				input_list[i-1] = input_list[i];
				++i;
			}
			input_list[i-1] = key;
		}
	}
	// small << big
	else if(type == 1)
	{
		cout << "insert sort small << big" << endl;
		int i,j;
		for(j = 1;j <= input_list.size()-1;++j)
		{
			float key = input_list[j];
			i = j-1;
			while((i >= 0) && key < input_list[i])
			{
				input_list[i+1] = input_list[i];
				--i;
			}
			input_list[i+1] = key;
		}
	}
	// double direction bubble sort small << big
	else if(type == 2)
	{
		cout << "double direction bubble sort small << big" << endl;
		int i,j,low,high;
		low = 0;
		high = input_list.size()-1;
		while(low < high)
		{
			for(i = low;i < high;++i)
				if(input_list[i]>input_list[i+1])
				{
					float temp = input_list[i];
					input_list[i] = input_list[i+1];
					input_list[i+1] = temp;
				}
			--high;
			for(i = high;i > low;--i)
				if(input_list[i-1]>input_list[i])
				{
					float temp = input_list[i];
					input_list[i] = input_list[i-1];
					input_list[i-1] = temp;
				}
			++low;
		}
	}
	// divide, conquer & merge
	else if(type == 3)
	{
		cout << "divide, conquer & merge small << big" << endl;
		merge_sort(input_list,0,input_list.size()-1);
	}

	// cout << "input_list after: ";
	// for(int i = 0;i < input_list.size();++i)
	// {
	// 	cout << input_list[i] << " ";
	// }
	// cout << endl;

	return input_list;
}

int main(void)
{
	vector<float> input_list,output_list;
	input_list = {0,1,3,5,2,4,9,8,4,3,10,2,7,6,11,3};
	output_list = my_sort(input_list,3);
	// cout << "output_list size: " << output_list.size() << endl;
	cout << "output_list: ";
	for(int i = 0;i < output_list.size();++i)
	{
		cout << output_list[i] << " ";
	}
	cout << endl;
	return 0;
}
