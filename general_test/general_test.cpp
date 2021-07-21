#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;

std::string planning_status_for_log_ = "";
std::string planning_status_titles_ = "";

double Saturate(const double in, const double min, const double max) {
    return std::max(std::min(in,max),min);
}

void test_list_size(float list_in[]) {
    cout << "list_in size: " << sizeof(list_in) << endl;
    cout << "list_in size: " << sizeof(list_in)/sizeof(float) << endl;
}

size_t FindStrNum(const std::string& mp_status, const std::string& start_str, const std::string& end_str,
                               const size_t start_idx, const std::string& title_str, const size_t sub_num = 0) {
  std::string::size_type start_pos = mp_status.find(start_str, start_idx);
  start_pos = (start_pos != mp_status.npos ? start_pos : mp_status.size());
  std::string::size_type end_pos = mp_status.find(end_str, start_pos + start_str.size());
  std::cout << "s pos: " << start_pos << " e pos: " << end_pos << " str: " << title_str << std::endl;
  if (start_pos != mp_status.npos && end_pos != mp_status.npos) {
    planning_status_for_log_ +=
        mp_status.substr(start_pos + start_str.size(), end_pos - start_pos - start_str.size()) + ",";
    planning_status_titles_ += title_str + ",";
    return end_pos;
  } else if (start_pos != mp_status.npos && start_pos + start_str.size() + sub_num < mp_status.size()) {
    std::cout << "real s: " << start_pos + start_str.size() + sub_num << " sub num: " << sub_num << std::endl;
    planning_status_for_log_ +=
        mp_status.substr(start_pos + start_str.size(), sub_num) + ",";
    planning_status_titles_ += title_str + ",";
  }
  return start_pos + start_str.size();
}

class Test
{
public:
  Test() = default;
  ~Test() = default;

  const int& get_a() const {return a_;}
  void print_a() {std::cout << "a: " << a_ << std::endl;}

private:
  int a_ = 0;
    
};


class TestA
{
public:
  TestA(int a) { a_ = a; }
  ~TestA() = default;

  const int& get_a() const {return a_;}
  void print_a() {std::cout << "a: " << a_ << std::endl;}

private:
  int a_ = 0;
    
};

