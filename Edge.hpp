//lihicohen1123@gmail.com
namespace graph {

    class Edge {

        public:
        int dest;
        int weight;

        Edge() : dest(-1), weight(0) {}

        Edge(int d, int w = 1):dest(d), weight(w){}
           
    };
}
