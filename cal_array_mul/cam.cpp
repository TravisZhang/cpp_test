#include <boost/range/adaptor/reversed.hpp>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

vector<double> CalArrayMul(vector<double> &input_list) {
  vector<double> result(input_list.size(), 0.0);
  if (input_list.size() > 1) {
    vector<double> left_mul(input_list.size(), 0.0);
    vector<double> right_mul(input_list.size(), 0.0);

    size_t idx = 0;
    double mul_temp = 1.0;
    for (const auto &v : input_list) {
      mul_temp *= v;
      left_mul[idx++] = mul_temp;
			cout << "left: " << left_mul[idx-1] << " mul_temp: " << mul_temp << endl;
    }
		cout << "aaa" << endl;

    mul_temp = 1.0;
    for (const auto &v : boost::adaptors::reverse(input_list)) {
      mul_temp *= v;
      right_mul[--idx] = mul_temp;
      
			cout << "right: " << right_mul[idx] << " mul_temp: " << mul_temp << endl;
    }
		cout << "bbb" << endl;

    idx = 0;
    for (auto &v : result) {
			cout << "idx: " << idx << endl;
      if (idx == 0) {
        result[idx] = right_mul[idx + 1];
      } else if (idx == input_list.size() - 1) {
        result[idx] = left_mul[idx - 1];
      } else {
        result[idx] = right_mul[idx + 1] * left_mul[idx - 1];
      }
			cout << "result:" << result[idx] << endl;
			++idx;
    }
    return result;
  } else if (input_list.size() == 1) {
    result[0] = input_list[0];
    return result;
  } else {
    cout << "error !!!" << endl;
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  vector<double> input_list = {1.0, 2.0, 3.0, 4.0};
  vector<double> result = CalArrayMul(input_list);
  cout << "result: "
       << "size:" << result.size() << endl;
  for (const auto &v : result) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}