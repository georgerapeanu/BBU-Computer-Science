/*!
 * @file Graph.cpp this file contains the implementation described in Graph.h
 */

//
// Created by georgerapeanu on 28.03.2022.
//

#pragma once
#include "Graph.h"
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

GraphException::GraphException(const string &msg) {
    this->message = msg;
}

string GraphException::what() const {
    return this->message;
}

Graph::Graph() {
    ;
}

Graph::Graph(const Graph &other) {
    this->nin = other.nin;
    this->nout = other.nout;
    this->cost = other.cost;
}

Graph &Graph::operator=(const Graph &other) {
    this->nin = other.nin;
    this->nout = other.nout;
    this->cost = other.cost;
    return *this;
}

Graph::~Graph() {
    ;
}

vector<std::string> Graph::parse_vertices() const {
    vector<std::string> vertices;
    for(const auto& it:this->nin){
        vertices.push_back(it.first);
    }
    return vertices;
}

bool Graph::is_edge(const string &x, const string &y) {
    if(this->nout.count(x) == 0 || this->nin.count(y) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    return find(this->nout[x].begin(), this->nout[x].end(), y) != this->nout[x].end();
}

int Graph::get_in_degree(const string &x) {
    if(this->nin.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    return this->nin[x].size();
}

int Graph::get_out_degree(const string &x) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    return this->nout[x].size();
}

vector<string> Graph::parse_outbound_edges(const string &x) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    return this->nout[x];
}

vector<string> Graph::parse_inbound_edges(const string &x) {
    if(this->nin.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    return this->nin[x];
}

int Graph::get_edge_cost(const string &x, const string &y) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->nin.count(y) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->cost.count({x, y}) == 0){
        throw GraphException("Edge doesn't exist");
    }
    return this->cost[{x, y}];
}

void Graph::modify_edge_cost(const string &x, const string &y, int z) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->nin.count(y) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->cost.count({x, y}) == 0){
        throw GraphException("Edge doesn't exist");
    }
    this->cost[{x, y}] = z;
}

void Graph::add_vertex(const string &x) {
    if(this->nout.count(x) > 0){
        throw GraphException("Vertex already exists");
    }
    this->nout[x] = vector<std::string>();
    this->nin[x] = vector<std::string>();
}

void Graph::remove_vertex(const string &x) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exists");
    }
    for(const auto& it:this->nout[x]){
        this->nin[it].erase(find(this->nin[it].begin(), this->nin[it].end(), x));
        this->cost.erase({x, it});
    }

    for(const auto& it:this->nin[x]){
        this->nout[it].erase(find(this->nout[it].begin(), this->nout[it].end(), x));
        this->cost.erase({it, x});
    }
    this->nout.erase(x);
    this->nin.erase(x);
}

void Graph::add_edge(const string &x, const string &y, int z) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->nin.count(y) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->cost.count({x, y}) > 0){
        throw GraphException("Edge already exists");
    }
    this->nout[x].push_back(y);
    this->nin[y].push_back(x);
    this->cost[{x,y}] = z;
}

void Graph::remove_edge(const string &x, const string &y) {
    if(this->nout.count(x) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->nin.count(y) == 0){
        throw GraphException("Vertex doesn't exist");
    }
    if(this->cost.count({x, y}) == 0){
        throw GraphException("Edge doesn't exist");
    }
    this->nout[x].erase(find(this->nout[x].begin(), this->nout[x].end(), y));
    this->nin[y].erase(find(this->nin[y].begin(), this->nin[y].end(), x));
    this->cost.erase({x,y});
}

bool Graph::operator==(const Graph &other) const {
    if(this->nout.size() != other.nout.size() || this->nin.size() != other.nin.size()){
        return false;
    }
    if(this->cost.size() != other.cost.size()){
        return false;
    }
    vector<std::string> this_vertices = this->parse_vertices();
    vector<std::string> other_vertices = other.parse_vertices();
    sort(this_vertices.begin(), this_vertices.end());
    sort(other_vertices.begin(), other_vertices.end());
    if(this_vertices != other_vertices){
        return false;
    }

    for(auto it:cost){
        if(other.cost.count(it.first) == 0 || other.cost.at(it.first) != it.second){
            return false;
        }
    }
    return true;
}

bool Graph::operator!=(const Graph &other) const {
    return !(*this == other);
}

