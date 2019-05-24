#include "jump.hpp"

using namespace std;

double mul(double x,double i)
{	
	if(i != 0)
	{
		if(x > i)
			return(x*mul(x-1,i));
		else
			return i;
	}
	else
		return 1;
}

double divide(double stairs)
{
	double len = stairs/2+1;

	double num,i;
	double temp = 0;
	double result = 0;

	for(i = 0;i < len;++i)
	{
		if(i == 0 || i == len-1)
			temp = 1;
		else
		{
			temp = mul(stairs-i,stairs-2*i+1)/mul(i,1);
		}
		cout << "i: " << i << " temp: " << temp << endl; 
		result += temp;
	}

	return result;

}

//time complexity: O(n^n)
int main(void){

	double num1,num2,stairs;
	num1 = 1;
	num2 = 2;
	stairs = 300;
	double result = divide(stairs);
	cout << "result: " << result << endl;

  	return 0;

}