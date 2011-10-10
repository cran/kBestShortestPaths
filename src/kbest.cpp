#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cfloat>

#include <Rinternals.h>
#include <R.h>
#include <R_ext/Memory.h>

#include "graehl/graph.h"
#include "numberGenerator.h"
#include "exceptions.h"
#include "dataRead.h"


using namespace std;
using namespace tfl;

int nonZeroCount(string input)
{
	int count = 0;
	for (int i = 0; input.c_str()[i]; i++)
		if (input.c_str()[i] != '0')
			count++;
	return count;
}

// adds to graph like dfs.
void addToGraph(Graph &g, map<string, int> &graphIdMap, map<string, double> &pvals, NumberGenerator &n, int &id, vector<bool> &visited)
{
//	cerr << "called." << endl;
	if (graphIdMap.find(n.text()) == graphIdMap.end())
	{
		graphIdMap[n.text()] = id;
		//Rprintf("befor loop, num: %s\tid: %d\n", n.text(), id);
		visited.push_back(false);
		id++;
	}

	for (int i = 0; i < n.nonZeroCount(); i++)
	{
		GraphArc a;
		NumberGenerator neighbor = n.neighbor(i);

		if (graphIdMap.find(neighbor.text()) == graphIdMap.end())
		{
			graphIdMap[neighbor.text()] = id;
			//Rprintf("loop, num: %s\tid: %d\n", neighbor.text(), id);
			visited.push_back(false);
			id++;
		}

		a.dest = graphIdMap[n.text()];
		a.source = graphIdMap[neighbor.text()];
		a.weight = -pvals[n.text()];
		a.data = NULL;
		g.states[a.source].arcs.push(a);
//		printf("(%s %s %lg)\n", neighbor.text(), n.text(), a.weight);
//		cerr << "source: " << n.text() << " dest: " << neighbor.text();
//		cerr << " one item added: " << a << endl;
//		cerr << g;

		if (!visited[graphIdMap[neighbor.text()]])
		{
//			fprintf(stderr, "----calling in this state: %s to %s\n", n.text(), neighbor.text());
			addToGraph(g, graphIdMap, pvals, neighbor, id, visited);
		}
	}
	visited[graphIdMap[n.text()]] = true;
}

// first input is to be filled and should be empty as input
void createGraph(Graph &g, map<string, int> &graphIdMap, vector<string> edge_names, double *edge_weights, int edge_count, int directed)
{
	g.nStates = graphIdMap.size();
    g.states = new GraphState[g.nStates];
	
	for (int i = 0; i < edge_count; i++)
	{
		GraphArc a;

		char *tmp;
		char *save_ptr;
		char edge_[256];
		strncpy(edge_, edge_names[i].c_str(), 256);
		tmp = strtok_r(edge_, "~", &save_ptr);
		string source = tmp;
		tmp = strtok_r(NULL, "~", &save_ptr);
		string dest = tmp;
		a.source = graphIdMap[source];
		a.dest = graphIdMap[dest];
		a.weight = edge_weights[i];
		a.data = NULL;
		g.states[a.source].arcs.push(a);
		if (!directed)
		{
			a.source = graphIdMap[dest];
			a.dest = graphIdMap[source];
			a.weight = edge_weights[i];
			a.data = NULL;
			g.states[a.dest].arcs.push(a);
		}
//		printf("(%s %s %lg)\n", neighbor.text(), n.text(), a.weight);
//		cerr << "source: " << n.text() << " dest: " << neighbor.text();
//		cerr << " one item added: " << a << endl;
//		cerr << g;
	}
}

string getKey(map<string, int> m, int v)
{
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++)
		if (it->second == v)
			return it->first;
	return "NULL";
}

void addEdge(map<string, map<string, double> > &edge_list, string source, string dest, double value)
{
	if (edge_list.find(source) == edge_list.end())
		edge_list[source] = map<string, double>();
	if (edge_list[source].find(dest) == edge_list[source].end())
		edge_list[source][dest] = value;
}

void addNodeSize(map<string, double> &node_size, string node, double size)
{
	if (node_size.find(node) == node_size.end())
		node_size[node] = size;
	else
		node_size[node] += size;
}

string getHex(unsigned char value)
{
	char c1 = value / 16;
	char c2 = value % 16;
	if (c1 < 10)
		c1 = '0' + c1;
	else
		c1 = 'A' + c1 - 10;

	if (c2 < 10)
		c2 = '0' + c2;
	else
		c2 = 'A' + c2 - 10;
	string res;
	res.append(1, c1);
	res.append(1, c2);
	return res;
}

