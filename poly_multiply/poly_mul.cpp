#include <vector>
#include <iostream>
using namespace std;

// calculate (s+p0)*(s+p1)*...*(s+pn) coef an,an-1,...,a0

vector<double> cal_coefs(vector<double> p_list)
{
	int n = p_list.size();
	int size_coef = n + 1;
	vector<double> coef_list(size_coef,0);
	coef_list[1] = 1;
	coef_list[0] = p_list[0];

	for(int i = 0; i < n-1; ++i)
	{
		for(int j = i+2; j > 0; --j)
		{
			coef_list[j] = coef_list[j-1]
		}

		coef_list[0] = p_list[i+1]*coef_list[1];
		for(int j = 1; j < i+2; ++j)
		{
			coef_list[j] += p_list[i+1]*coef_list[j+1];
		}

	}

	return coef_list;

}

int main(int argc, char* argv[])
{
    

    return 0;
}