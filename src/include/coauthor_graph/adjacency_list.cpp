#include "adjacency_list.hpp"
#include <unordered_map>

adjacency_list::adjacency_list(int n) : size(n){
  list = new vector<node>[size];
  for(int i = 0; i < size; i++) list[i] = vector<node>();
}

adjacency_list::~adjacency_list(){
  delete [] list;
} 

void adjacency_list::add_edge(int u, int v, const features &edge_features){
  if (u > v) swap(u, v);
  if(u >= size) cout<<"u out of bound: "<<u<<". size: "<<size<<endl;
  for(auto &[neighbour, edge] : list[u])
    if(neighbour == v){ edge[edge_features.year]++; return; }
  list[u].push_back(node(v, unordered_map<string, int>()));
  list[u][list[u].size()-1].second[edge_features.year] = 1;
}

mutex mtx;
void adjacency_list::count_edge_frequency_range(int start, int end){
  for(int i = start; i < end; i++)
    for(auto &[neighbour, edge] : list[i])
      for(auto feature : edge){
        if(feature.second >= 139){ 
          cerr<<"There is an edge greater than 140"; 
          return; }
        int C = atoi(feature.first.c_str()) < 1936 ? 0 : 1936;
        lock_guard<mutex> lock(mtx);
        edge_frequency[atoi(feature.first.c_str()) - C][feature.second]++;
      }
}

void adjacency_list::count_edge_frequency(int t){
  const int num_threads = t;
  if(t == 1){ count_edge_frequency_range(0, size); return; }
  vector<thread> threads(num_threads);
  int blockSize = size/num_threads;
  for(int i = 0; i < num_threads; i++){
    int start = i * blockSize;
    int end = (i == num_threads - 1) ? size : start + blockSize;
    threads[i] = thread(&adjacency_list::count_edge_frequency_range, this, start, end);
  }
  for(auto& thread : threads) thread.join();
}

int adjacency_list::get_edge_freq(int u, int v){
  return edge_frequency[u][v];
}

long long adjacency_list::graph_size(){
  long long total_size = 0;
    total_size += sizeof(node*) * size;
    total_size += sizeof(int) * size;
  /*
    for(int i = 0; i < size; i++) 
      for(node* j = list[i]; j; j = j->next)
        total_size += sizeof(node);
    total_size += sizeof(*this);
  */
    return total_size;
}

