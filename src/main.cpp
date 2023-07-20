#include "dblp_parser/dblp_parser.hpp"
#include "coauthor_graph/adjacency_list.hpp"
#include "utils/chronograph.hpp"
#include "utils/input_handler.hpp"
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <cstring>

mutex CG_mutex, matrix_mutex;

/* SHARED STRUCTURES */
adjacency_list* CG;
vector<vector<long long>> coauth_x_pub_x_yr;

/* RACE CONDITION HANDLER */
void process_article(const string& input_file, const string& type){
  dblp_parser *t_dblp = new dblp_parser(input_file);
  for(xml_node article = t_dblp->first_article(type); article; t_dblp->next_article(article, type)){
    vector<int> authors = t_dblp->get_authors(article);
    xml_node year_node = article.child("year");
    if(!year_node) continue; // there are articles without year node
    features f; f.year = year_node.first_child().value();
    int num_of_authors = authors.size();
    {
      lock_guard<mutex> lock(matrix_mutex);
      coauth_x_pub_x_yr[atoi(f.year.c_str()) - 1936][num_of_authors]++;
    }
    for(int i = 0; i < num_of_authors-1; i++)
      for(int j = i + 1; j < num_of_authors; j++){
        lock_guard<mutex> lock(CG_mutex);
        CG->add_edge(authors[i], authors[j], f); 
      }
  }
  cout<<"File: "<<input_file<<" done\n";
  delete t_dblp;
}

int main(int argc, char *argv[]){

  start_timer();
  input_handler arguments(argc, argv);
  int threads_number = arguments.t_number;

  //dblp_parser dblp(arguments.file_path); 
  //cout<<dblp.get_number_of_authors(arguments.type.c_str())<<endl; basta con ejecutar una vez esto para saber el numero
  //WIP, dejarlo en un archivo de texto y verificar que tenga el valor.
  int dblp_total_authors = 2176110;
  CG = new adjacency_list(dblp_total_authors + 10); 
  coauth_x_pub_x_yr.resize(95,vector<long long>(305, 0));
  string type = arguments.pub_type; // article or inproceedings

  if(threads_number == 1) process_article(arguments.file_path, type);

  else{
    // Get all XML files in the directory
    string data_path = filesystem::current_path().string() + "/data/partitions/"; // dir MUST be already created
    vector<string> input_files;
    for(const auto & entry : filesystem::directory_iterator(data_path)){
      if(entry.path().extension() == ".xml") input_files.push_back(entry.path());
      if(input_files.size() >= arguments.t_number) break;
    }

    vector<thread> threads;
    for(const auto& input_file : input_files)
        threads.emplace_back(thread(process_article, input_file, type));

    for(auto& thread : threads) thread.join();
  }

  /* TABLE 1 CREATION */
  CG->count_edge_frequency(threads_number);
  //cout<<","<<CG->graph_size()<<"\n";

  string outputs_prefix(arguments.output_path);
  ofstream output_1(outputs_prefix + "/table1.csv");
  ofstream output_2(outputs_prefix + "/table2.csv");

  auto column_names = [](int x){
    ostringstream oss; oss<<"year";
    for(int i = 1; i <= x; i++) oss<<","<<i;
    oss<<"\n";
    return oss.str();
  };

  int max_freq = 140;
  output_1<<column_names(max_freq);
  for(int i = 0; i < 90; i++){
    output_1<<(i + 1936);
    for(int j = 1; j <= max_freq; j++)
      output_1<<","<<CG->get_edge_freq(i, j);
    output_1<<"\n";
  }

  output_2<<column_names(300);
  for(int i = 0; i < 90; i++){
    output_2<<(i + 1936);
    for(int j = 1; j <= 300; j++)
      output_2<<","<<coauth_x_pub_x_yr[i][j];
    output_2<<"\n";
  }

  output_1.close();
  output_2.close();
  delete CG;
  cout<<"Total runtime: ";
  stop_timer();
  
  return 0;
}
