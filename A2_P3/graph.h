//
//  graph.h
//  project3
/*
 *   Student Name: Hasan H. Eroğlu
 *   Student ID: 150150058
 *   Analysis of Algorithms II - Project 3
 */
//  Created by Hasan Eroglu on 14.05.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include "league.h"

#ifndef graph_h
#define graph_h

class Edge{
public:
    int capacity;
    int nodeIndex;
    Edge(int capacity, int nodeIndex){
        this->capacity = capacity;
        this->nodeIndex = nodeIndex;
    }
};

class Node{
public:
    bool visited;
    int teamNoX;
    int teamNoY;
    std::vector<Edge> adjacencyList;
    Node(int teamNoX=-1, int teamNoY=-1){
        this->teamNoX = teamNoX;
        this->teamNoY = teamNoY;
        visited = false;
    }
};

class Graph{
    std::vector<Node*> graph;
    std::stack<int> nodeStack;
    int teamStartIndex;
    int nodeCount;
    bool pathFound;
    League *league;
public:
    Graph(std::string);
    void AddNode(int, int);
    void AddEdge(Node*, int, int);
    void CreateGraph(int);
    void ResetGraph();

    void AddMatches(int);
    void AddTeams(int);
    void ConnectMatchesAndTeams();
    
    void DFS(int, int);
    void DecreaseAugmentingPath();
    bool AllMatchesPlayed();
    
    int CheckElimination();
    void FindResults();
    void PrintResults();
    
    void ResetVisited();
    bool CheckAllVisited();
    
    void InitiateStack();
    void EmptyStack();
    
    void ReadFile(std::string);
    void WriteFile(std::string);
};


#endif /* graph_h */
