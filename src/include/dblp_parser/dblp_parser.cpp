#include "dblp_parser.hpp"

xml_node dblp_parser::first_article(const string &type){
  return dblp.child(type.c_str());
}

void dblp_parser::next_article(xml_node &article, const string &type){
  article = article.next_sibling(type.c_str());
}

void dblp_parser::read_file(string file_path){
  xml_parse_result result = doc.load_file(file_path.c_str());
  if(!result) cerr<<"Failed to parse XML data! "<<result.description()<<endl; 
  dblp = doc.child("dblp");
}

dblp_parser::dblp_parser(string file_path){
  this->read_file(file_path);
}

vector<int> dblp_parser::get_authors(xml_node &article){
  vector<int> author_id_list;
  for(xml_node author = article.first_child(); author; author = author.next_sibling("author")){
    string author_name(author.first_child().value());
    if(!author_id.count(author_name))
      author_id[author_name] = id++;
    author_id_list.push_back(author_id[author_name]);
  }
  return author_id_list;
}

int dblp_parser::get_number_of_authors(const string &type){
  if(n_of_authors != -1) return n_of_authors;
  if(n_of_papers != 0) n_of_papers = 0;
  for(xml_node article = dblp.child(type.c_str()); article; article = article.next_sibling(type.c_str())){
    n_of_papers++;
    get_authors(article);
  }
  return n_of_authors = author_id.size();
}

