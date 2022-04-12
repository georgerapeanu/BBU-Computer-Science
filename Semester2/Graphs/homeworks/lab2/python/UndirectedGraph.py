#!/usr/bin/python3
import random
from copy import deepcopy


class UndirectedGraph:
    def __init__(self, vertices, edges):
        """ Constructor for graph.

        :param vertices: a list of initial vertices
        :type vertices: a list of strings
        :param edges: a list of tuples (a, b, c), meaning there is an edge from a to b with cost c
        :type edges: list of tuples
        :raises Exception: if the vertices or edges do not respect the specified format
        :raises Exception: if not all nodes used by the edges are in the initial vertex list
        :raises Exception: if there are multiple edges with the same source and destination
        """
        self.__neighbors = {}
        self.__costs = {}

        if not isinstance(vertices, list) or not isinstance(edges, list):
            raise Exception("Arguments do not have the required type")

        for node in vertices:
            if not isinstance(node, str):
                raise Exception("Vertices do not have the required type")
            self.__neighbors[node] = []

        for edge in edges:
            if not isinstance(edge, tuple) or len(edge) != 3 or type(edge[2]) != int:
                raise Exception("Malformed edge")
            if edge[0] not in self.__neighbors or edge[1] not in self.__neighbors:
                raise Exception("Initial edges don't have both endpoints in the initial vertices")
            if (edge[0], edge[1]) in self.__costs:
                raise Exception("Edge already exists")
            self.__neighbors[edge[1]].append(edge[0])
            self.__costs[(edge[0], edge[1])] = edge[2]
            if edge[0] != edge[1]:
                self.__neighbors[edge[0]].append(edge[1])
                self.__costs[(edge[1], edge[0])] = edge[2]

    def has_vertex(self, vertex):
        """ This function returns true if the provided vertex exists, false otherwise

        :param vertex: the vertex
        :type vertex: str
        :return: boolean
        """
        if not isinstance(vertex, str):
            raise Exception("Vertex should be str")
        return vertex in self.__neighbors

    def parse_vertices(self):
        """ This function returns an iterable containing nodes

        The nodes are deepcopied, in order to avoid being modified from the outside
        :return: iterator through a list of deepcopied nodes
        """
        for node in self.__neighbors:
            yield deepcopy(node)

    def is_edge(self, x, y):
        """ This function returns True if the edge x-y exists, false otherwise

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :return: True if an edge exists, false otherwise
        :raises Exception: if x or y are not vertices
        """

        if x not in self.__neighbors or y not in self.__neighbors:
            raise Exception("Vertices invalid")
        return (x, y) in self.__costs.keys()

    def get_degree(self, x):
        """ This function returns the degree of a vertex

        :param x: the vertex
        :type x: str
        :return: the in degree of the vertex x
        :raises Exception: if x doesn't exist
        """

        if x not in self.__neighbors:
            raise Exception("Vertex doesn't exist")

        return len(self.__neighbors[x])

    def parse_adjacent_edges(self, x):
        """ This function returns an iterable of deepcopied vertices

        :param x: the vertex for which to retrieve the iterator
        :return: iterator to a deepcopied list of outbound vertices
        :raise Exception: if the vertex doesn't exist
        """
        if x not in self.__neighbors:
            raise Exception("Vertex doesn't exist")
        for node in self.__neighbors[x]:
            yield deepcopy(node)

    def get_edge_cost(self, x, y):
        """ This function returns the cost of the edge between x and y

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :return: the cost of the edge from x to y
        :raises Exception: if there is no edge from x to y
        """

        if (x, y) not in self.__costs:
            raise Exception("Edge doesn't exist")
        return self.__costs[(x, y)]

    def modify_edge_cost(self, x, y, z):
        """ This function modifies the cost of the edge from x to y

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :param z: the new cost
        :type z: int
        :raises Exception: if there is no edge from x to y
        """

        if (x, y) not in self.__costs:
            raise Exception("Edge doesn't exist")
        if type(z) != int:
            raise Exception("Cost isn't int")
        self.__costs[(x, y)] = z
        self.__costs[(y, x)] = z

    def copy(self):
        """ This function retrieves a copy of the current graph

        :return: a Graph copy
        """
        return deepcopy(self)

    def add_vertex(self, x):
        """ This function adds the vertex x to the graph

        :param x: the vertex to be added
        :type x: str
        :raises Exception: if x is not string
        :raises Exception: if x already exists
        """

        if not isinstance(x, str):
            raise Exception("Vertex doesn't have the required type")
        if x in self.__neighbors.keys():
            raise Exception("Vertex already exists")

        self.__neighbors[x] = []

    def remove_vertex(self, x):
        """ This function removes the vertex x from the graph

        :param x: the vertex to be removed
        :type x: str
        :raises Exception: if x doesn't exist
        """

        if x not in self.__neighbors.keys():
            raise Exception("Vertex doesn't exist")

        for neighbor in self.__neighbors[x]:
            del self.__costs[(x, neighbor)]
            if neighbor != x:
                del self.__costs[(neighbor, x)]
                self.__neighbors[neighbor].remove(x)

        del self.__neighbors[x]

    def add_edge(self, x, y, z):
        """ This function adds the edge from x to y to the graph

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :param z: the cost
        :type z: int
        :raises Exception: if types do not follow the specification
        :raises Exception: if nodes do not exist
        :raises Exception: if edge already exists
        """
        if not isinstance(x, str) or not isinstance(y, str) or not isinstance(z, int):
            raise Exception("Arguments do not have the correct types")

        if y not in self.__neighbors or x not in self.__neighbors:
            raise Exception("Vertices don't exist")

        if (x, y) in self.__costs:
            raise Exception("Edge already exists")

        self.__neighbors[y].append(x)
        self.__costs[(x, y)] = z
        if x != y:
            self.__neighbors[x].append(y)
            self.__costs[(y, x)] = z

    def remove_edge(self, x, y):
        """ This function removes the edge from x to y from the graph

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :raises Exception: if edge already exists
        """

        if (x, y) not in self.__costs:
            raise Exception("Edge doesn't exist")

        self.__neighbors[y].remove(x)
        del self.__costs[(x, y)]
        if x != y:
            self.__neighbors[x].remove(y)
            del self.__costs[(y, x)]

    def __eq__(self, other):
        """ This function return True if two graphs are the same, False otherwise

        :param other: the other graph
        :type other: UndirectedGraph
        :return: True if same graph, False otherwise
        """

        if sorted(self.__neighbors.keys()) != sorted(other.__neighbors.keys()):
            return False

        if sorted(self.__costs.keys()) != sorted(other.__costs.keys()):
            return False

        for key in self.__costs.keys():
            if self.__costs[key] != other.__costs[key]:
                return False

        return True


