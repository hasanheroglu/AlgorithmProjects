//
//  main.cpp
/*
 *   Student Name: Hasan H. Eroğlu
 *   Student ID: 150150058
 *   Analysis of Algorithms II - Project 3
 */
//  Created by Hasan Eroglu on 2.05.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <iostream>
#include "graph.h"

int main(int argc, const char * argv[]){
    
    if(argc == 1){
        std::cout<<"Input file name is missing."<<std::endl;
        return 0;
    }
    else if(argc > 3){
        std::cout<<"Too many arguments."<<std::endl;
        return 0;
    }
    
    Graph * g = new Graph(argv[1]);
    g->FindResults();
    if(argc == 3)
        g->WriteFile(argv[2]);
    else
        g->PrintResults();
    
    return 0;
}
