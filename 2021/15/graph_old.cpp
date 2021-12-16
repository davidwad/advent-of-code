class Node {
    public:
        int ipos;
        int jpos;
        int d = INT32_MAX;
        Node* pred;

        Node () {

        }

        Node(int i, int j) {
            ipos = i;
            jpos = j;
        }
        bool operator==(const Node& node) {
            return node.ipos == ipos && node.jpos == jpos;
        }
};

class Edge {
    public:
        Node start;
        Node end;
        int weight;

        Edge(Node s, Node e, int w) {
            start = s;
            end = e;
            weight = w;
        }
};

class Graph {
    public:
        list<Edge> adj_list;

        void add_edge(Edge e) {
            adj_list.push_back(e);
        }

        list<Edge> get_edges(Node node) {
            list<Edge> edges;
            for (Edge e : adj_list) {
                //if (e.start.equals(node)) {
                if (e.start == node) {
                    edges.push_back(e);
                }
            }
            return edges;
        }

        // list<Node> get_neighbours(Node node) {
        //     list
        // }
};