def read_graph(filename):
    """ This function reads a graph from a file.
        It supports 2 formats
        .txt and  .modified.txt

        In case of .txt, the file is supposed to look like this:

        On the first line, the number n of vertices and the number m of edges;
        On each of the following m lines, three numbers, x, y and c, describing an edge.

        In case of .modified.txt, the file is supposed to look like this:

        On the first line, the number n of vertices and the number m of edges
        On the second line, a list of the n vertices separated by space
        On each of the following m lines, three numbers, x, y and c, describing an edge.

    :param filename: the file from which to read(name, relative path or absolute path)
    :type filename: str
    :return: Graph
    :raises Exception: in case of invalid format
    """

    if not isinstance(filename, str) or not filename.endswith(".txt"):
        raise Exception("invalid filename")

    n = m = 0
    vertices = []
    edges = []

    with open(filename, "r") as f:
        lines = list(f.readlines())
        for i in range(0, len(lines)):
            lines[i] = lines[i].strip()
        lines = list(filter(lambda x: len(x) > 0, lines))
        metadata = lines[0].strip().split(" ")
        if len(metadata) != 2:
            raise Exception("invalid format")
        n, m = int(metadata[0]), int(metadata[1])

        if filename.endswith(".modified.txt"):
            if len(lines) != m + 2:
                raise Exception("invalid format")
            if len(lines[1].strip().split(" ")) != n:
                raise Exception("invalid format")

            for i in range(0, n):
                vertices.append(lines[1].strip().split(" ")[i])

            for i in range(2, len(lines)):
                line_data = lines[i].strip().split(" ")
                if len(line_data) != 3:
                    raise Exception("invalid format")
                edges.append((line_data[0], line_data[1], int(line_data[2])))
        else:
            if len(lines) != m + 1:
                raise Exception("invalid format")
            for i in range(0, n):
                vertices.append(str(i))
            for i in range(1, len(lines)):
                line_data = lines[i].strip().split(" ")
                if len(line_data) != 3:
                    raise Exception("invalid format")
                edges.append((line_data[0], line_data[1], int(line_data[2])))
    return UndirectedGraph(vertices, edges)


