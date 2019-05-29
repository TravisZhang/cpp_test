#ifndef FILTERS_H
#define FILTERS_H

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



namespace xmotors
{
namespace filters
{

using namespace std;

typedef pair<double,double> ComplexNum; // real + pure-complex

class DigitalFilter
{
public:
	DigitalFilter(){}
	~DigitalFilter(){}

	Init();

private:

	ComplexNum CalMul(const ComplexNum& a, const ComplexNum& b);
	ComplexNum CalSum(const ComplexNum& a, const ComplexNum& b);
	vector<ComplexNum> CalCoefs(const vector<ComplexNum>& p_list); // for complex poles
	vector<double> CalCoefs(const vector<double>& p_list); // for real poles
	
};


} // namespace filters
} // namespace xmotors

#endif