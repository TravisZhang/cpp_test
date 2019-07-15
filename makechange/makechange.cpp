// 找零钱.cpp : 定义控制台应用程序的入口点。
//

// #include "stdafx.h"
#include <vector>
#include <algorithm>

#include <iostream>

#include <string>


# include "stdlib.h"
using namespace std;

int global_types = 1;

//定义表格中的单元格
class unit{
public:
	int coin;  //当前单元格所花费的当前币种
	string message;//每个单元格的coin的最少硬币数构成组成信息

	vector<int> type_num_list;

	unit() :coin(0), message("")
	{type_num_list.resize(global_types,0);}


};
int main(void)
{


	int types, money;
	cout << "请输入硬币的种类\n";
	cin >> types ;
	global_types = types;
	vector<int>coin(types, 0);
	cout << "请输入各个硬币\n";
	for (int i = 0; i < types; i++)
	{
		cin >> coin[i];

	}
	cout << "请输入要找的零钱\n";

	//对硬币币值升序排序，
	sort(coin.begin(), coin.end());
	cin >> money;
	
	//定义多张表格，张数为硬币的种类，每张表格有money+1列。
	vector <vector<unit>> table(types, vector <unit> (money+1));

	// vector <vector <vector <unit>>> table_full;

	// table_full.resize(types);
	// for(int i = 0;i < types;++i)
	// {
	// 	table_full[i].resize(money+1);
	// 	for(int j = 0;j < money+1;++j)
	// 	{
	// 		table_full[i][j].resize(1);
	// 	}
	// }

	//对于一个列,对于各种解决方案的总硬币数目进行存储，
	vector<int> result;
	// vector<unit> result_full;
	

	for (int i = 0; i < types; i++)  //开始考虑每个币种，
	{
		cout << "i " <<i<<endl;
		if (i == 0)
		{
			//第一张表格初始化，一般情况，最小币值一定是1，所以第一张表格中每个单元格很好填，耗费的硬币数目就是列号
			for (int j = 0; j < money + 1; j++)
			{

				table[i][j].coin = j;  //第j列的找零需要j个1元硬币

				table[i][j].message = to_string(j) + "*" + to_string(1); //信息

				// table_full[i][j].push_back(table[i][j]);

				// table_full[i][j][0].type_num_list[i] = j;

			}
		}
		else{
			//接下来开始计算后面的几张表格。就是考虑每一个新币种的加入
			for (int j = 0; j < money + 1; j++)
			{

				//对于一个列所对应的需要找零的数目，当前币值的可以取多个，只要总数不超过列对应的找零数目，余数部分由上一个表来凑。
				for (int k = 0; k*coin[i] <= j; k++)
				{

					//当前币值的硬币用了k个，不足的部分用上一个表的最佳方案。
					result.push_back(k + table[i-1][j - k*coin[i]].coin);

					// cout << "k " <<k<<endl;
					// cout << "table_full[i-1][j - k*coin[i]].size() "<<table_full[i-1][j - k*coin[i]].size()<<endl;

					// for(int m = 0; m < table_full[i-1][j - k*coin[i]].size(); ++m)
					// {
					// 	cout << "m "<<m<<endl;
					// 	table_full[i-1][j - k*coin[i]][m].type_num_list[i] = k;
					// 	result_full.push_back(table_full[i-1][j - k*coin[i]][m]);

					// }

				}

				//一个列中，消耗硬币数最少的方案
				auto g= min_element(result.begin(), result.end());
				//当前列所需要的最小硬币数目：*g
				table[i][j].coin = *g;

				//当前币种用了l个
				int l = (int)(g - result.begin());

				//更信信息
				table[i][j].message = table[i - 1][j - coin[i]*l].message +"+" +to_string(l) + "*" + to_string(coin[i]);

				// table_full[i][j] = result_full;

				// cout << "table_full[i][j].size() "<<table_full[i][j].size()<<endl;
				// for(int n = 0;n < table_full[i][j].size(); ++n)
				// {
				// 	cout<<"n "<<n<<endl;
				// 	// cout<<"global_types "<<global_types<<endl;
				// 	table_full[i][j][n].message = "";
				// 	for(int p = 0;p < global_types;++p)
				// 	{
				// 		// cout<<"p "<<p<<endl;
				// 		if(p == 0)
				// 			table_full[i][j][n].message += to_string(table_full[i][j][n].type_num_list[p]) + "*" + to_string(coin[p]);
				// 		else
				// 			table_full[i][j][n].message += "+" + to_string(table_full[i][j][n].type_num_list[p]) + "*" + to_string(coin[p]);
				// 	}				
				// }
				
				//清空，准备下一个列的计算。
				result.clear();

				// result_full.clear();

			}
		
		
		
		}

	}
	cout << "需要的硬币数目为 " << table[types - 1][money].coin << endl;
	cout << "最佳解决方案为 " << table[types - 1][money].message << endl;

	// vector<unit> table_final;

	// table_final.push_back(table_full[0][money][0]);

	// for(int i = 0;i < types;++i)
	// {
	// 	cout << "i " << i <<endl;
	// 	for(int j = 0;j < table_full[i][money].size();++j)
	// 	{
	// 		cout << "j " << j <<endl;
	// 		for(int m = 0;m < table_final.size();++m)
	// 		{
	// 			cout << "m " << m <<endl;
	// 			int flag = 0;
	// 			for(int k = 0;k < types;++k)
	// 			{
	// 				if(table_full[i][money][j].type_num_list[k] == table_final[m].type_num_list[k])
	// 					flag++;
	// 			}
	// 			if(flag<types)
	// 			{
	// 				table_final.push_back(table_full[i][money][j]);
	// 			}
	// 		}
	// 	}
	// }

	// cout << "全部解决方案为 " << endl;
	// for(int i = 0;i < table_final.size();++i)
	// {
	// 	cout << table_final[i].message << endl;
	// }

	// system("pause");
	return 0;
}

