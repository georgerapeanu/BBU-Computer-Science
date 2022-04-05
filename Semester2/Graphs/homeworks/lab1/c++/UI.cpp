/*!
 * @file UI.cpp this file contains the ui of the application. It also serves as the main file
 */

#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "Graph.h"
#include <regex>

using namespace std;

/*!
 * @brief this function displays a vector o edges
 * @param edges the vector containing the edges
 */
void display_edges(const vector<tuple<string, string, int> > &edges){
    for(const auto& edge: edges){
        cout << "edge from " << get<0>(edge) << " to " << get<1>(edge) << " with cost " <<  get<2>(edge) << endl;
    }
}

/*!
 * This function displays the given vertices
 * @param vertices the vector of vertices
 */
void display_vertices(const vector<string> &vertices){
    cout << "Vertexes" << endl;
    for(const auto& vertex:vertices){
        cout << vertex << " ";
    }
    cout << endl;
}

/*!
 * This function displays a given help prompt
 * @param help_prompt
 */
void display_help(vector<string> &help_prompt){
    for(const auto &it:help_prompt){
        cout << it << endl;
    }
}

/*!
 * This function splits a given string by a separator
 * @param s the string
 * @param separator the separator
 * @return a vector containing the fields of the result
 */
vector<string> my_split(string s, char separator){
    vector<string> ans;
    string curr;

    for(auto it:s){
        if(it == separator){
            if(!curr.empty()){
                ans.push_back(curr);
            }
            curr = "";
        }else{
            curr += it;
        }
    }
    if(!curr.empty()){
        ans.push_back(curr);
    }
    return ans;
}

/*!
 * the main of the file
 * @return 0 hopefully
 */
int main() {
    vector<regex> commands_regex = {
            regex("^ *print +vertices *$"),
            regex("^ *print +is +edge +[^ ]+ +[^ ]+ *$"),
            regex("^ *print +in +degree +[^ ]+ *$"),
            regex("^ *print +out +degree +[^ ]+ *$"),
            regex("^ *print +outbound +edges +[^ ]+ *$"),
            regex("^ *print +inbound +edges +[^ ]+ *$"),
            regex("^ *print +edge +cost +[^ ]+ +[^ ]+ *$"),
            regex("^ *modify +edge +cost +[^ ]+ +[^ ]+ +[^ ]+ *$"),
            regex("^ *add +vertex +[^ ]+ *$"),
            regex("^ *remove +vertex +[^ ]+ *$"),
            regex("^ *add +edge +[^ ]+ +[^ ]+ +[^ ]+ *$"),
            regex("^ *remove +edge +[^ ]+ +[^ ]+ *$"),
            regex("^ *read +graph +[^ ]+ *$"),
            regex("^ *write +graph +[^ ]+ *$"),
            regex("^ *random +graph +[^ ]+ +[^ ]+ *$"),
            regex("^ *help *$"),
            regex("^ *exit *$")
    };

    vector<string> help_prompt = {"Usage:",
                                  "print vertices",
                                  "\tprints all verticies of the graph",
                                  "print is edge [x] [y]",
                                  "\tprints True if the edge x->y exists, False otherwise",
                                  "print in degree [x]",
                                  "\tprints the in degree of x",
                                  "print out degree [x]",
                                  "\tprints the out degree of x",
                                  "print outbound edges [x]",
                                  "\t prints the outbound edges of x",
                                  "print inbound edges [x]",
                                  "\tprints the inbound edges of x",
                                  "print edge cost [x] [y]",
                                  "\tprints the cost of the edge from x to y",
                                  "modify edge cost [x] [y] [z]",
                                  "\tsets the edge from x to y to z",
                                  "add vertex [x]",
                                  "\tadds the vertex x to the graph",
                                  "remove vertex [x]",
                                  "\tremoves the vertex x from the graph",
                                  "add edge [x] [y] [z]",
                                  "\tadds an edge from x to y with cost z",
                                  "remove edge [x] [y]",
                                  "\tremoves the edge from x to y",
                                  "read graph [file]",
                                  "\treads the graph from file",
                                  "write graph [file]",
                                  "\twrites the graph to file",
                                  "random graph [n] [m]",
                                  "\tgenerates a random graph with n vertices and m edges",
                                  "help",
                                  "exit"
    };
    Graph graph({}, {});
    display_help(help_prompt);
    while (true) {
        string command;
        std::cmatch base_match;
        getline(cin, command);
        vector<string> args = my_split(command, ' ');
        try {
            if(regex_search( command,commands_regex[0])) {
                display_vertices(graph.parse_vertices());
            }else if(regex_search( command,commands_regex[1])){
                cout << (graph.is_edge(args[3], args[4]) ? "true":"false") << endl;
            }else if(regex_search( command, commands_regex[2])){
                cout << (graph.get_in_degree(args[3])) << endl;
            }else if(regex_search( command,commands_regex[3])){
                cout << graph.get_out_degree(args[3]) << endl;
            }else if(regex_search( command,commands_regex[4])){
                vector<string> outbound_vertices = graph.parse_outbound_edges(args[3]);
                vector<tuple<string, string, int> > outbound_edges = {};
                for(const auto &outbound: outbound_vertices){
                    outbound_edges.push_back({args[3], outbound, graph.get_edge_cost(args[3], outbound)});
                }
                display_edges(outbound_edges);
            }else if(regex_search( command,commands_regex[5])){
                vector<string> inbound_vertices = graph.parse_inbound_edges(args[3]);
                vector<tuple<string, string, int> > inbound_edges = {};
                for(const auto &inbound: inbound_vertices){
                    inbound_edges.push_back({inbound, args[3], graph.get_edge_cost(inbound, args[3])});
                }
                display_edges(inbound_edges);
            }else if(regex_search( command,commands_regex[6])){
                cout << graph.get_edge_cost(args[3], args[4]);
            }else if(regex_search( command,commands_regex[7])){
                graph.modify_edge_cost(args[3], args[4], stoi(args[5]));
            }
            else if(regex_search( command,commands_regex[8])){
                graph.add_vertex(args[2]);
            }else if(regex_search( command,commands_regex[9])){
                graph.remove_vertex(args[2]);
            }else if(regex_search( command,commands_regex[10])){
                graph.add_edge(args[2], args[3], stoi(args[4]));
            }else if(regex_search( command,commands_regex[11])){
                graph.remove_edge(args[2], args[3]);
            }else if(regex_search( command,commands_regex[12])){
                graph = read_graph(args[2]);
            }else if(regex_search( command,commands_regex[13])){
                write_graph(args[2], graph);
            }else if(regex_search( command,commands_regex[14])){
                graph = random_graph(stoi(args[2]), stoi(args[3]));
            }else if(regex_search( command,commands_regex[15])){
                display_help(help_prompt);
            }else if(regex_search( command,commands_regex[16])){
                break;
            }else{
                throw GraphException("Invalid command");
            }
            cout << "Operation successful" << endl;
        }
        catch (const GraphException &ex) {
            cout << "Error: " << ex.what() << endl;
        }
    }
    return 0;
}