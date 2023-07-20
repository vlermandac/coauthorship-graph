#include<memory>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<unordered_map>
#include<pugixml.hpp>
#include<mutex>
#include<thread>
using namespace std;

using node = pair< int, unordered_map<string, int>>;

struct features{ string year; };

//cantidad de numero de colaboraciones por autor
class adjacency_list{
private:
  vector<node> *list;
  int edge_frequency[90][145] = {0};
public:
  int size;
  adjacency_list(int n);
  ~adjacency_list();
  void add_edge(int u, int v, const features &edge_features);
  void count_edge_frequency(int t = 1);
  long long graph_size();
  void count_edge_frequency_range(int start, int end);
  int get_edge_freq(int u, int v);
};