Graph::Graph(const vector<string> &vertices,
             const vector<tuple<string, string, int>> &edges) {
    for(auto it:vertices){
        this->nin[it] = vector<std::string>();
        this->nout[it] = vector<std::string>();
    }

    for(auto it:edges){
        if(this->nout.count(get<0>(it)) == 0 || this->nin.count(get<1>(it)) == 0){
            throw GraphException("Vertices don't exist");
        }
        if(this->cost.count({get<0>(it), get<1>(it)})){
            throw GraphException("Edge already exists");
        }
        this->nout[get<0>(it)].push_back(get<1>(it));
        this->nin[get<1>(it)].push_back(get<0>(it));
        this->cost[{get<0>(it), get<1>(it)}] = get<2>(it);
    }
}

bool endswith(string s, string ends){
    if(s.size() < ends.size()){
        return false;
    }
    for(int i = 0;i < (int)ends.size();i++){
        if(s[(int)s.size() - i] != ends[(int)ends.size() - i]){
            return false;
        }
    }
    return true;
}

static void assert_nothing_after(istringstream &s){
    if(!s){
        return ;
    }
    char tmp = '\0';
    while((s >> tmp) && tmp == '\n' && tmp == ' ');
    if(tmp != '\n' && tmp != ' ' && tmp != '\0'){
        throw GraphException("invalid format");
    }
}

Graph read_graph(const string &file){
    if(endswith(file, ".txt") == 0){
        throw GraphException("invalid filename");
    }
    ifstream f(file);

    vector<string> lines;

    string line;
    while(getline(f, line)){
        lines.push_back(line);
    }

    int n, m;
    if(lines.empty()){
        throw GraphException("invalid format");
    }
    istringstream reader(lines[0]);
    if(!(reader >> n >> m)){
        throw GraphException("invalid format");
    }

    assert_nothing_after(reader);
    /*
     * tmp = '0';
    while((reader >> tmp) && tmp == ' ' || tmp == '\n');
    if(tmp != '\n' && tmp != ' ' && tmp != '\0'){
        throw GraphException("invalid format");
    }
     */

    vector<string> vertices;
    vector<tuple<string, string, int> > edges;

    if(endswith(file, ".modified.txt")) {
        if (lines.size() != m + 2) {
            throw GraphException("invalid format");
        }
        reader = istringstream(lines[1]);

        for (int i = 0; i < n; i++) {
            string vertex;
            if (!(reader >> vertex)) {
                throw GraphException("invalid format");
            }
            vertices.push_back(vertex);
        }
        assert_nothing_after(reader);

        for (int i = 0; i < m; i++) {
            string x, y;
            int z;
            reader = istringstream(lines[2 + i]);
            if (!(reader >> x >> y >> z)) {
                throw GraphException("invalid format");
            }
            edges.push_back({x, y, z});
            assert_nothing_after(reader);
        }
        f.close();

    }else{
        if (lines.size() != m + 1) {
            throw GraphException("invalid format");
        }

        for (int i = 0; i < n; i++) {
            string vertex;
            ostringstream tmp("");
            tmp << i;
            vertex = tmp.str();
            vertices.push_back(vertex);
        }

        for (int i = 0; i < m; i++) {
            string x, y;
            int z;
            reader = istringstream(lines[1 + i]);
            if (!(reader >> x >> y >> z)) {
                throw GraphException("invalid format");
            }
            edges.push_back({x, y, z});
            assert_nothing_after(reader);
        }

        f.close();
    }
    Graph ans(vertices, edges);
    return ans;
}

void write_graph(const string &file, Graph &graph){
    if(endswith(file, ".modified.txt") == 0){
        throw GraphException("invalid filename");
    }
    ofstream g(file);

    vector<string> vertices = graph.parse_vertices();
    int n = vertices.size();
    int m = 0;

    for(auto vertex:vertices){
        m += graph.get_out_degree(vertex);
    }

    g << n << " " << m << endl;
    for(auto vertex:vertices){
        g << vertex << " ";
    }
    g << endl;
    for(auto vertex:vertices){
        for(auto edge: graph.parse_outbound_edges(vertex)){
            g << vertex << " " << edge << " " << graph.get_edge_cost(vertex, edge) << endl;
        }
    }

    g.close();
}

Graph random_graph(int n, int m){
    if(n < 0 || m < 0 || m > n * n){
        throw GraphException("invalid arguments");
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<tuple<string, string, int> > edges;
    vector<string> vertices;
    for(int i = 0;i < n;i++){
        vertices.push_back(to_string(i));
    }
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++){
            edges.push_back({to_string(i), to_string(j), (rng() % 2000000000) - 1000000000});
        }
    }
    shuffle(edges.begin(), edges.end(), rng);
    edges.resize(m);
    return Graph(vertices, edges);
}