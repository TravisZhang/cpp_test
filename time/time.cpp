#include <bits/stdc++.h>

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

int main()
{
    auto t1 = Clock::now();
    auto t2 = Clock::now();
    std::cout << "Delta t2-t1: " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;

    cout << "t1: " << std::chrono::duration<double>(t1).count() << endl;
    cout << "t2: " << std::chrono::duration<double>(t2).count() << endl;

    auto current_time = chrono::system_clock::now();
    auto duration_in_seconds = chrono::duration<double>(current_time.time_since_epoch());

    cout << setprecision(32) <<  "duration: " << duration_in_seconds.count() << endl; 

   return 0;
}