void setMaxMin(double value, double &min, double &max)
{
	if (value < min)
		min = value;
	if (value > max)
		max = value;
}

static int p_count = 0;
void my_protect(SEXP p)
{
	PROTECT(p);
	p_count++;
}

void unprotect_all()
{
	UNPROTECT(p_count);
	p_count = 0;
}

extern "C"
{
	void kbest(vector<string> &node_names, 
			int node_count,
			vector<string> edge_names,
			double *edge_weights,
			int edge_count,
			int directed_graph,
			string source_node, 
			string dest_node,
			int s_best_count,
			//outputs
			vector<vector<string> > &best_paths, 
			vector<vector<double> > &path_weights)
	{
		int node_c = node_count;
		int edge_c = edge_count;
		int best_count = s_best_count;
		int directed = directed_graph;

		map<string, int> graphIdMap;

		for (int i = 0; i < node_c; i++)
		{
			graphIdMap[node_names[i]] = i;
		}
		
		Graph graph;
		createGraph(graph, graphIdMap, edge_names, edge_weights, edge_c, directed);
		//Rprintf("%s", graph2str(graph).c_str());
		//map<string, double> node_size;
		//map<string, map<string, double> > edge_list;
		//node_size.clear();
		//edge_list.clear();
		//double min_node_size = DBL_MAX, max_node_size = DBL_MIN;
		//double min_edge_size = DBL_MAX, max_edge_size = DBL_MIN;
		//	cout << source.text() << " " << graphIdMap[source.text()] << "\n" << dest.text() << " " << graphIdMap[dest.text()] << "\n";
		//	return;

		//printf("source:%s\ndest:%s\n", source.text(), dest.text());
		List<List<GraphArc *> > *paths = bestPaths(graph, graphIdMap[source_node], graphIdMap[dest_node], best_count);
		for ( ListIter<List<GraphArc *> > pathIter(*paths) ; pathIter ; ++pathIter ) 
		{
			//double pathWeight = 0;
			GraphArc *a;
			//int trim = 0;
			best_paths.push_back(vector<string>());
			path_weights.push_back(vector<double>());
			for ( ListIter<GraphArc *> arcIter(pathIter.data()) ; arcIter ; ++arcIter ) 
			{
				a = arcIter.data();
				//if (pvals[getKey(graphIdMap, a->dest)] < pvals[getKey(graphIdMap, a->source)])
				//	trim = 1;
				
				//printf("a->dest:%d\t", a->dest);
				//printf("getkey:%s\t", getKey(graphIdMap, a->dest).c_str());
				//printf("best_paths[%d] <- %s\n", node_pos, getKey(graphIdMap, a->dest).c_str());

				char tmp_edge[256];
				sprintf(tmp_edge, "%s~%s", getKey(graphIdMap, a->source).c_str(), getKey(graphIdMap, a->dest).c_str());
				best_paths.back().push_back(tmp_edge);
				path_weights.back().push_back(a->weight);
				//printf("(%s %lg)", getKey(graphIdMap, a->dest).c_str(), pvals[getKey(graphIdMap, a->dest)]);
			}
			//printf("\n");
		}

		delete paths;
		delete[] graph.states;
	}
	
	SEXP bozghale(SEXP e_node_names,
			SEXP e_node_count,
			SEXP e_edge_names,
			SEXP e_edge_weights,
			SEXP e_edge_count,
			SEXP e_directed_graph,
			SEXP e_source_node, 
			SEXP e_dest_node,
			SEXP e_s_best_count)
	{

		int node_count = asInteger(e_node_count);
		double *edge_weights = REAL(e_edge_weights);
		int edge_count = asInteger(e_edge_count);
		int directed_graph = asInteger(e_directed_graph);
		int s_best_count = asInteger(e_s_best_count);
		
		vector<string> node_names;
		for (int i = 0; i < node_count; i++)
		{
			node_names.push_back(CHAR(STRING_ELT(e_node_names, i)));
		}

		vector<string> edge_names;
		for (int i = 0; i < edge_count; i++)
		{
			edge_names.push_back(CHAR(STRING_ELT(e_edge_names, i)));
		}

		string source_node = CHAR(asChar(e_source_node));
		string dest_node = CHAR(asChar(e_dest_node));

		vector<vector<string> > best_paths;
		vector<vector<double> > path_weights;

		kbest(node_names, 
				node_count,
				edge_names,
				edge_weights,
				edge_count,
				directed_graph,
				source_node, 
				dest_node,
				s_best_count,
				//outputs
				best_paths, 
				path_weights);
		
		SEXP res;
		my_protect(res = allocVector(VECSXP, 2));
		SEXP e_best_paths;
		my_protect(e_best_paths = allocVector(VECSXP, best_paths.size()));
		for (size_t i = 0; i < best_paths.size(); i++)
		{
			vector<string> &path = best_paths[i];
			SEXP e_path;
			my_protect(e_path = allocVector(STRSXP, path.size()));
			for (size_t j = 0; j < path.size(); j++)
			{
				SET_STRING_ELT(e_path, j, mkChar(path[j].c_str()));
			}
			SET_VECTOR_ELT(e_best_paths, i, e_path);
		}

		SEXP e_path_weights;
		my_protect(e_path_weights = allocVector(VECSXP, path_weights.size()));
		for (size_t i = 0; i < path_weights.size(); i++)
		{
			vector<double> &path = path_weights[i];
			SEXP e_path;
			my_protect(e_path = allocVector(REALSXP, path.size()));
			double *path_p = REAL(e_path);
			for (size_t j = 0; j < path.size(); j++)
			{
				path_p[j] = path[j];
			}
			SET_VECTOR_ELT(e_path_weights, i, e_path);
		}

		SET_VECTOR_ELT(res, 0, e_best_paths);
		SET_VECTOR_ELT(res, 1, e_path_weights);

		SEXP member_names;
		my_protect(member_names = allocVector(STRSXP, 2));
		SET_STRING_ELT(member_names, 0, mkChar("best.paths"));
		SET_STRING_ELT(member_names, 1, mkChar("path.weights"));
		setAttrib(res, R_NamesSymbol, member_names);

		unprotect_all();
		return res;
	}
}

