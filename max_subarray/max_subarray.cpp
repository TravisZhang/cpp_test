#include <bits/stdc++.h>

using namespace std;

vector<float> find_max_crossing_subarray(vector<float>& A, int low, int mid, int high)
{
	float left_sum = A[mid-1];
	float sum = 0;
	int max_left = mid-1; // index

	for(int i = mid-1;i >= low;--i)
	{
		sum += A[i];
		if(sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	float right_sum = A[mid];
	sum = 0;
	int max_right = mid;

	for(int i = mid;i <= high;++i)
	{
		sum += A[i];
		if(sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}

	vector<float> R(3);
	R[0] = float(max_left);
	R[1] = float(max_right);
	R[2] = left_sum + right_sum;
	return R;
}

vector<float> find_max_subarray(vector<float>& A, int low, int high)
{
	if(high == low)
	{
		// A has only one element
		vector<float> R(3);
		R[0] = float(low);
		R[1] = float(high);
		R[2] = A[low];
		return R;
	}
	else
	{
		int mid = floor((low+high)*0.5);
		vector<float> P(3);
		vector<float> L = find_max_subarray(A,low,mid); P[0] = L[2];
		vector<float> R = find_max_subarray(A,mid+1,high); P[1] = R[2];
		vector<float> M = find_max_crossing_subarray(A,low,mid,high); P[2] = M[2];

		sort(P.begin(), P.end(), greater<float>());
		if(P[0] == L[2])
		{
			return L;
		}
		else if(P[0] == R[2])
		{
			return R;
		}
		else
		{
			return M;
		}
	}
}

int main()
{
	vector<float> input_list,R;
	input_list = {0,-1,-3,5,-2,4,-9,8,-4,3,10,-2,7,6,-11,3};
	R = find_max_subarray(input_list,0,input_list.size()-1);
	cout << "max_left: " << R[0] << endl;
	cout << "max_right: " << R[1] << endl;
	cout << "max_sum: " << R[2] << endl;

    return 0;
}
