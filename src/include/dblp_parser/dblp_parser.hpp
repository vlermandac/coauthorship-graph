#include <pugixml.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace pugi;
using namespace std;

class dblp_parser{
public:
  xml_document doc;
  xml_node dblp;
  map<string, int> author_id;
  int id = 0;
  int n_of_authors = -1;
  int n_of_papers = 0;
//Methods:
  dblp_parser(string file_path);
  void read_file(string file_path);
  vector<int> get_authors(xml_node &article);
  int get_number_of_authors(const string &type);
  xml_node first_article(const string &type);
  void next_article(xml_node &article, const string &type);
};
