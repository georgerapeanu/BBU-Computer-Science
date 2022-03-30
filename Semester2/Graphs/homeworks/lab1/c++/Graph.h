/*!
 * @file Graph.h this file contains the model for a Graph class
 */

//
// Created by georgerapeanu on 28.03.2022.
//

#ifndef C_GRAPH_H
#define C_GRAPH_H
#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <map>


//! the graph exception class
class GraphException{
    //! the message of the exception
    std::string message;
public:
    //! the constructor of the exception
    GraphException(const std::string &msg);
    //! the message of the exception
    std::string what()const;
};

//! the model for the graph class
class Graph{
    //! this is a map that stores all inbound neighbors for an entry
    std::map<std::string, std::vector<std::string> > nin;
    //! this is a map that stores all outbound neighbors for an entry
    std::map<std::string, std::vector<std::string> > nout;
    //! this is a map that stores all the costs for each entry(which is an edge)
    std::map<std::pair<std::string, std::string>, int > cost;
public:
    //! @brief The empty constructor of the graph. Returns an empty graph
    Graph();
    //! @brief The copy constructor of the graph.
    Graph(const Graph &other);
    //! @brief The assignment constructor of the graph
    Graph& operator = (const Graph &other);
    //! @brief the desturctor of the graph
    ~Graph();

    /*!
     * @brief constructor from a given list of vertices and a given list of edges
     * @param vertices the vertices of the graph
     * @param edges the edges of the graph, provided as tuples of (string, string, int)
     */
    Graph(const std::vector<std::string> &vertices, const std::vector<std::tuple<std::string, std::string, int> > &edges);

    //! @brief this function returns a vector containing all vertices
    std::vector<std::string> parse_vertices()const;
    /*!
     * @brief this function returns true if there is an edge from x to y and false otherwise
     * @param x the first vertex
     * @param y the second vertex
     * @return true if there is an edge from x to y false otherwise
     */
    bool is_edge(const std::string &x, const std::string &y);
    /*!
     * @brief this function returns the in degree of a given vertex x
     * @param x the vertex
     * @return the in degree of the specified vertex
     */
    int get_in_degree(const std::string &x);
    /*!
     * @brief this function returns the out degree of a given vertex x
     * @param x the vertex
     * @return the out degree of the specified vertex
     * @raises GraphException if vertex doesn't exist
     */
    int get_out_degree(const std::string &x);
    /*!
     * @brief This function returns a vector containing the endpoints of all edges outbound to x
     * @param x the vertex
     * @return a vector containing the outbound neighbors of x
     * @raises GraphException if vertex doesn't exist
     */
    std::vector<std::string> parse_outbound_edges(const std::string &x);
    /*!
     * @brief This function returns a vector containing the endpoints of all edges inbound to x
     * @param x the vertex
     * @return a vector containing the inbound neighbors of x
     * @raises GraphException if vertex doesn't exist
     */
    std::vector<std::string> parse_inbound_edges(const std::string &x);
    /*!
     * @brief this function returns the cost of the edge from x to y
     * @param x the first vertex
     * @param y the second vertex
     * @return the cost of the edge from x to y
     * @raises GraphException if vertices don't exist
     * @raises GraphException if edge doesn't exist
     */
    int get_edge_cost(const std::string& x, const std::string &y);
    /*!
     * @brief modifies the cost of the edge from x to y
     * @param x the first vertex
     * @param y the second vertex
     * @param z the new cost
     * @raises GraphException if vertices don't exist
     * @raises GraphException if edge doesn't exist
     */
    void modify_edge_cost(const std::string& x, const std::string &y, int z);
    /*!
     * @brief adds a vertex to the graph
     * @param x the vertex
     * @raises GraphException if the vertex already exists
     */
    void add_vertex(const std::string& x);
    /*!
     * @brief removes a vertex from the graph
     * @param x the vertex
     * @raises GraphException if the vertex doesn't exist
     */
    void remove_vertex(const std::string& x);
    /*!
     * @brief adds an edge from x to y with cost z
     * @param x the first vertex
     * @param y the second vertex
     * @param z the cost of the edge
     * @raises GraphException if the vertices don't exist or if the edge already exists
     */
    void add_edge(const std::string& x, const std::string& y, int z);
    /*!
     * @brief removes the edge from x to y
     * @param x the first vertex
     * @param y the second vertex
     * @raises GraphException if the vertices don't exist or the edge doesn't exist
     */
    void remove_edge(const std::string& x, const std::string& y);
    /*!
     * @brief graph equality operator. Checks if the graphs are basicly the same
     * @param other the other graph
     * @return true if they are equal, false otherwise
     */
    bool operator == (const Graph &other)const;
    /*!
     * @brief graph not equal operator. Checks if the graphs are not the same
     * @param other the other graph
     * @return true if they are different, false otherwise
     */
    bool operator != (const Graph &other)const;
};

/*!
 * @brief reads a graph from file
 * It supports 2 formats
 * .txt and  .modified.txt
 *
 * In case of .txt, the file is supposed to look like this:
 *
 *   On the first line, the number n of vertices and the number m of edges;
 *   On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.
 *
 * In case of .modified.txt, the file is supposed to look like this:
 *
 * On the first line, the number n of vertices and the number m of edges
 *
 *   On the second line, a list of the n vertices separated by space
 *   On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.
 *
 * @param filename the file from which to read(name, relative path or absolute path)
 * @return Graph
 * @raises GraphException in case of invalid format
 */
Graph read_graph(const std::string &file);
/*!
 * @brief writes a graph to file
 * This function writes a graph from a file.
 * It supports 1 format
 *      .modified.txt
 *
 *      On the first line, the number n of vertices and the number m of edges
 *      On the second line, a list of the n vertices separated by space
 *      On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.
 *
 *  @param filename the filename to which to read(name, relative path or absolute path), MUST end in .modified.txt
 *  @param graph: the graph to be written
 *  @raises GraphException: if invalid data
 */
void write_graph(const std::string &file, Graph &graph);
/*!
 * @brief This function generates a random graph with n vertices and m edges
 * @param n the number of vertices
 * @param m the number of edges
 * @return the graph
 */
Graph random_graph(int n, int m);

#endif //C_GRAPH_H
