#!/usr/bin/python3
import re
import traceback

import Graph
from math import inf


def display_edges(edges):
    """This function displays a given list of edges

    :param edges: list of edges represented as tuples
    :type edges: list
    :return: None
    """
    for edge in edges:
        print("Edge from %s to %s with cost %d" % (edge[0], edge[1], edge[2]))


def display_vertices(vertices):
    """ This function displays the given vertices

    :param vertices: the vertices
    :type vertices: list
    :return: None
    """
    print("Vertexes: ")
    for vertex in vertices:
        print(vertex, end=" ")
    print("")


def main():
    """ The main of the program

    :return: None
    """
    commands_regex = [
        "^ *print +vertices *$",
        "^ *print +is +edge +[^ ]+ +[^ ]+ *$",
        "^ *print +in +degree +[^ ]+ *$",
        "^ *print +out +degree +[^ ]+ *$",
        "^ *print +outbound +edges +[^ ]+ *$",
        "^ *print +inbound +edges +[^ ]+ *$",
        "^ *print +edge +cost +[^ ]+ +[^ ]+ *$",
        "^ *modify +edge +cost +[^ ]+ +[^ ]+ +[^ ]+ *$",
        "^ *add +vertex +[^ ]+ *$",
        "^ *remove +vertex +[^ ]+ *$",
        "^ *add +edge +[^ ]+ +[^ ]+ +[^ ]+ *$",
        "^ *remove +edge +[^ ]+ +[^ ]+ *$",
        "^ *read +graph +[^ ]+ *$",
        "^ *write +graph +[^ ]+ *$",
        "^ *random +graph +[^ ]+ +[^ ]+ *$",
        "^ *help *$",
        "^ *exit *$",
        "^ *get +TSP *$"
    ]
    ## The help prompt
    help_prompt = "\n".join(
            ["Usage:",
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
            "get TSP",
            "\tgets a low cost hamiltonian cycle",
            "help",
            "exit"
            ])

    ## Initializes graph with empty graph
    graph = Graph.Graph([], [])
    print(help_prompt)
    while True:
        command = input().strip()
        args = list(filter(lambda arg: len(arg) > 0, [arg.strip() for arg in command.split(" ")]))
        try:
            if re.match(commands_regex[0], command) is not None:
                display_vertices(graph.parse_vertices())
            elif re.match(commands_regex[1], command) is not None:
                print(graph.is_edge(args[3], args[4]))
            elif re.match(commands_regex[2], command) is not None:
                print(graph.get_in_degree(args[3]))
            elif re.match(commands_regex[3], command) is not None:
                print(graph.get_out_degree(args[3]))
            elif re.match(commands_regex[4], command) is not None:
                outbound_vertices = graph.parse_outbound_edges(args[3])
                outbound_edges = []
                for outbound in outbound_vertices:
                    outbound_edges.append((args[3], outbound, graph.get_edge_cost(args[3], outbound)))
                display_edges(outbound_edges)
            elif re.match(commands_regex[5], command) is not None:
                inbound_vertices = graph.parse_inbound_edges(args[3])
                inbound_edges = []
                for outbound in inbound_vertices:
                    inbound_edges.append((outbound, args[3], graph.get_edge_cost(outbound, args[3])))
                display_edges(inbound_edges)
            elif re.match(commands_regex[6], command) is not None:
                print(graph.get_edge_cost(args[3], args[4]))
            elif re.match(commands_regex[7], command) is not None:
                graph.modify_edge_cost(args[3], args[4], int(args[5]))
            elif re.match(commands_regex[8], command) is not None:
                graph.add_vertex(args[2])
            elif re.match(commands_regex[9], command) is not None:
                graph.remove_vertex(args[2])
            elif re.match(commands_regex[10], command) is not None:
                graph.add_edge(args[2], args[3], int(args[4]))
            elif re.match(commands_regex[11], command) is not None:
                graph.remove_edge(args[2], args[3])
            elif re.match(commands_regex[12], command) is not None:
                graph = Graph.read_graph(args[2])
            elif re.match(commands_regex[13], command) is not None:
                Graph.write_graph(args[2], graph)
            elif re.match(commands_regex[14], command) is not None:
                graph = Graph.random_graph(int(args[2]), int(args[3]))
            elif re.match(commands_regex[15], command) is not None:
                print(help_prompt)
            elif re.match(commands_regex[16], command) is not None:
                break
            elif re.match(commands_regex[17], command) is not None:
                answer = Graph.get_hamiltonian_path(graph)
                if answer[1] == []:
                    print("No hamiltonian path found")
                else:
                    print("Found hamiltonian path of cost %d" % answer[0])
                    for node in answer[1]:
                        print(node, end=" ")
                    print("")
            else:
                raise Exception("Invalid command!")
            print("Operation successful")
        except Exception as ex:
            print("Error: " + str(ex))
            print(traceback.print_exc())


if __name__ == "__main__":
    main()
