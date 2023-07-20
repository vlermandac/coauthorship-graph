#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;

class chronograph{
private:
  long long time;
  chrono::time_point<chrono::high_resolution_clock> start;
public:
  void start_time(){
    start = std::chrono::high_resolution_clock::now();
  }
  long long stop_time(){
    auto end = chrono::high_resolution_clock::now();
    return time = chrono::duration_cast<chrono::microseconds>(end - start).count();
  }
};

chronograph cr;
void start_timer(){ cr.start_time(); }
void stop_timer(){ 
  long long ms = cr.stop_time();
  double seconds = static_cast<double>(ms) / 1000000.0;
  cout<<","<<fixed<<setprecision(2)<<seconds; 
}
