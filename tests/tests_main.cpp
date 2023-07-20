#include "coauthor_graph/adjacency_list.hpp"
#include "dblp_parser/dblp_parser.hpp"

int main(int argc, char **argv){

  string path(argv[1]);
  dblp_parser dblp(path);

  int num_of_cols = 10;
  adjacency_list* CG = new adjacency_list(dblp.get_number_of_authors("article"));
  int coauth_x_pub_x_yr[11][11] = {0}; // test deben tener menos de 10 autores (modificable)
  
  for(pugi::xml_node article = dblp.first_article("article"); article; dblp.next_article(article, "article")){
    vector<int> authors = dblp.get_authors(article);
    features f; f.year = article.child("year").first_child().value();
    int num_of_authors = authors.size();
    coauth_x_pub_x_yr[atoi(f.year.c_str())][num_of_authors]++;
    for(int i = 0; i < num_of_authors-1; i++)
      for(int j = i + 1; j < num_of_authors; j++) 
        CG->add_edge(authors[i], authors[j], f);}
  CG->count_edge_frequency();

  // PRINT RESULT TO TEST
  for(int i = 0; i < 10; i++){
    cout<<"\n"<<i;
    for(int j = 1; j <= num_of_cols; j++)
      cout<<","<<CG->get_edge_freq(i, j);}
  cout<<endl;
  for(int i = 0; i < 10; i++){
    cout<<"\n"<<i;
    for(int j = 1; j <= num_of_cols; j++)  
      cout<<","<<coauth_x_pub_x_yr[i][j];}
  cout<<endl;

  return 0;
}
