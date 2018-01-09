#include "Graph.h"
#include "ClusterClass.h"
#include "HashMap.h"

using namespace std;

void createGraph(Graph &net, ifstream &in);
void clustering(Graph &net, ofstream& out, double density, double cp);


int main(int argc, char *argv[]) {

	Graph net; 

	//argv[1]: path to input file
	//argv[2]: path to output file
	//argv[3]: threshold density (0 < d <= 1)
	//argv[4]: threshold cluster property range (0 < cp <= 1)
	ifstream in(argv[1]); ofstream out(argv[2]);
	createGraph(net, in);
	clustering(net, out, strtod(argv[3], NULL), strtod(argv[4], NULL));

	return 0;
}

void createGraph(Graph &net, ifstream &in) {
	HashMap *Map;
	string a, b; double weight;
	Map = new HashMap(10);

	vNode *src = NULL, *dest = NULL;

	while (!in.eof()) {
		if (Map->currentSize >= Map->tableSize)
			tableDoubling(Map);

		in >> a;
		in >> b;
		in >> weight;

		if (!(Map->get(HashKey(a), dest, a))) {
			dest = net.addtoList(a);
			Map->put(HashKey(a), dest);
		}


		if (!(Map->get(HashKey(b), src, b))) {
			src = net.addtoList(b);
			Map->put(HashKey(b), src);
		}

		net.addEdge(dest, src, weight);
	}
	net.MergeSort(net.headV);
	in.close();
	delete Map;
}

void clustering(Graph &net, ofstream& out, double density, double cp) {
	Cluster* c;
	int p = 1;
	net.generateHighest();
	if (net.highest == 0)
		return;
	c = new Cluster(density, cp, p);
	while (net.highest != NULL) {
		c->cluster(net.highest);
		c->Print(out);
		delete c;
		p++;
		c = new Cluster(density, cp, p);
		net.generateHighest();
	}
}