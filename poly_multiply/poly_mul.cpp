#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

// calculate (s+p0)*(s+p1)*...*(s+pn) coef an,an-1,...,a0

typedef pair<double,double> ComplexNum; // real + pure-complex

// calculate complex mutiplication
ComplexNum cal_mul(const ComplexNum& a, const ComplexNum& b) {

	ComplexNum c;
	c.first = a.first*b.first - a.second*b.second; // real
	c.second = a.first*b.second + a.second*b.first; // pure-complex
	return c;
}

ComplexNum cal_sum(const ComplexNum& a, const ComplexNum& b) {

	return ComplexNum(a.first+b.first, a.second+b.second);

}

// complex valued poles
vector<ComplexNum> cal_coefs(const vector<ComplexNum>& p_list) {
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
vector<double> cal_coefs(const vector<double>& p_list) {
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

int Ceil(double n) {
	if(n != (int)n) return (int)n+1;
	else return (int)n;
}

int main(int argc, char* argv[]) {
    
	vector<double> p_list = {1,2,3,4};
	vector<double> coef = cal_coefs(p_list);

	for(int i = 0; i < coef.size(); ++i)
	{
		cout << "a" << i << ": " << coef[i] << endl;
	}
	cout << endl;

	vector<ComplexNum> p_list_c;
	p_list_c.push_back(ComplexNum(1,2));
	p_list_c.push_back(ComplexNum(2,1));
	p_list_c.push_back(ComplexNum(2,3));
	p_list_c.push_back(ComplexNum(3,4));
	vector<ComplexNum> coef_c = cal_coefs(p_list_c);

	for(int i = 0; i < coef_c.size(); ++i)
	{
		cout << "b" << i << ": " << coef_c[i].first << " + " << coef_c[i].second <<"i" << endl;
	}
	cout << endl;

	// bilinear transform s = 2/T * (z-1)/(z+1)
	int degree = p_list_c.size();
	double dt = 1;
	vector<ComplexNum> den_coefs(degree+1);
	vector<ComplexNum> num_coefs(degree+1);
	vector<ComplexNum> p_list_den(degree,ComplexNum(-1,0));
	vector<ComplexNum> p_list_num(degree,ComplexNum(1,0));


	for(int i = degree; i >= 0; --i)
	{
		// calculate denominator coefs
		vector<ComplexNum> temp = cal_coefs(p_list_den);
		for(int j = degree; j >= 0; --j)
		{
			den_coefs[j] = cal_sum(den_coefs[j], cal_mul(temp[j],cal_mul(ComplexNum(pow(2.0/dt,i),0),coef_c[i])) );
		}

		if(i > 0)
		{
			p_list_den[i-1] = ComplexNum(1,0);
		}
	}

	// calculate numerator coefs
	num_coefs = cal_coefs(p_list_num);

	for(int i = 0; i < den_coefs.size(); ++i)
	{
		cout << "den" << i << ": " << den_coefs[i].first << " + " << den_coefs[i].second <<"i" << endl;
	}
	cout << endl;

	for(int i = 0; i < den_coefs.size(); ++i)
	{
		cout << "num" << i << ": " << num_coefs[i].first << " + " << num_coefs[i].second <<"i" << endl;
	}
	cout << endl;

	cout << Ceil(1) << endl;

    return 0;
}