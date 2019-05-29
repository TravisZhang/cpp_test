#include "filters.h"

namespace xmotors
{
namespace filters
{


// calculate (s+p0)*(s+p1)*...*(s+pn) coef an,an-1,...,a0

// calculate complex mutiplication
ComplexNum DigitalFilter::CalMul(const ComplexNum& a, const ComplexNum& b) {

	ComplexNum c;
	c.first = a.first*b.first - a.second*b.second; // real
	c.second = a.first*b.second + a.second*b.first; // pure-complex
	return c;
}

// calculate complex sum
ComplexNum DigitalFilter::CalSum(const ComplexNum& a, const ComplexNum& b) {

	return ComplexNum(a.first+b.first, a.second+b.second);

}

// complex valued poles
vector<ComplexNum> DigitalFilter::CalCoefs(const vector<ComplexNum>& p_list) {
	int n = p_list.size();
	if(n == 0)
	{
		return vector<ComplexNum>(1,ComplexNum(1,0));
	}
	else
	{
		int size_coef = n + 1;
		vector<ComplexNum> coef_list(size_coef);
		coef_list[1] = ComplexNum(1,0);
		coef_list[0] = p_list[0];
	 
	 	for(int i = 1; i < n; ++i)
		{
			for(int j = i+1; j > 0; --j)
			{
				coef_list[j] = coef_list[j-1];
			}

			coef_list[0] = cal_mul(p_list[i], coef_list[1]);
			for(int j = 1; j < i+1; ++j)
			{
				coef_list[j] = cal_sum(coef_list[j], cal_mul(p_list[i], coef_list[j+1]));
			}

		}

		return coef_list;

	}
}


// real valued poles
vector<double> DigitalFilter::CalCoefs(const vector<double>& p_list) {
	int n = p_list.size();
	if(n == 0)
	{
		return vector<double>(1,1);
	}
	else
	{
		int size_coef = n + 1;
		vector<double> coef_list(size_coef,0);
		coef_list[1] = 1;
		coef_list[0] = p_list[0];

		for(int i = 1; i < n; ++i)
		{
			for(int j = i+1; j > 0; --j)
			{
				coef_list[j] = coef_list[j-1];
			}

			coef_list[0] = p_list[i]*coef_list[1];
			for(int j = 1; j < i+1; ++j)
			{
				coef_list[j] += p_list[i]*coef_list[j+1];
			}

		}

		return coef_list;
	}

}




} // namespace filters
} // namespace xmotors