def write_graph(filename, graph):
    """ This function writes a graph from a file.
        It supports 1 format
        .modified.txt

        On the first line, the number n of vertices and the number m of edges
        On the second line, a list of the n vertices separated by space
        On each of the following m lines, three numbers, x, y and c, describing an edge.

    :param filename: the filename to which to read(name, relative path or absolute path), MUST end in .modified.txt
    :type filename: str
    :param graph: the graph to be written
    :type graph: UndirectedGraph
    :raises Exception: if invalid data
    """

    if not isinstance(filename, str) or not filename.endswith(".modified.txt"):
        raise Exception("invalid filename")

    if not isinstance(graph, UndirectedGraph):
        raise Exception("Invalid arguments")

    with open(filename, "w") as f:
        vertices = list(graph.parse_vertices())
        edges = []
        for vertex in vertices:
            for neighbor in graph.parse_adjacent_edges(vertex):
                if neighbor >= vertex:
                    edges.append((vertex, neighbor, graph.get_edge_cost(vertex, neighbor)))
        f.write("%d %d\n" % (len(vertices), len(edges)))
        for vertex in vertices:
            f.write("%s " % vertex)
        f.write("\n")
        for edge in edges:
            f.write("%s %s %d\n" % (edge[0], edge[1], edge[2]))


def random_graph(n, m):
    """ This function creates a random graph with specified number of vertices and edges

    :param n: the number of vertices
    :type n: int
    :param m: the number of edges
    :type m: int
    :return: a graph with specified parameters
    :raises Exception: if invalid parameters
    """

    if not isinstance(n, int) or not isinstance(m, int):
        raise Exception("Arguments have invalid types")

    if n < 0 or m < 0 or m > n * (n + 1) // 2:
        raise Exception("Bad arguments")

    graph = UndirectedGraph([str(x) for x in range(0, n)], [])

    possible_edges = []
    for i in range(0, n):
        for j in range(i, n):
            possible_edges.append((i, j))

    random.shuffle(possible_edges)

    for i in range(0, m):
        graph.add_edge(str(possible_edges[i][0]), str(possible_edges[i][1]), random.randint(-10**9, 10**9))

    return graph


def get_connected_components(graph):
    """ Returns a list of UndirectedGraph-s representing the connected component of the given graph

    :param graph: the graph
    :type graph: UndirectedGraph
    :return: list of UndirectedGraph
    """

    def dfs(vertex, component, visited):
        """ This function is to be used only in the get_connected_components function
            It implements a dfs, that adds to the supplied component the new vertices and edges
            It also needs a visited dictionary, for it to keep track of what has been visited so far
            It implements dfs in a non-recursive way
        :param vertex: the current vertex
        :type vertex: str
        :param component: the component in which to save data
        :type component: UndirectedGraph
        :param visited: the dictionary of visited vertices
        :type visited: dict
        :return: None
        """
        dfs_stack = [vertex]
        while len(dfs_stack) != 0:
            vertex = dfs_stack.pop()
            if vertex not in visited:
                visited[vertex] = True
                component.add_vertex(vertex)
                for neighbor in graph.parse_adjacent_edges(vertex):
                    if neighbor not in visited:
                        dfs_stack.append(neighbor)
                    else:
                        component.add_edge(vertex, neighbor, graph.get_edge_cost(vertex, neighbor))

    ans = []
    visited = {}
    for vertex in graph.parse_vertices():
        if vertex not in visited:
            ans.append(UndirectedGraph([], []))
            dfs(vertex, ans[-1], visited)
    return ans
