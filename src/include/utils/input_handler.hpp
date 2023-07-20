#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

struct input_handler {
  string pub_type;
  string file_path;
  string output_path;
  int t_number;

  input_handler(int argc, char** argv){
    if(argc == 1){
     cerr<<"Usage: "<<argv[0]<<" [-t pub_type] [-i input_file] [-o output_directory] [-p threads_number]"<<endl;
     exit(1);
    }
    int opt;
    while((opt = getopt(argc, argv, "t:i:o:p:")) != -1) {
      switch(opt){
        case 't':
          pub_type = optarg;
          cout<<"-t: "<<optarg<<endl;
          break;
        case 'i':
          file_path = optarg;
          cout<<"-i: "<<optarg<<endl;
          break;
        case 'o':
          output_path = optarg;
          cout<<"-o: "<<optarg<<endl;
          break;
        case 'p':
          try {
            t_number = std::stoi(optarg);
          } catch (std::exception& e) {
            cerr << "Invalid thread number: " << optarg << endl;
            exit(1);
          }
          cout<<"-p: "<<optarg<<endl;
          break;
        default:
          cerr<<"Usage: "<<argv[0]<<" [-t pub_type] [-i input_file] [-o output_directory] [-p threads_number]"<<endl;
          exit(1);
      }
    }
  }
};
