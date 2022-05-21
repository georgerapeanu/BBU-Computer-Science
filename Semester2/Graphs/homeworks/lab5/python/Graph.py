#!/usr/bin/python3
import random
from copy import deepcopy
from math import inf

class Graph:
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
        self.__nin = {}
        self.__nout = {}
        self.__costs = {}
        self._last_dist = None
        self._last_prev = None

        if not isinstance(vertices, list) or not isinstance(edges, list):
            raise Exception("Arguments do not have the required type")

        for node in vertices:
            if not isinstance(node, str):
                raise Exception("Vertices do not have the required type")
            self.__nin[node] = []
            self.__nout[node] = []

        for edge in edges:
            if not isinstance(edge, tuple) or len(edge) != 3 or type(edge[2]) != int:
                raise Exception("Malformed edge")
            if edge[0] not in self.__nin or edge[1] not in self.__nout:
                raise Exception("Initial edges don't have both endpoints in the initial vertices")
            if (edge[0], edge[1]) in self.__costs:
                raise Exception("Edge already exists")
            self.__nin[edge[1]].append(edge[0])
            self.__nout[edge[0]].append(edge[1])
            self.__costs[(edge[0], edge[1])] = edge[2]

    def parse_vertices(self):
        """ This function returns an iterable containing nodes

        The nodes are deepcopied, in order to avoid being modified from the outside
        :return: iterator through a list of deepcopied nodes
        """
        return deepcopy([node for node in self.__nin])

    def is_edge(self, x, y):
        """ This function returns True if the edge x->y exists, false otherwise

        :param x: the first vertex
        :type x: str
        :param y: the second vertex
        :type y: str
        :return: True if an edge exists, false otherwise
        :raises Exception: if x or y are not vertices
        """

        if x not in self.__nout or y not in self.__nin:
            raise Exception("Vertices invalid")
        return (x, y) in self.__costs.keys()

    def get_in_degree(self, x):
        """ This function returns the in degree of a vertex

        :param x: the vertex
        :type x: str
        :return: the in degree of the vertex x
        :raises Exception: if x doesn't exist
        """

        if x not in self.__nin:
            raise Exception("Vertex doesn't exist")

        return len(self.__nin[x])

    def get_out_degree(self, x):
        """ This function returns the out degree of a vertex

        :param x: the vertex
        :type x: str
        :return: the out degree of the vertex x
        :raises Exception: if x doesn't exist
        """

        if x not in self.__nout:
            raise Exception("Vertex doesn't exist")

        return len(self.__nout[x])

    def parse_outbound_edges(self, x):
        """ This function returns an iterable of deepcopied vertices

        :param x: the vertex for which to retrieve the iterator
        :return: iterator to a deepcopied list of outbound vertices
        :raise Exception: if the vertex doesn't exist
        """
        if x not in self.__nout:
            raise Exception("Vertex doesn't exist")
        return deepcopy(self.__nout[x])

    def parse_inbound_edges(self, x):
        """ This function returns an iterable of deepcopied vertices

        :param x: the vertex for which to retrieve the iterator
        :return: iterator to a deepcopied list of inbound vertices
        :raise Exception: if the vertex doesn't exist
        """

        if x not in self.__nout:
            raise Exception("Vertex doesn't exist")
        return deepcopy(self.__nin[x])

    def get_edge_cost(self, x, y):
        """ This function returns the cost of the edge from x to y

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
        self._last_dist = None
        self._last_prev = None

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
        if x in self.__nout.keys():
            raise Exception("Vertex already exists")

        self.__nin[x] = []
        self.__nout[x] = []
        self._last_dist = None
        self._last_prev = None

    def remove_vertex(self, x):
        """ This function removes the vertex x from the graph

        :param x: the vertex to be removed
        :type x: str
        :raises Exception: if x doesn't exist
        """

        if x not in self.__nout.keys():
            raise Exception("Vertex doesn't exist")

        for outbound in self.__nout[x]:
            del self.__costs[(x, outbound)]
            self.__nin[outbound].remove(x)
        for inbound in self.__nin[x]:
            del self.__costs[(inbound, x)]
            self.__nout[inbound].remove(x)

        del self.__nout[x]
        del self.__nin[x]
        self._last_dist = None
        self._last_prev = None

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

        if y not in self.__nin or x not in self.__nout:
            raise Exception("Vertices don't exist")

        if (x, y) in self.__costs:
            raise Exception("Edge already exists")

        self.__nin[y].append(x)
        self.__nout[x].append(y)
        self.__costs[(x, y)] = z
        self._last_dist = None
        self._last_prev = None

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

        self.__nin[y].remove(x)
        self.__nout[x].remove(y)
        del self.__costs[(x, y)]
        self._last_dist = None
        self._last_prev = None

    def __eq__(self, other):
        """ This function return True if two graphs are the same, False otherwise

        :param other: the other graph
        :type other: Graph
        :return: True if same graph, False otherwise
        """

        if sorted(self.__nin.keys()) != sorted(other.__nin.keys()) or sorted(self.__nout.keys()) != sorted(other.__nout.keys()):
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
        On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.

        In case of .modified.txt, the file is supposed to look like this:

        On the first line, the number n of vertices and the number m of edges
        On the second line, a list of the n vertices separated by space
        On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.

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

    return Graph(vertices, edges)


def write_graph(filename, graph):
    """ This function writes a graph from a file.
        It supports 1 format
        .modified.txt

        On the first line, the number n of vertices and the number m of edges
        On the second line, a list of the n vertices separated by space
        On each of the following m lines, three numbers, x, y and c, describing an edge: the origin, the target and the cost of that edge.

    :param filename: the filename to which to read(name, relative path or absolute path), MUST end in .modified.txt
    :type filename: str
    :param graph: the graph to be written
    :type graph: Graph
    :raises Exception: if invalid data
    """

    if not isinstance(filename, str) or not filename.endswith(".modified.txt"):
        raise Exception("invalid filename")

    if not isinstance(graph, Graph):
        raise Exception("Invalid arguments")

    with open(filename, "w") as f:
        vertices = graph.parse_vertices()
        edges = []
        for vertex in vertices:
            for outbound in graph.parse_outbound_edges(vertex):
                edges.append((vertex, outbound, graph.get_edge_cost(vertex, outbound)))
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

    if n < 0 or m < 0 or m > n * n:
        raise Exception("Bad arguments")

    graph = Graph([str(x) for x in range(0, n)], [])

    possible_edges = []
    for i in range(0, n):
        for j in range(0, n):
            possible_edges.append((i, j))

    random.shuffle(possible_edges)

    for i in range(0, m):
        graph.add_edge(str(possible_edges[i][0]), str(possible_edges[i][1]), random.randint(-10**9, 10**9))

    return graph


def get_hamiltonian_path(graph):
    """ This function get a hamiltonian path in the graph

    :param graph: the graph
    :type graph: Graph
    :return: tuple of (the cost, a list of nodes which represents the path)
    """

    def backtracking(node, path, cost):
        """ gets a low cost hamiltonian path using backtracking

        :param node: the current node
        :type node: str
        :param path: the path of the nodes so far
        :type path: list
        :param cost: the current cost
        :type cost: int
        :return:
        """
        if len(path) >= len(list(graph.parse_vertices())):
            if path[0] in graph.parse_outbound_edges(path[-1]):
                return (cost + graph.get_edge_cost(path[-1], path[0]), deepcopy(path))
            return (0, [])
        neighbors = graph.parse_outbound_edges(node)
        for i in range(len(neighbors)):
            neighbors[i] = (graph.get_edge_cost(node, neighbors[i]), neighbors[i])
        neighbors = sorted(neighbors)
        for neighbor_cost, neighbor in neighbors:
            if neighbor in path:
                continue
            path.append(neighbor)
            tmp = backtracking(neighbor, path, cost + neighbor_cost)
            if tmp != (0, []):
                return tmp
            path.pop()
        return (0, [])

    if len(list(graph.parse_vertices())) == 0:
        return (0, [])

    return backtracking(list(graph.parse_vertices())[0], [list(graph.parse_vertices())[0]], 0)
