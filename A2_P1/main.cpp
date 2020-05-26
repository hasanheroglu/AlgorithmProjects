//
//  main.cpp
//  project1
//
//  Created by Hasan Eroglu on 10.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "miningsite.h"
#include "node.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    
    if(argc != 4){
        std::cout<<"You need to enter three arguments: <dfs or bfs> <input_file> <output_file>"<<std::endl;
    }
    
    else{
        std::string algorithm;
        std::string input_file;
        std::string output_file;
        clock_t time;
        
        algorithm = argv[1];
        input_file = argv[2];
        output_file = argv[3];
    
        Graph* graph = new Graph(input_file);
        
        if(algorithm == "dfs"){
            time = clock();
            graph->DepthFirstSearch();
            time = clock() - time;
            std::cout<<"Algorithm: DFS"<<std::endl;
            std::cout<<"Number of visited nodes: "<<graph->nodeCount<<std::endl;
            std::cout<<"Maximum number of nodes kept in the memory: "<<graph->maxDepthCount<<std::endl;
            std::cout<<"Running time: "<<(float)time/CLOCKS_PER_SEC<<std::endl;
        }
        
        if(algorithm == "bfs"){
            time = clock();
            graph->BreadthFirstSearch();
            time = clock() - time;
            std::cout<<"Algorithm: BFS"<<std::endl;
            std::cout<<"Number of visited nodes: "<<graph->nodeCount<<std::endl;
            std::cout<<"Maximum number of nodes kept in the memory: "<<graph->maxBreadthCount<<std::endl;
            std::cout<<"Running time: "<<(float)time/CLOCKS_PER_SEC<<std::endl;
        }
        
        graph->WriteFile(output_file);
    }   
    return 0;
}
 
/*
int main(){
    MiningSite* ms = new MiningSite("input_1.txt");
    Node* node = new Node();
    node->miningSite->Clone(ms);
    
    Graph* graph = new Graph(node);
    graph->DepthFirstSearch();
    graph->WriteFile("ebe.txt");
    
    return 0;
}
*/
