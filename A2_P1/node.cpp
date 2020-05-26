//
//  node.cpp
//  project1
//
//  Created by Hasan Eroglu on 11.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <stdio.h>
#include "node.h"

Node::Node(){
    visited = false;
    miningSite = new MiningSite();
}

Node::Node(const Node &oldNode){
    visited = false;
    miningSite = new MiningSite();
}

Node::~Node(){
    delete miningSite;
}
/*
void Node::AddNeighbour(Node neighbour){
    neighbours.push_back(neighbour);
}
*/
