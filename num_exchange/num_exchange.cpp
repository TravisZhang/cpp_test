#include <vector>
#include <iostream>
#include <string>
using namespace std;

// https://www.zhihu.com/collection/169026899?page=4

int main(int argc, char* argv[])
{

	int n = 6;
	vector<int> list(n,0);
	if(n % 2 == 1) {
		int mid = (int)(n/2.0f)+1;
		// cout << mid << endl;
		for(int i = 0; i < mid-1; ++i)
		{
			list[i*2] = mid-i;
			list[i*2+1] = mid+1+i; 
		}
		list.back() = 1; 
	}
	else {
		int mid = n/2;
		for(int i = 0; i < mid; ++i)
		{
			list[i*2] = mid-i;
			list[i*2+1] = mid+1+i; 
		}

	}

	cout << "result: ";
	for (const auto& num: list)
	{
		cout << num << ' ';
	}
	cout << endl;
    return 0;
}