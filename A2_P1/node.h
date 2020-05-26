//
//  node.h
//  project1
//
//  Created by Hasan Eroglu on 11.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//
#include "miningsite.h"

#ifndef node_h
#define node_h
class Node{
private:
    
public:
    MiningSite * miningSite;
    bool visited;
    //std::vector<Node*> neighbours;
    Node();
    Node(const Node &oldNode);
    ~Node();
    //void AddNeighbour(Node* neighbour);
};


#endif /* node_h */
