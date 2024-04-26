#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include "qlist.h"
#include "qlist.h"
#include "qqueue.h"
#include "qstack.h"
#include <stack>

class Digraph
{
private:
	int V;  
	int E;  
	QList<QList<int>> adj;

public:
	Digraph(int V) : V(V), E(0)	{
		for (int i = 0; i < V; i++)		{
			adj << QList<int>();
		}
		for (int v = 0; v < V; ++v) {
			adj[v] = QList<int>();
		}
	}

	int getV() const { return V; }  
	int getE() const { return E; }  

	void addEdge(int v, int w) {
		adj[v].push_back(w); 
		E++;
	}

	QList<int> getAdj(int v) const {
		return adj[v];
	}

	Digraph reverse() const {
		Digraph R(V);
		for (int v = 0; v < V; v++) {
			for (int w : adj[v]) {
				R.addEdge(w, v);  
			}
		}
		return R;
	}
};

class DirectedCycle {
private:
	QList<bool> marked;
	QList<int> edgeTo;
	std::stack<int> cycle;  
	QList<std::stack<int>> cycles;  
	QList<bool> onStack; 

public:
	DirectedCycle(const Digraph& G)	{
		for (int v = 0; v < G.getV(); v++)		{
			onStack << false;
			edgeTo << -1;
			marked << false;
		}
		for (int v = 0; v < G.getV(); v++)		{
			if (!marked[v])
				dfs(G, v);
		}
	}

	bool hasCycle() const {
		return !cycle.empty();
	}

	std::stack<int> getCycle() const {
		return cycle;
	}
	QList<int> getMincycle()	{
		std::stack<int> tempcycle = cycle;

		QList<int> cc;
		while (!tempcycle.empty())		{
			int value = tempcycle.top(); 
			tempcycle.pop();
			cc << value;
		}
		return cc;
	}
	QList<QList<int>> getcycles()	{
		QList<QList<int>> ccs;
		QList<std::stack<int>> tempcycles = cycles;
		for each (std::stack<int> tempcycle in tempcycles)	{
			QList<int> cc;
			while (!tempcycle.empty())	{
				int value = tempcycle.top(); 
				tempcycle.pop();
				cc << value;
			}
			ccs << cc;
		}
		return ccs;
	}

private:
	void dfs(const Digraph& G, int v) {
		onStack[v] = true;  
		marked[v] = true;

		for (int w : G.getAdj(v)) {
			if (!marked[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
			else if (onStack[w]) {
				std::stack<int> tempCycle;
				for (int x = v; x != w; x = edgeTo[x]) {
					tempCycle.push(x);
				}
				tempCycle.push(w);
				tempCycle.push(v);

				cycles << tempCycle;
				if (cycle.empty() || tempCycle.size() < cycle.size()) {
					cycle = tempCycle;
				}
			}
		}
		onStack[v] = false;
	}
};
