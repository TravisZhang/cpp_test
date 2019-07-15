#include <vector>
#include <iostream>
#include <string>
using namespace std;

double Saturate(const double in, const double min, const double max) {
    return std::max(std::min(in,max),min);
}

void test_list_size(float list_in[]) {
    cout << "list_in size: " << sizeof(list_in) << endl;
    cout << "list_in size: " << sizeof(list_in)/sizeof(float) << endl;
}

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

    return 0;
}