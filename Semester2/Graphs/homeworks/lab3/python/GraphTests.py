from Graph import Graph, read_graph, write_graph, random_graph, floyd_warshall
from math import inf
import unittest


class GraphTests(unittest.TestCase):

    def setUp(self):
        self.graph = Graph(["1", "2", "3"], [("1", "2", 0), ("2", "1", 10), ("1", "3", 3)])

    def test_constructor(self):
        with self.assertRaises(Exception):
            Graph(1, [])
        with self.assertRaises(Exception):
            Graph([], "")
        with self.assertRaises(Exception):
            graph = Graph([1, 2, 3], [(1, 2, 0)])

        with self.assertRaises(Exception):
            graph = Graph(["1", "2", "3"], [(1, 2, 0)])

        with self.assertRaises(Exception):
            graph = Graph(["1", "2", "3"], [("1", "2", "0")])

        with self.assertRaises(Exception):
            graph = Graph(["1", "2", "3"], [("1", "2", 0), ("2", "1", 10), ("1", "2", 3)])
        graph = Graph(["1", "2", "3"], [("1", "2", 0), ("2", "1", 10), ("1", "3", 3)])

    def test_parse_vertices(self):
        self.assertEqual(self.graph.parse_vertices(), ["1", "2", "3"])

    def test_is_edge(self):
        with self.assertRaises(Exception):
            self.graph.is_edge(1, 2)
        self.assertEqual(self.graph.is_edge("1", "1"), False)
        self.assertEqual(self.graph.is_edge("1", "2"), True)
        self.assertEqual(self.graph.is_edge("1", "3"), True)
        self.assertEqual(self.graph.is_edge("2", "1"), True)
        self.assertEqual(self.graph.is_edge("2", "2"), False)
        self.assertEqual(self.graph.is_edge("2", "3"), False)
        self.assertEqual(self.graph.is_edge("3", "1"), False)
        self.assertEqual(self.graph.is_edge("3", "2"), False)
        self.assertEqual(self.graph.is_edge("3", "3"), False)

    def test_get_in_degree(self):
        with self.assertRaises(Exception):
            self.graph.get_in_degree(10)
        with self.assertRaises(Exception):
            self.graph.get_in_degree("10")
        self.assertEqual(self.graph.get_in_degree("1"), 1)
        self.assertEqual(self.graph.get_in_degree("2"), 1)
        self.assertEqual(self.graph.get_in_degree("3"), 1)

    def test_get_out_degree(self):
        with self.assertRaises(Exception):
            self.graph.get_out_degree(10)
        with self.assertRaises(Exception):
            self.graph.get_out_degree("10")
        self.assertEqual(self.graph.get_out_degree("1"), 2)
        self.assertEqual(self.graph.get_out_degree("2"), 1)
        self.assertEqual(self.graph.get_out_degree("3"), 0)

    def test_parse_outbound_edges(self):
        with self.assertRaises(Exception):
            self.graph.parse_outbound_edges(10)
        with self.assertRaises(Exception):
            self.graph.parse_outbound_edges("4")
        self.assertEqual(self.graph.parse_outbound_edges("1"), ["2", "3"])
        self.assertEqual(self.graph.parse_outbound_edges("2"), ["1"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])

    def test_parse_inbound_edges(self):
        with self.assertRaises(Exception):
            self.graph.parse_inbound_edges(10)
        with self.assertRaises(Exception):
            self.graph.parse_inbound_edges("4")

        self.assertEqual(self.graph.parse_inbound_edges("1"), ["2"])
        self.assertEqual(self.graph.parse_inbound_edges("2"), ["1"])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["1"])

    def test_get_edge_cost(self):
        with self.assertRaises(Exception):
            self.graph.get_edge_cost(3, 1)
        with self.assertRaises(Exception):
            self.graph.get_edge_cost("3", "1")
        self.assertEqual(self.graph.get_edge_cost("1", "2"), 0)
        self.assertEqual(self.graph.get_edge_cost("2", "1"), 10)
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)

    def test_modify_edge_cost(self):
        with self.assertRaises(Exception):
            self.graph.modify_edge_cost(3, 1, 10)
        with self.assertRaises(Exception):
            self.graph.modify_edge_cost("3", "1", 10)
        with self.assertRaises(Exception):
            self.graph.modify_edge_cost("2", "1", "10")
        self.graph.modify_edge_cost("2", "1", -7)
        self.assertEqual(self.graph.get_edge_cost("1", "2"), 0)
        self.assertEqual(self.graph.get_edge_cost("2", "1"), -7)
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)

    def test_copy(self):
        graph2 = self.graph.copy()
        self.graph.modify_edge_cost("2", "1", -7)
        self.assertEqual(graph2.get_edge_cost("1", "2"), 0)
        self.assertEqual(graph2.get_edge_cost("2", "1"), 10)
        self.assertEqual(graph2.get_edge_cost("1", "3"), 3)
        self.assertEqual(graph2.parse_outbound_edges("1"), ["2", "3"])
        self.assertEqual(graph2.parse_outbound_edges("2"), ["1"])
        self.assertEqual(graph2.parse_outbound_edges("3"), [])
        self.assertEqual(graph2.parse_inbound_edges("1"), ["2"])
        self.assertEqual(graph2.parse_inbound_edges("2"), ["1"])
        self.assertEqual(graph2.parse_inbound_edges("3"), ["1"])
        self.assertEqual(graph2.parse_vertices(), ["1", "2", "3"])

    def test_add_vertex(self):
        with self.assertRaises(Exception):
            self.graph.add_vertex(1)
        with self.assertRaises(Exception):
            self.graph.add_vertex("1")
        self.graph.add_vertex("4")
        self.graph.add_vertex("10")
        self.assertEqual(self.graph.get_edge_cost("1", "2"), 0)
        self.assertEqual(self.graph.get_edge_cost("2", "1"), 10)
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)
        self.assertEqual(self.graph.parse_outbound_edges("1"), ["2", "3"])
        self.assertEqual(self.graph.parse_outbound_edges("2"), ["1"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])
        self.assertEqual(self.graph.parse_inbound_edges("1"), ["2"])
        self.assertEqual(self.graph.parse_inbound_edges("2"), ["1"])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["1"])
        self.assertEqual(self.graph.parse_vertices(), ["1", "2", "3", "4", "10"])

    def test_remove_vertex(self):
        with self.assertRaises(Exception):
            self.graph.remove_vertex(1)
        with self.assertRaises(Exception):
            self.graph.remove_vertex("10")
        self.graph.remove_vertex("2")
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)
        self.assertEqual(self.graph.parse_outbound_edges("1"), ["3"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])
        self.assertEqual(self.graph.parse_inbound_edges("1"), [])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["1"])
        self.assertEqual(self.graph.parse_vertices(), ["1", "3"])

    def test_add_edge(self):
        with self.assertRaises(Exception):
            self.graph.add_edge(1, "2", 10)
        with self.assertRaises(Exception):
            self.graph.add_edge("1", 2, 10)
        with self.assertRaises(Exception):
            self.graph.add_edge("1", "2", 10)
        with self.assertRaises(Exception):
            self.graph.add_edge("3", "2", "10")
        with self.assertRaises(Exception):
            self.graph.add_edge("3", "4", 10)
        self.graph.add_vertex("10")
        self.graph.add_vertex("4")
        self.graph.add_edge("10", "2", 1)
        self.graph.add_edge("10", "1", 10)
        self.graph.add_edge("1", "10", 3)
        self.graph.add_edge("2", "3", 4)
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)
        self.assertEqual(self.graph.get_edge_cost("10", "2"), 1)
        self.assertEqual(self.graph.get_edge_cost("10", "1"), 10)
        self.assertEqual(self.graph.get_edge_cost("1", "10"), 3)
        self.assertEqual(self.graph.get_edge_cost("2", "3"), 4)
        self.assertEqual(self.graph.parse_outbound_edges("1"), ["2", "3", "10"])
        self.assertEqual(self.graph.parse_outbound_edges("2"), ["1", "3"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])
        self.assertEqual(self.graph.parse_outbound_edges("4"), [])
        self.assertEqual(self.graph.parse_outbound_edges("10"), ["2", "1"])
        self.assertEqual(self.graph.parse_inbound_edges("1"), ["2", "10"])
        self.assertEqual(self.graph.parse_inbound_edges("2"), ["1", "10"])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["1", "2"])
        self.assertEqual(self.graph.parse_inbound_edges("10"), ["1"])
        self.assertEqual(self.graph.parse_inbound_edges("4"), [])
        self.assertEqual(self.graph.parse_vertices(), ["1", "2", "3", "10", "4"])

    def test_remove_edge(self):
        with self.assertRaises(Exception):
            self.graph.remove_edge(1, "2")
        with self.assertRaises(Exception):
            self.graph.remove_edge("1", 2)
        with self.assertRaises(Exception):
            self.graph.remove_edge("2", "3")
        with self.assertRaises(Exception):
            self.graph.remove_edge("3", "2")
        with self.assertRaises(Exception):
            self.graph.remove_edge("3", "4")
        self.graph.add_vertex("10")
        self.graph.add_vertex("4")
        self.graph.add_edge("10", "2", 1)
        self.graph.add_edge("10", "1", 10)
        self.graph.add_edge("1", "10", 3)
        self.graph.remove_edge("1", "2")
        self.graph.remove_edge("2", "1")
        self.graph.add_edge("2", "3", 4)
        self.assertEqual(self.graph.get_edge_cost("1", "3"), 3)
        self.assertEqual(self.graph.get_edge_cost("10", "2"), 1)
        self.assertEqual(self.graph.get_edge_cost("10", "1"), 10)
        self.assertEqual(self.graph.get_edge_cost("1", "10"), 3)
        self.assertEqual(self.graph.get_edge_cost("2", "3"), 4)
        self.assertEqual(self.graph.parse_outbound_edges("1"), ["3", "10"])
        self.assertEqual(self.graph.parse_outbound_edges("2"), ["3"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])
        self.assertEqual(self.graph.parse_outbound_edges("4"), [])
        self.assertEqual(self.graph.parse_outbound_edges("10"), ["2", "1"])
        self.assertEqual(self.graph.parse_inbound_edges("1"), ["10"])
        self.assertEqual(self.graph.parse_inbound_edges("2"), ["10"])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["1", "2"])
        self.assertEqual(self.graph.parse_inbound_edges("10"), ["1"])
        self.assertEqual(self.graph.parse_inbound_edges("4"), [])
        self.assertEqual(self.graph.parse_vertices(), ["1", "2", "3", "10", "4"])
        self.graph.remove_vertex("1")
        self.assertEqual(self.graph.get_edge_cost("10", "2"), 1)
        self.assertEqual(self.graph.get_edge_cost("2", "3"), 4)
        self.assertEqual(self.graph.parse_outbound_edges("2"), ["3"])
        self.assertEqual(self.graph.parse_outbound_edges("3"), [])
        self.assertEqual(self.graph.parse_outbound_edges("4"), [])
        self.assertEqual(self.graph.parse_outbound_edges("10"), ["2"])
        self.assertEqual(self.graph.parse_inbound_edges("2"), ["10"])
        self.assertEqual(self.graph.parse_inbound_edges("3"), ["2"])
        self.assertEqual(self.graph.parse_inbound_edges("10"), [])
        self.assertEqual(self.graph.parse_inbound_edges("4"), [])
        self.assertEqual(self.graph.parse_vertices(), ["2", "3", "10", "4"])

    def test_eq(self):
        self.assertEqual(self.graph.copy(), self.graph)
        graph2 = self.graph.copy()
        graph2.add_vertex("4")
        self.assertNotEqual(graph2, self.graph)
        graph2.remove_vertex("1")
        self.assertNotEqual(graph2, self.graph)
        graph2.remove_vertex("4")
        self.assertNotEqual(graph2, self.graph)
        graph2.add_vertex("1")
        self.assertNotEqual(graph2, self.graph)
        graph2.add_edge("1", "2", 0)
        self.assertNotEqual(graph2, self.graph)
        graph2.add_edge("1", "3", 3)
        self.assertNotEqual(graph2, self.graph)
        graph2.add_edge("2", "1", 10)
        self.assertEqual(graph2, self.graph)
        self.graph.add_edge("1", "1", 0)
        graph2.add_edge("1", "1", 10)
        self.assertNotEqual(graph2, self.graph)

    def test_read_graph(self):
        with self.assertRaises(Exception):
            read_graph("aaaa")
        with self.assertRaises(Exception):
            read_graph("aaaa.modified")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail1.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail2.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail3.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail1.modified.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail2.modified.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail3.modified.txt")
        with self.assertRaises(Exception):
            read_graph("./test_files/fail4.modified.txt")
        self.assertEqual(read_graph("./test_files/graph1.txt"), Graph(["0", "1", "2", "3", "4"], [
            ("0", "0", 1),
            ("0", "1", 7),
            ("1", "2", 2),
            ("2", "1", -1),
            ("1", "3", 8),
            ("2", "3", 5)
        ]))
        self.assertEqual(read_graph("./test_files/graph2.modified.txt"), Graph(["0", "1", "2", "3", "5"], [
            ("1", "5", 10),
            ("1", "2", 0),
            ("0", "3", 4),
            ("3", "5", 20),
            ("2", "1", 4),
            ("1", "1", 5)
        ]))

    def test_write_graph(self):
        with self.assertRaises(Exception):
            write_graph("aaaa", self.graph)
        with self.assertRaises(Exception):
            write_graph("aaaa.txt", self.graph)
        with self.assertRaises(Exception):
            write_graph("aaaa.modified.txt", "")
        write_graph("./test_files/aaaa.modified.txt", self.graph)
        self.assertEqual(read_graph("./test_files/aaaa.modified.txt"), self.graph)

    def test_random_graph(self):
        with self.assertRaises(Exception):
            random_graph(-10, 2)
        with self.assertRaises(Exception):
            random_graph(10, -2)
        with self.assertRaises(Exception):
            random_graph(6, 40)
        with self.assertRaises(Exception):
            random_graph("6", "2")
        graph = random_graph(6, 20)
        self.assertEqual(len(graph.parse_vertices()), 6)
        cnt_edges = 0
        for x in range(0, 6):
            cnt_edges += len(graph.parse_outbound_edges(str(x)))
        self.assertEqual(cnt_edges, 20)

    def test_floyd_warshall(self):
        self.graph.add_vertex("4")
        self.graph.add_edge("3", "4", 2)
        self.graph.add_edge("2", "4", 4)
        self.assertEqual(floyd_warshall(self.graph, "1", "4"), (4, ["1", "2", "4"]))
        self.assertEqual(floyd_warshall(self.graph, "4", "2"), (inf, []))
