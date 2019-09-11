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
      // cout << "left: " << left_mul[idx - 1] << " mul_temp: " << mul_temp
      //  << endl;
    }
    // cout << "aaa" << endl;

    mul_temp = 1.0;
    for (const auto &v : boost::adaptors::reverse(input_list)) {
      mul_temp *= v;
      right_mul[--idx] = mul_temp;

      // cout << "right: " << right_mul[idx] << " mul_temp: " << mul_temp <<
      // endl;
    }
    // cout << "bbb" << endl;

    idx = 0;
    for (auto &v : result) {
      // cout << "idx: " << idx << endl;
      if (idx == 0) {
        result[idx] = right_mul[idx + 1];
      } else if (idx == input_list.size() - 1) {
        result[idx] = left_mul[idx - 1];
      } else {
        result[idx] = right_mul[idx + 1] * left_mul[idx - 1];
      }
      // cout << "result:" << result[idx] << endl;
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

vector<double> CalArrayMulRanged(vector<pair<int, int>> &input_idx_list,
                                 vector<double> &input_list) {
  vector<double> result(input_idx_list.size(), 0.0);
  if (input_list.size() > 0) {
    vector<double> left_mul(input_list.size(), 0.0);

    size_t idx = 0;
    double mul_temp = 1.0;
    for (const auto &v : input_list) {
      if (v != 0.0)
        mul_temp *= v;
      left_mul[idx++] = mul_temp;
      // cout << "left: " << left_mul[idx - 1] << " mul_temp: " << mul_temp
      //  << endl;
    }
    // cout << "aaa" << endl;

    size_t i = 0;
    for (const auto &v : input_list) {
      size_t j = 0;
			// cout << "j: " << j << endl;
      for (const auto &pair : input_idx_list) {
				// cout << "first: " << pair.first << " second: " << pair.second << endl;
        if (result[j++] == 1.0 || (i < pair.first || i > pair.second) || input_list[i] != 0.0) {
          continue;
        }
				// cout << "first: " << pair.first << " second: " << pair.second << endl;
				result[j-1] = 1.0;
				// cout << "i:" << i << " j:" << j << endl;
      }
      ++i;
    }

    // cout << "result: "
    //      << "size:" << result.size() << endl;
    // for (const auto &v : result) {
    //   cout << v << " ";
    // }
    // cout << endl;

    idx = 0;
    for (const auto &pair : input_idx_list) {
      if (result[idx] == 1.0) {
        result[idx] = 0.0;
      } else {
        result[idx] = left_mul[pair.second] / left_mul[pair.first] *
                      input_list[pair.first];
      }
      ++idx;
    }
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

  vector<double> input_list1 = {2.0, 0.0, 3.0, 5.0, 0.0, 6.0, 0.0};
  vector<pair<int, int>> idx_list;
  idx_list.push_back(pair<int, int>(1, 3));
  idx_list.push_back(pair<int, int>(2, 4));
  idx_list.push_back(pair<int, int>(0, 5));
  idx_list.push_back(pair<int, int>(3, 6));
	idx_list.push_back(pair<int, int>(2, 3));

  result = CalArrayMulRanged(idx_list, input_list1);
  cout << "result: "
       << "size:" << result.size() << endl;
  for (const auto &v : result) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}