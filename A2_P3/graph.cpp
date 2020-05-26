//
//  graph.cpp
//  project3
/*
 *   Student Name: Hasan H. Eroğlu
 *   Student ID: 150150058
 *   Analysis of Algorithms II - Project 3
 */
//  Created by Hasan Eroglu on 14.05.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include "graph.h"

Graph::Graph(std::string fileName){
    nodeCount=0;
    pathFound=false;
    InitiateStack();
    league = new League();
    ReadFile(fileName);
}

void Graph::AddNode(int teamNoX=-1, int teamNoY=-1){
    Node * node = new Node(teamNoX, teamNoY);
    graph.push_back(node);
    nodeCount++;
}

void Graph::AddEdge(Node *node, int weight, int targetNodeIndex){
    Edge edge(weight, targetNodeIndex);
    node->adjacencyList.push_back(edge);
}

void Graph::CreateGraph(int teamNo){
    AddNode(); //add source
    AddNode(); //add sink
    AddMatches(teamNo);
    AddTeams(teamNo);
    ConnectMatchesAndTeams();
    return;
}

void Graph::ResetGraph(){
    graph.clear();
    nodeCount = 0;
    EmptyStack();
}

void Graph::AddMatches(int teamNo){
    for(int i=0; i<league->teamCount; i++){
        if(i == teamNo)
            continue;
        for(int j=i; j<league->teamCount; j++){
            if(j == teamNo)
                continue;
            if(league->matches[i][j] != 0){
                AddNode(i,j);
                AddEdge(graph[0], league->matches[i][j], nodeCount-1);
            }
            
        }
    }
}

void Graph::AddTeams(int teamNo){
    teamStartIndex = nodeCount;
    for(int i=0; i<league->teamCount; i++){
        if(i==teamNo)
            continue;
        int winCapacity = league->SetWinCapacity(teamNo, i);
        AddNode(i);
        AddEdge(graph[nodeCount-1], winCapacity, 1);
    }
}

void Graph::ConnectMatchesAndTeams(){
    for(int i=2; i<teamStartIndex; i++){
        for(int j=teamStartIndex; j<nodeCount; j++){
            if(graph[i]->teamNoX == graph[j]->teamNoX || graph[i]->teamNoY == graph[j]->teamNoX){
                AddEdge(graph[i], -1, j);
            }
        }
    }
}

void Graph::DFS(int startIndex, int targetIndex){
    int nextIndex;
    graph[startIndex]->visited = true;
    if(pathFound)
        return;
    if(startIndex==targetIndex){
        pathFound = true;
        return;
    }
    else if(CheckAllVisited())
        return;
    else{
        for(int i=0; i<graph[startIndex]->adjacencyList.size(); i++){
            nextIndex = graph[startIndex]->adjacencyList[i].nodeIndex;
            if(graph[nextIndex]->visited == false && graph[startIndex]->adjacencyList[i].capacity != 0){
                nodeStack.push(nextIndex);
                DFS(nextIndex, targetIndex);
                if(pathFound)
                    return;
                nodeStack.pop();
            }
        }
    }
    
    return;
}

void Graph::DecreaseAugmentingPath(){
    int firstNodeIndex, firstTargetIndex, secondNodeIndex;
    nodeStack.pop();
    secondNodeIndex = nodeStack.top();
    nodeStack.pop();
    firstTargetIndex = nodeStack.top();
    nodeStack.pop();
    firstNodeIndex = nodeStack.top();
    for(int i=0; i<graph[firstNodeIndex]->adjacencyList.size(); i++){
        if(graph[firstNodeIndex]->adjacencyList[i].nodeIndex == firstTargetIndex)
            firstTargetIndex = i;
    }
    
    int leastFlow;
    leastFlow = std::min(graph[firstNodeIndex]->adjacencyList[firstTargetIndex].capacity, graph[secondNodeIndex]->adjacencyList[0].capacity);
    graph[firstNodeIndex]->adjacencyList[firstTargetIndex].capacity -= leastFlow;
    graph[secondNodeIndex]->adjacencyList[0].capacity -= leastFlow;
}

bool Graph::AllMatchesPlayed(){
    for(int i=0; i<graph[0]->adjacencyList.size(); i++){
        if(graph[0]->adjacencyList[i].capacity!=0)
            return false;
    }
    
    return true;
}

int Graph::CheckElimination(){
    while(1){
        DFS(0,1);
        if(pathFound){
            DecreaseAugmentingPath();
            ResetVisited();
            pathFound = false;
        }
        else{
            if(AllMatchesPlayed())
                return 1;
            else
                return 0;
        }
    }
}

void Graph::FindResults(){
    for(int i=0; i<league->teamCount; i++){
        CreateGraph(i);
        league->eliminationList.push_back(CheckElimination());
        ResetGraph();
    }
}

void Graph::PrintResults(){
    for(int i=0; i<league->teamCount; i++){
        std::cout<<league->eliminationList[i]<<" ";
    }
    std::cout<<std::endl;
}

bool Graph::CheckAllVisited(){
    for(int i=0; i<nodeCount; i++){
        if(!graph[i]->visited){
            return false;
        }
    }
    return true;
}

void Graph::ResetVisited(){
    for(int i=0; i<nodeCount; i++){
        graph[i]->visited = false;
    }
}

void Graph::InitiateStack(){
    nodeStack.push(-1);
    nodeStack.push(0);
}

void Graph::EmptyStack(){
    while(nodeStack.top()!=0)
        nodeStack.pop();
}

void Graph::ReadFile(std::string fileName){
    league->ReadFile(fileName);
}
void Graph::WriteFile(std::string fileName){
    league->WriteFile(fileName);
}
