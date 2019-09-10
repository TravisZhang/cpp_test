#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

vector<int> FindAppearTime(vector<double>& input_list) {
	unordered_map <double, int> list_dict;
	vector<int> result(input_list.size());
	size_t idx = 0;
	for(const auto& v : input_list) {
		if(list_dict.find(v) == list_dict.end()) {
			list_dict[v] = 1;
			result[idx] = -1;
			// cout << "aaa" << endl;
		}
		else {
			list_dict[v] += 1;
			result[idx] = 0;
			// cout << "bbb" << endl;
		}
		++idx;
	}
	return result;
}

int main(int argc, char* argv[])
{
	vector<double> input_list = {1.0, 3.0, 1.0, 2.0, 1.0};
	vector<int> result = FindAppearTime(input_list);
	cout << "result: " << "size:" << result.size() << endl;
	for(const auto& v : result) {
		cout << v << " ";
 	}
 	cout << endl;

	return 0;
}