char **allocate(int x, int y)
{
	char **matrix = (char **)calloc(x, sizeof(char*));
	for(int i = 0; i < x; i++) 
	{
		matrix[i] = (char *)calloc(y, sizeof(char));
	}
	return matrix;
}

void destroy(char **v, int x)
{
	for (int i = 0; i < x; i++)
		free(v[i]);
	free(v);
}

int main(int argc, char **argv)
{
	try
	{
		if (argc != 5)
		{
			fprintf(stderr, "usage: %s signs_file pvalue_file back_trace_start_string path_count\n", argv[0]);
			exit(-1);
		}
/*		char *pval_file_name = argv[2];
		char *signs_file_name = argv[1];
		char *back_trace_start = argv[3];
		int path_count = atoi(argv[4]);

		int trim_paths = 0;

		int data_count = 100000;
		int protein_count = strlen(back_trace_start);
		double *pvals = new double[data_count];
		int *s_values = new int[data_count * protein_count];
		char **signs = allocate(data_count, 255);
		int signs_row_num;
		char **proteins = allocate(10, 10);

		readPvals(signs_file_name, 
				pval_file_name, 
				pvals, 
				s_values, 
				signs, 
				signs_row_num,
				proteins);
	
		char **best_paths = allocate(path_count * protein_count, 255);;
		double node_pvalue[path_count * protein_count];
		char **gnodes = allocate(path_count * protein_count * 3, 255);
		char **gedges = allocate(path_count * protein_count * 5, 255);
		int node_count;
		int edge_count;
		c_analyze(signs, 
				s_values, 
				&signs_row_num, 
				&protein_count, 
				pvals, 
				proteins,
				&back_trace_start, 
				&path_count, 
				&trim_paths,
				//outputs
				best_paths, 
				node_pvalue,
				gnodes, 
				gedges,
				&node_count,
				&edge_count);
		//dumpGraphvizFile(graph, pvals, signs, proteins, graphIdMap, source, dest, path_count, "salam");
		//cout << graph;
		destroy(signs, data_count);
		destroy(proteins, 10);
		destroy(best_paths, path_count * protein_count);
		destroy(gnodes, path_count * protein_count * 3);
		destroy(gedges, path_count * protein_count * 5);
		delete[] pvals;
		delete[] s_values;*/
	}
	catch (Exception e)
	{
		fprintf(stderr, "%s\n", e.getMsg().c_str());
	}
	
	return 0;
}

