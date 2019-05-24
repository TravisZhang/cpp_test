#include "num.hpp"

using namespace std;

string num_multiply(string num1, string num2)
{
	string result;

	int i,j,len,len1,len2,carry,c_temp;
	vector <int> a,c;
	vector < vector<int> > b;


	len1 = num1.size();
	len2 = num2.size();

	len = len1 + len2;

	b.reserve(len2);
	b.resize(len2);
	for(i = 0;i < len2;++i)
	{
		b[i].reserve(len);
		b[i].resize(len,0);
	}

	for(i = 0;i < len1;++i)
	{
		for(j = 0;j < len2;++j)
		{
			// cout << (num1[len1-1 - i]-'0')*(num2[len2-1 - j]-'0') << endl;
			a.push_back((num1[len1-1 - i]-'0')*(num2[len2-1 - j]-'0'));
		}
	}

	for(i = 0;i < len2;++i)
	{
		for(j = 0;j < len1;++j)
		{
			b[i][len-1-j-i] = a[len2*j + i];
		}
	}

	c.reserve(len);
	c.resize(len,0);

	carry = 0;
	for(i = 0;i < len;++i)
	{
		for(j = 0;j < len2;++j)
		{
			c[len-1 -i] += b[j][len-1 -i];
		}
		c[len-1 -i] += carry;
		c_temp = int(c[len-1 -i]/10);
		c[len-1 -i] %= 10;
		carry = c_temp;
	}

	bool flag = 0;
	for(i = 0;i < c.size();++i)
	{
		if(c[i] != 0 && flag == 0)
		{
			result += c[i] + '0';
			flag = 1;
		}
		else if(flag == 1)
		{
			result += c[i] + '0';
		}
	}

	return result;

}


int main(void){

	string num1 ("123456789123456789123456789123456789123456789");
	string num2 = num1;
	string result = num_multiply(num1, num2);
	cout << "result: " << result << endl;

  	return 0;

}