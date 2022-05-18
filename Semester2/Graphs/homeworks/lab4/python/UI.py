#!/usr/bin/python3
import re
import traceback

import UndirectedGraph


def display_edges(edges):
    """This function displays a given list of edges

    :param edges: list of edges represented as tuples
    :type edges: list
    :return: None
    """
    for edge in edges:
        print("Edge between %s and %s with cost %d" % (edge[0], edge[1], edge[2]))


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

def display_graph(graph):
    """displays a graph

    :param graph: the graph
    :type graph: UndirectedGraph.UndirectedGraph
    :return: None
    """
    print("Graph:")
    display_vertices(graph.parse_vertices())
    edges = []
    for vertex in graph.parse_vertices():
        neighbor_list = list(filter(lambda x: x >= vertex, graph.parse_adjacent_edges(vertex)))
        for neighbor in neighbor_list:
            edges.append((vertex, neighbor, graph.get_edge_cost(vertex, neighbor)))
    print("And edges:")
    display_edges(edges)

def main():
    """ The main of the program

    :return: None
    """
    commands_regex = [
        "^ *print +vertices *$",
        "^ *print +is +edge +[^ ]+ +[^ ]+ *$",
        "^ *print +degree +[^ ]+ *$",
        "^ *print +adjacent +edges +[^ ]+ *$",
        "^ *print +edge +cost +[^ ]+ +[^ ]+ *$",
        "^ *modify +edge +cost +[^ ]+ +[^ ]+ +[^ ]+ *$",
        "^ *add +vertex +[^ ]+ *$",
        "^ *remove +vertex +[^ ]+ *$",
        "^ *add +edge +[^ ]+ +[^ ]+ +[^ ]+ *$",
        "^ *remove +edge +[^ ]+ +[^ ]+ *$",
        "^ *read +graph +[^ ]+ *$",
        "^ *write +graph +[^ ]+ *$",
        "^ *random +graph +[^ ]+ +[^ ]+ *$",
        "^ *print +connected +components *$",
        "^ *help *$",
        "^ *exit *$",
        "^ *get +MST *$"
    ]
    ## The help prompt
    help_prompt = "\n".join(
            ["Usage:",
            "print vertices",
            "\tprints all verticies of the graph",
            "print is edge [x] [y]",
            "\tprints True if the edge x-y exists, False otherwise",
            "print degree [x]",
            "\tprints the degree of x",
            "print adjacent edges [x]",
            "\t prints the adjacent edges of x",
            "print edge cost [x] [y]",
            "\tprints the cost of the edge from x to y",
            "modify edge cost [x] [y] [z]",
            "\tsets the edge between x and y to z",
            "add vertex [x]",
            "\tadds the vertex x to the graph",
            "remove vertex [x]",
            "\tremoves the vertex x from the graph",
            "add edge [x] [y] [z]",
            "\tadds an edge between x and y with cost z",
            "remove edge [x] [y]",
            "\tremoves the edge from x to y",
            "read graph [file]",
            "\treads the graph from file",
            "write graph [file]",
            "\twrites the graph to file",
            "random graph [n] [m]",
            "\tgenerates a random graph with n vertices and m edges",
            "print connected components",
            "\tprints all connected components from a graph",
            "get MST",
            "\tDisplays the minimum spanning tree of the graph",
            "help",
            "exit"
            ])

    ## Initializes graph with empty graph
    graph = UndirectedGraph.UndirectedGraph([], [])
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
                print(graph.get_degree(args[2]))
            elif re.match(commands_regex[3], command) is not None:
                adjacent_vertices = graph.parse_adjacent_edges(args[3])
                adjacent_edges = []
                for adjacent in adjacent_vertices:
                    adjacent_edges.append((args[3], adjacent, graph.get_edge_cost(args[3], adjacent)))
                display_edges(adjacent_edges)
            elif re.match(commands_regex[4], command) is not None:
                print(graph.get_edge_cost(args[3], args[4]))
            elif re.match(commands_regex[5], command) is not None:
                graph.modify_edge_cost(args[3], args[4], int(args[5]))
            elif re.match(commands_regex[6], command) is not None:
                graph.add_vertex(args[2])
            elif re.match(commands_regex[7], command) is not None:
                graph.remove_vertex(args[2])
            elif re.match(commands_regex[8], command) is not None:
                graph.add_edge(args[2], args[3], int(args[4]))
            elif re.match(commands_regex[9], command) is not None:
                graph.remove_edge(args[2], args[3])
            elif re.match(commands_regex[10], command) is not None:
                graph = UndirectedGraph.read_graph(args[2])
            elif re.match(commands_regex[11], command) is not None:
                UndirectedGraph.write_graph(args[2], graph)
            elif re.match(commands_regex[12], command) is not None:
                graph = UndirectedGraph.random_graph(int(args[2]), int(args[3]))
            elif re.match(commands_regex[13], command) is not None:
                components = UndirectedGraph.get_connected_components(graph)
                for i in range(len(components)):
                    print("Component %d:" % i)
                    display_graph(components[i])
            elif re.match(commands_regex[14], command) is not None:
                print(help_prompt)
            elif re.match(commands_regex[15], command) is not None:
                break
            elif re.match(commands_regex[16], command) is not None:
                display_graph(UndirectedGraph.get_minimum_spanning_tree(graph))
            else:
                raise Exception("Invalid command!")
            print("Operation successful")
        except Exception as ex:
            print("Error: " + str(ex))
            print(traceback.print_exc())


if __name__ == "__main__":
    main()
