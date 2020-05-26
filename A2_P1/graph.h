//
//  graph.h
//  project1
//
//  Created by Hasan Eroglu on 11.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//
#include "node.h"
#include "miningsite.h"
#include <vector>
#include <stack>

#ifndef graph_h
#define graph_h
struct BranchData{
    int index;
    int possibleMinerIndex;
};

class Graph{
private:
    std::vector<Node*> nodes;
    std::vector<int> levelIndex;
    std::vector<Node*> visitedNodes;
    std::stack<BranchData> branchStack;
public:
    int nodeCount, branchCount, breadthCount, maxBreadthCount, depthCount, maxDepthCount;
    Graph(std::string fileName);
    Graph(Node* node);
    bool AddNode(Node* newNode);
    bool DuplicateExists(std::vector<MinerSpace> minerPositions);
    void BreadthAddNode(int level, Node* newNode);
    bool BreadthDuplicateExists(int level, std::vector<MinerSpace> minerPositions);
    void BreadthFirstSearch();
    void DepthFirstSearch();
    void PushToStack(int index, int possibleMinerIndex);
    void WriteFile(std::string fileName);
};

#endif /* graph_h */
