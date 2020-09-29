#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "MultiCellDS.hpp"
#include "MultiCellDS-pimpl.hpp"
#include "MultiCellDS-simpl.hpp"


struct io_face{
  mesh::face * mcds_obj;
  double lowest_x;
  double lowest_y;
  double highest_x;
  double highest_y;
  std::vector<int> node_ids;
  std::vector<int> edge_ids;
  std::vector<int> cell_ids;
};

struct io_edge{
  mesh::edge * mcds_obj;
  double lowest_x;
  double lowest_y;
  double highest_x;
  double highest_y;
  std::vector<int> node_ids;
  std::vector<int> face_ids;
  std::vector<int> cell_ids;
};

struct io_node{
  mesh::node * mcds_obj;
  double x;
  double y;
  std::vector<int> edge_ids;
  std::vector<int> face_ids;
  std::vector<int> cell_ids;
};

struct io_cell{
  cell::cell * mcds_obj;
  std::vector<int> node_ids;
  std::vector<int> edge_ids;
  std::vector<int> face_ids;
};

class MCDS_io{
  public:
    MCDS_io();
    MCDS_io(std::string filename);
    void read(std::string filename);
    void write(std::string filename);
    void add_metadata(std::string filename);
    void add_time();
    void finalize_cellshapes();
    void map_cellshape();

    inline MultiCellDS * get_multicellds(){return multicellds;}
    inline std::map<int, io_face> * get_faces(){return &faces;}
    inline std::map<int, io_edge> * get_edges(){return &edges;}
    inline std::map<int, io_node> * get_nodes(){return &nodes;}
    inline std::map<int, io_cell> * get_cells(){return &cells;}

    inline io_face * face_by_id(int id){return & faces[id];}
    inline io_edge * edge_by_id(int id){return & edges[id];}
    inline io_node * node_by_id(int id){return & nodes[id];}
    inline io_cell * cell_by_id(int id){return & cells[id];}
   
    inline int get_lowest_x(){return lowest_x;}
    inline int get_lowest_y(){return lowest_y;}
    inline int get_highest_x(){return highest_x;}
    inline int get_highest_y(){return highest_y;}

    io_cell * get_new_cell(int id);
    io_edge * get_new_edge(int id);
    io_face * get_new_face(int id);
    io_node * get_new_node(int id);

    int get_new_edge_uniq(int node1, int node2);

  private:
    double lowest_x;
    double lowest_y;
    double highest_x;
    double highest_y;
 
    bool mapped = false;
    MultiCellDS* multicellds;
    std::map<int, io_face> faces;
    std::map<int, io_edge> edges;
    std::map<int, io_node> nodes;
    std::map<int, io_cell> cells;
    
    std::map<std::string, int> edge_by_nodes; 
};

