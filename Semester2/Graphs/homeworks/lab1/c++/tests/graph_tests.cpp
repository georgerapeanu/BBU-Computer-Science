#include "gtest/gtest.h"
#include "Graph.h"

using namespace std;

class GraphTest:public testing::Test{
protected:
    Graph graph;
    void SetUp() override {
        vector<string> vertices = {"1", "2", "3"};
        vector<tuple<string, string, int> > edges = {{"1", "2", 0}, {"2", "1", 10}, {"1", "3", 3}};
        graph = Graph(vertices, edges);
    }
};

TEST_F(GraphTest, test_constructor){
    ASSERT_THROW(graph = Graph({"1", "2", "3"}, {{"1", "2", 0}, {"2", "1", 10}, {"1", "2", 3}}), GraphException);
    ASSERT_THROW(graph = Graph({"1", "2", "3"}, {{"1", "2", 0}, {"2", "1", 10}, {"1", "4", 3}}), GraphException);
    graph = Graph({"1", "2", "3"}, {{"1", "2", 0}, {"2", "1", 10}, {"1", "3", 3}});
}

TEST_F(GraphTest, test_parse_vertices){
    vector<string> vertices = {"1", "2", "3"};
    ASSERT_EQ(this->graph.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_is_edge){
    vector<string> vertices = {"1", "2", "3"};
    ASSERT_THROW(this->graph.is_edge("4", "2"), GraphException);
    ASSERT_EQ(this->graph.is_edge("1", "1"), false);
    ASSERT_EQ(this->graph.is_edge("1", "2"), true);
    ASSERT_EQ(this->graph.is_edge("1", "3"), true);
    ASSERT_EQ(this->graph.is_edge("2", "1"), true);
    ASSERT_EQ(this->graph.is_edge("2", "2"), false);
    ASSERT_EQ(this->graph.is_edge("2", "3"), false);
    ASSERT_EQ(this->graph.is_edge("3", "1"), false);
    ASSERT_EQ(this->graph.is_edge("3", "2"), false);
    ASSERT_EQ(this->graph.is_edge("3", "3"), false);
}

TEST_F(GraphTest, test_get_in_degree){
    ASSERT_THROW(this->graph.get_in_degree("4"), GraphException);
    ASSERT_EQ(this->graph.get_in_degree("1"), 1);
    ASSERT_EQ(this->graph.get_in_degree("2"), 1);
    ASSERT_EQ(this->graph.get_in_degree("3"), 1);
}

TEST_F(GraphTest, test_get_out_degree){
    ASSERT_THROW(this->graph.get_out_degree("4"), GraphException);
    ASSERT_EQ(this->graph.get_out_degree("1"), 2);
    ASSERT_EQ(this->graph.get_out_degree("2"), 1);
    ASSERT_EQ(this->graph.get_out_degree("3"), 0);
}

TEST_F(GraphTest, test_parse_outbound_edges){
    ASSERT_THROW(this->graph.parse_outbound_edges("4"), GraphException);
    vector<string> vertices;
    vertices = {"2", "3"};
    ASSERT_EQ(this->graph.parse_outbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(this->graph.parse_outbound_edges("2"), vertices);
    vertices = {};
    ASSERT_EQ(this->graph.parse_outbound_edges("3"), vertices);
}

TEST_F(GraphTest, test_parse_inbound_edges){
    ASSERT_THROW(this->graph.parse_inbound_edges("4"), GraphException);
    vector<string> vertices;
    vertices = {"2"};
    ASSERT_EQ(this->graph.parse_inbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(this->graph.parse_inbound_edges("2"), vertices);
    vertices = {"1"};
    ASSERT_EQ(this->graph.parse_inbound_edges("3"), vertices);
}

TEST_F(GraphTest, test_get_edge_cost){
    ASSERT_THROW(this->graph.get_edge_cost("4", "1"), GraphException);
    ASSERT_THROW(this->graph.get_edge_cost("3", "2"), GraphException);
    ASSERT_THROW(this->graph.get_edge_cost("1", "4"), GraphException);
    ASSERT_EQ(this->graph.get_edge_cost("1", "2"), 0);
    ASSERT_EQ(this->graph.get_edge_cost("1", "3"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("2", "1"), 10);
}

TEST_F(GraphTest, test_modify_edge_cost){
    ASSERT_THROW(this->graph.modify_edge_cost("4", "1", 0), GraphException);
    ASSERT_THROW(this->graph.modify_edge_cost("3", "2", 0), GraphException);
    ASSERT_THROW(this->graph.modify_edge_cost("1", "4", 0), GraphException);
    this->graph.modify_edge_cost("2", "1", -7);
    ASSERT_EQ(this->graph.get_edge_cost("1", "2"), 0);
    ASSERT_EQ(this->graph.get_edge_cost("1", "3"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("2", "1"), -7);
}

TEST_F(GraphTest, test_copy){
    Graph graph2 = Graph(this->graph);
    this->graph.modify_edge_cost("2", "1", -7);
    ASSERT_EQ(graph2.get_edge_cost("1", "2"), 0);
    ASSERT_EQ(graph2.get_edge_cost("2", "1"), 10);
    ASSERT_EQ(graph2.get_edge_cost("1", "3"), 3);
    vector<string> vertices;
    vertices = {"2", "3"};
    ASSERT_EQ(graph2.parse_outbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph2.parse_outbound_edges("2"), vertices);
    vertices = {};
    ASSERT_EQ(graph2.parse_outbound_edges("3"), vertices);
    vertices = {"2"};
    ASSERT_EQ(graph2.parse_inbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph2.parse_inbound_edges("2"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph2.parse_inbound_edges("3"), vertices);
    vertices = {"1", "2", "3"};
    ASSERT_EQ(graph2.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_add_vertex){
    ASSERT_THROW(this->graph.add_vertex("1"), GraphException);
    this->graph.add_vertex("10");
    this->graph.add_vertex("4");
    ASSERT_EQ(graph.get_edge_cost("1", "2"), 0);
    ASSERT_EQ(graph.get_edge_cost("2", "1"), 10);
    ASSERT_EQ(graph.get_edge_cost("1", "3"), 3);
    vector<string> vertices;
    vertices = {"2", "3"};
    ASSERT_EQ(graph.parse_outbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_outbound_edges("2"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("3"), vertices);
    vertices = {"2"};
    ASSERT_EQ(graph.parse_inbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_inbound_edges("2"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_inbound_edges("3"), vertices);
    vertices = {"1", "10", "2", "3", "4"};
    ASSERT_EQ(graph.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_remove_vertex){
    ASSERT_THROW(this->graph.remove_vertex("10"), GraphException);
    this->graph.remove_vertex("2");
    ASSERT_EQ(graph.get_edge_cost("1", "3"), 3);
    vector<string> vertices;
    vertices = {"3"};
    ASSERT_EQ(graph.parse_outbound_edges("1"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("3"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_inbound_edges("1"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_inbound_edges("3"), vertices);
    vertices = {"1", "3"};
    ASSERT_EQ(graph.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_add_edge){
    ASSERT_THROW(this->graph.add_edge("3", "4", 10), GraphException);
    ASSERT_THROW(this->graph.add_edge("4", "3", 10), GraphException);
    this->graph.add_vertex("10");
    this->graph.add_vertex("4");
    this->graph.add_edge("10", "2", 1);
    this->graph.add_edge("10", "1", 10);
    this->graph.add_edge("1", "10", 3);
    this->graph.add_edge("2", "3", 4);

    ASSERT_EQ(this->graph.get_edge_cost("1", "3"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("10", "2"), 1);
    ASSERT_EQ(this->graph.get_edge_cost("10", "1"), 10);
    ASSERT_EQ(this->graph.get_edge_cost("1", "10"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("2", "3"), 4);


    vector<string> vertices;
    vertices = {"2", "3", "10"};
    ASSERT_EQ(graph.parse_outbound_edges("1"), vertices);
    vertices = {"1", "3"};
    ASSERT_EQ(graph.parse_outbound_edges("2"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("3"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("4"), vertices);
    vertices = {"2", "1"};
    ASSERT_EQ(graph.parse_outbound_edges("10"), vertices);
    vertices = {"2", "10"};
    ASSERT_EQ(graph.parse_inbound_edges("1"), vertices);
    vertices = {"1", "10"};
    ASSERT_EQ(graph.parse_inbound_edges("2"), vertices);
    vertices = {"1", "2"};
    ASSERT_EQ(graph.parse_inbound_edges("3"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_inbound_edges("10"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_inbound_edges("4"), vertices);
    vertices = {"1", "10", "2", "3", "4"};
    ASSERT_EQ(graph.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_remove_edge){
    ASSERT_THROW(this->graph.remove_edge("3", "4"), GraphException);
    ASSERT_THROW(this->graph.remove_edge("3", "2"), GraphException);
    ASSERT_THROW(this->graph.remove_edge("4", "3"), GraphException);

    this->graph.add_vertex("10");
    this->graph.add_vertex("4");
    this->graph.add_edge("10", "2", 1);
    this->graph.add_edge("10", "1", 10);
    this->graph.remove_edge("1", "2");
    this->graph.remove_edge("2", "1");
    this->graph.add_edge("1", "10", 3);
    this->graph.add_edge("2", "3", 4);

    ASSERT_EQ(this->graph.get_edge_cost("1", "3"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("10", "2"), 1);
    ASSERT_EQ(this->graph.get_edge_cost("10", "1"), 10);
    ASSERT_EQ(this->graph.get_edge_cost("1", "10"), 3);
    ASSERT_EQ(this->graph.get_edge_cost("2", "3"), 4);


    vector<string> vertices;
    vertices = {"3", "10"};
    ASSERT_EQ(graph.parse_outbound_edges("1"), vertices);
    vertices = {"3"};
    ASSERT_EQ(graph.parse_outbound_edges("2"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("3"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_outbound_edges("4"), vertices);
    vertices = {"2", "1"};
    ASSERT_EQ(graph.parse_outbound_edges("10"), vertices);
    vertices = {"10"};
    ASSERT_EQ(graph.parse_inbound_edges("1"), vertices);
    vertices = {"10"};
    ASSERT_EQ(graph.parse_inbound_edges("2"), vertices);
    vertices = {"1", "2"};
    ASSERT_EQ(graph.parse_inbound_edges("3"), vertices);
    vertices = {"1"};
    ASSERT_EQ(graph.parse_inbound_edges("10"), vertices);
    vertices = {};
    ASSERT_EQ(graph.parse_inbound_edges("4"), vertices);
    vertices = {"1", "10", "2", "3", "4"};
    ASSERT_EQ(graph.parse_vertices(), vertices);
}

TEST_F(GraphTest, test_eq){
    ASSERT_EQ(Graph(this->graph), this->graph);
    Graph graph2 = Graph(this->graph);
    graph2.add_vertex("4");
    ASSERT_NE(graph2, this->graph);
    graph2.remove_vertex("1");
    ASSERT_NE(graph2, this->graph);
    graph2.remove_vertex("4");
    ASSERT_NE(graph2, this->graph);
    graph2.add_vertex("1");
    ASSERT_NE(graph2, this->graph);
    graph2.add_edge("1", "2", 0);
    ASSERT_NE(graph2, this->graph);
    graph2.add_edge("1", "3", 3);
    ASSERT_NE(graph2, this->graph);
    graph2.add_edge("2", "1", 10);
    ASSERT_EQ(graph2, this->graph);
    this->graph.add_edge("1", "1", 0);
    graph2.add_edge("1", "1", 10);
    ASSERT_NE(graph2, this->graph);
}

TEST_F(GraphTest, test_read_graph){

    ASSERT_THROW(read_graph("aaaa"), GraphException);
    ASSERT_THROW(read_graph("aaaa.modified"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail1.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail2.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail3.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail1.modified.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail2.modified.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail3.modified.txt"), GraphException);
    ASSERT_THROW(read_graph("../../tests/test_files/fail4.modified.txt"), GraphException);
    vector<string> vertices = {"0", "1", "2", "3", "4"};
    vector<tuple<string, string, int> > edges;
    edges = {
            {"0", "0", 1},
            {"0", "1", 7},
            {"1", "2", 2},
            {"2", "1", -1},
            {"1", "3", 8},
            {"2", "3", 5}
    };
    Graph graph1 = read_graph("../../tests/test_files/graph1.txt");
    ASSERT_EQ(graph1, Graph(vertices, edges));
    Graph graph2 = read_graph("../../tests/test_files/graph2.modified.txt");
    vertices = {
            "1", "5", "2", "0", "3"
    };
    edges = {
            {"1", "5", 10},
            {"1", "2", 0},
            {"0", "3", 4},
            {"3", "5", 20},
            {"2", "1", 4},
            {"1", "1", 5}
    };
    ASSERT_EQ(graph2, Graph(vertices, edges));
}

TEST_F(GraphTest, test_write_graph){

    ASSERT_THROW(write_graph("aaaa",this->graph), GraphException);
    ASSERT_THROW(write_graph("aaaa.modified",this->graph), GraphException);
    write_graph("./aaaa.modified.txt", this->graph);
    ASSERT_EQ(read_graph("./aaaa.modified.txt"), this->graph);
}

TEST_F(GraphTest, test_random_graph){

    ASSERT_THROW(random_graph(-10, 2), GraphException);
    ASSERT_THROW(random_graph(10, -2), GraphException);
    ASSERT_THROW(random_graph(6, 40), GraphException);
    ASSERT_THROW(write_graph("aaaa.modified",this->graph), GraphException);
    Graph graph = random_graph(6, 3);
    ASSERT_EQ(graph.parse_vertices().size(), 6);
    int cnt_edges = 0;
    for(auto it:graph.parse_vertices()){
        cnt_edges += graph.get_out_degree(it);
    }
    ASSERT_EQ(cnt_edges, 3);
}