int main(int argc, char* argv[])
{

    double x = -14;
    x = Saturate(x, -5, 5);
    cout << "x after: " << x << endl;

    uint a = 2;
    uint b = 3;
    cout << a/b << endl;
    cout << (float)a/b << endl;
    float t = 0.5;
    cout << (a-t)/b << endl;

    float list0[5] = {0.0f};
    cout << "list0 size: " << sizeof(list0) << endl;
    cout << "list0 size: " << sizeof(list0)/sizeof(float) << endl;
    test_list_size(list0);

    float g = 5.0f, h = 2.0f;
    g /= h*2.0f;
    cout << "g: " << g << endl;

    double xxx = 1.23456789123456789123456789123456789e10;
    std::cout << std::to_string(xxx) << std::endl;

    std::ostringstream out;
    out.precision(std::numeric_limits<double>::digits);
    out << xxx;

    std::string res = std::move(out.str());
    std::cout << out.str() << std::endl;

    // succeed
    // std::string planning_status = "2021/01/08 02:42:35 821497   INFO [data_logging.cpp->LogError:64]    Now: 7890.51, Gap: 0.10, Delay: 0.20, Se: -0.0, Le: -0.00\nReal ka al: 0.00041, 0.103, Follow: 22.1m, 1.4s, Ref v: 15\nMatch Point yaw: -1.18, ka: 0.00037, dka*e8: -27, d0: -0.00, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 896, lat num: 7, lon num:128\nCurve v: 41., Lat L: 75.6m, RL idx: 864 [SUCC] \nMP Init Point v: 15.8, a: 0.01, yaw: -1.18, ka: 0.00037\nExecution: 0 ms";
    // fail
    // std::string planning_status = "2021/01/07 03:39:50 050089   INFO [data_logging.cpp->LogError:64]    Now: 7917.51, Gap: 0.10, Delay: 0.20, replan bp no enable\nReal ka al: -0.0164, -2.53, Follow: 17.3m, 1.4s, Ref v: 4.\nMatch Point yaw: -1.94, ka: -0.0169, dka*e8: -10582, d0: -0.09, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 0, lat num: 0, lon num:123\nCurve v: 10. [FAIL!!!!!] \nExecution: 0 ms";
    // lc cancel fail
    // std::string planning_status = "2021/01/07 03:39:50 050089   INFO [data_logging.cpp->LogError:64]    Now: 7917.51, Gap: 0.10, Delay: 0.20, replan bp no enable\nReal ka al: -0.0164, -2.53, Follow: 17.3m, 1.4s, Ref v: 4.\nMatch Point yaw: -1.94, ka: -0.0169, dka*e8: -10582, d0: -0.09, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 0, lat num: 0, lon num:123\nCurve v: 10., Follow: 17.3m, 1.4s, Ref v: 4.\nMatch Point yaw: -1.94, ka: -0.0169, dka*e8: -10582, d0: -0.09, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 0, lat num: 0, lon num:123\nCurve v: 10. [FAIL!!!!!] \nExecution: 0 ms";
    // lc cancel succeed
    std::string planning_status = "2021/01/07 03:39:50 050089   INFO [data_logging.cpp->LogError:64]    Now: 7917.51, Gap: 0.10, Delay: 0.20, replan bp no enable\nReal ka al: -0.0164, -2.53, Follow: 17.3m, 1.4s, Ref v: 4.\nMatch Point yaw: -1.94, ka: -0.0169, dka*e8: -10582, d0: -0.09, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 0, lat num: 0, lon num:123\nCurve v: 10., Follow: 17.3m, 1.4s, Ref v: 4.\nMatch Point yaw: -1.94, ka: -0.0169, dka*e8: -10582, d0: -0.09, Obj: \nLead s: 179769, Lead v: 0.000, Lead a: 0.00, Lead pa: 0.00\nTra pair: 0, lat num: 0, lon num:123\nCurve v: 10., Lat L: 75.6m, RL idx: 864 [SUCC] \nMP Init Point v: 15.8, a: 0.01, yaw: -1.18, ka: 0.00037\nExecution: 0 ms";

    size_t end_pos = 0;
    std::cout << "total size: " << planning_status.size() << std::endl;

    end_pos = FindStrNum(planning_status, "Real ka al:", ",", 0, "ka");
    // std::cout << "end pos: " << end_pos << std::endl;
    // std::cout << "str: " << planning_status.at(end_pos) << std::endl;
      FindStrNum(planning_status, ",", ",", end_pos, "al");
      end_pos = FindStrNum(planning_status, "Follow:", "m", 0, "desire follow dist");
      end_pos = FindStrNum(planning_status, ",", "s,", end_pos, "time gap");
      FindStrNum(planning_status, "Ref v:", "\n", end_pos, "ref v");

        FindStrNum(planning_status, "Match Point yaw:", ",", 0, "match yaw");
  FindStrNum(planning_status, "ka:", ",", 0, "ka");
  FindStrNum(planning_status, "dka*e8:", ",", 0, "dka*1e8");
  FindStrNum(planning_status, "d0:", ",", 0, "d0");

  FindStrNum(planning_status, "Lead s:", ",", 0, "lead s");
  FindStrNum(planning_status, "Lead v:", ",", 0, "v");
  FindStrNum(planning_status, "Lead a:", ",", 0, "a");
  FindStrNum(planning_status, "Lead pa:", "\n", 0, "pa");


  end_pos = FindStrNum(planning_status, "Tra pair:", ",", 0, "total pair");
  end_pos = FindStrNum(planning_status, "lat num:", ",", end_pos, "lat num");
  end_pos = FindStrNum(planning_status, "lon num:", "\n", end_pos, "lon num");

  end_pos = FindStrNum(planning_status, "Curve v:", ",", 0, "curv v", 4);

    // for lc cancel
  size_t end_pose_0 = end_pos;
  end_pos = FindStrNum(planning_status, "Tra pair:", ",", end_pose_0, "total pair");
  end_pos = FindStrNum(planning_status, "lat num:", ",", end_pos, "lat num");
  end_pos = FindStrNum(planning_status, "lon num:", "\n", end_pos, "lon num");
  // lc_canceled_ = end_pos != end_pose_0;

  FindStrNum(planning_status, "Lat L:", "m,", 0, "lat l");
  FindStrNum(planning_status, "RL idx: ", " ", 0, "rl idx");

  FindStrNum(planning_status, "Execution:", "ms", 0, "exec ms");

    std::cout << "planning_status_for_log_: " << planning_status_for_log_ << std::endl;
    std::cout << "planning_status_titles_:  " <<  planning_status_titles_ << std::endl;


    Test test;
    const int& aaa = test.get_a();
    // aaa = 3; // will report error
    test.print_a();

    TestA test_a(2);
    test_a = TestA(3);
    test_a.print_a();

    std::vector<double> vec0 = {1.0,2.0,3.0};
    std::cout << "vec0[-2]: " << vec0[-2] << std::endl;

    std::vector<double> rl = {};
    std::cout << "rl front: " << rl.front() << std::endl; // core dump

    std::vector<int> vec1 = {1,2,3,4,5,6,7,8,9};
    std::vector<int> vec2(vec1.begin()+3, vec1.begin()+1);
    for (const auto v : vec2) {
      std::cout << " v: " << v;
    }
    std::cout << std::endl;

    return 0;
}