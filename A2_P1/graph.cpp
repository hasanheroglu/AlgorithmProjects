//
//  graph.cpp
//  project1
//
//  Created by Hasan Eroglu on 11.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//
#include "graph.h"
#include <iostream>
#include <cstring>

Graph::Graph(std::string fileName){
    nodeCount = 0;
    breadthCount = 0;
    maxBreadthCount = 0;
    depthCount = 0;
    maxDepthCount = 0;
    branchCount = -1;
    MiningSite* ms = new MiningSite(fileName);
    Node* node = new Node();
    node->miningSite->Clone(ms);
    PushToStack(0, 0);
    AddNode(node);
}

Graph::Graph(Node* node){
    nodeCount = 0;
    breadthCount = 0;
    maxBreadthCount = 0;
    depthCount = 0;
    maxDepthCount = 0;
    branchCount = -1;
    PushToStack(0, 0);
    AddNode(node);
}

bool Graph::AddNode(Node* newNode){
    
    if(DuplicateExists(newNode->miningSite->minerPositions)){
        std::cout<<"Can't add the node because, it already exists."<<std::endl;
        return false;
    }
    else{
        nodes.push_back(newNode);
        nodeCount++;
        return true;
    }
}

void Graph::BreadthAddNode(int level, Node* newNode){
    
    if(BreadthDuplicateExists(level, newNode->miningSite->minerPositions)){
        delete newNode;
    }
    else{
        nodes.push_back(newNode);
        levelIndex[level+1]++;
        breadthCount++;
        nodeCount++;
    }
}

void Graph::BreadthFirstSearch(){
    int traverser=0;
    int level = -1;
    int newLevel = 0;
    levelIndex.push_back(0);
    while(true){
    
        Node* traverserNode = nodes[traverser];
        MiningSite* traverserMS = traverserNode->miningSite;
        newLevel = traverserMS->minerCount;
        
        if(newLevel != level){
            level = newLevel;
            levelIndex.push_back(0);
            levelIndex[level+1] += levelIndex[level];
            if(breadthCount > maxBreadthCount)
                maxBreadthCount =  breadthCount;
            breadthCount = 0;
        }
        
        if(traverserMS->PossibleMinerPositionCount() != 0){
            for(int i=0; i<traverserMS->minerPositions.size(); i++){
                if(traverserMS->CanPlaceMiner(i)){
                    Node* newNode = new Node();
                    newNode->miningSite->Clone(traverserMS);
                    newNode->miningSite->PlaceMiner(i);
                    BreadthAddNode(level, newNode);
                }
            }
        }
        
        if(traverserMS->minerCount == traverserMS->minerNeeded){
            break;
        }
        
        delete nodes[traverser];
        traverser++;
    }
}

void Graph::DepthFirstSearch(){
    int possibleMinerIndex=0;

    Node* traverserNode = nodes[branchCount];
    MiningSite* traverserMS = traverserNode->miningSite;

    while(true){
        if(depthCount > maxDepthCount)
            maxDepthCount = depthCount;
        
        if(traverserMS->minerCount == traverserMS->minerNeeded){
            break;
        }
        
        if(traverserMS->PossibleMinerPositionCount() != 0 && possibleMinerIndex < traverserMS->minerPositions.size()){
            if(traverserMS->CanPlaceMiner(possibleMinerIndex)){
                Node* newNode = new Node();
                newNode->miningSite->Clone(traverserMS);
                newNode->miningSite->PlaceMiner(possibleMinerIndex);
                
                if(AddNode(newNode)){
                    PushToStack(nodeCount-1, possibleMinerIndex);//no need for nodecount argument
                    traverserMS = nodes[branchCount]->miningSite;
                    possibleMinerIndex = 0;
                    newNode->miningSite->PrintMap();
                }
                else{
                    delete newNode;
                    traverserMS = nodes[branchStack.top().index]->miningSite;
                    possibleMinerIndex = branchStack.top().possibleMinerIndex;
                    possibleMinerIndex++;
                    branchStack.top().possibleMinerIndex = possibleMinerIndex;
                }
            }
            else{
                possibleMinerIndex++;
                branchStack.top().possibleMinerIndex = possibleMinerIndex;
            }
        }
        else{
            depthCount--;
            branchStack.pop();
            traverserMS = nodes[branchStack.top().index]->miningSite;
            possibleMinerIndex = branchStack.top().possibleMinerIndex;
            possibleMinerIndex++;
            branchStack.top().possibleMinerIndex = possibleMinerIndex;
        }
    }
}

bool Graph::DuplicateExists(std::vector<MinerSpace> minerPositions){
    
    int counter = 0;
    for(int i=0; i<nodeCount; i++){
        for(int j=0; j<minerPositions.size(); j++){
            if(minerPositions[j].isFilled != nodes[i]->miningSite->minerPositions[j].isFilled){
                counter = 0;
                break;
            }
            else
                counter++;
        }
        
        if(counter==minerPositions.size()){
            return true;
        }
    }
    
    
    return false;
}

bool Graph::BreadthDuplicateExists(int level, std::vector<MinerSpace> minerPositions){
    
    int counter = 0;
    for(int i=levelIndex[level]+1; i<nodeCount; i++){
        for(int j=0; j<minerPositions.size(); j++){
            if(minerPositions[j].isFilled != nodes[i]->miningSite->minerPositions[j].isFilled){
                counter = 0;
                break;
            }
            else
                counter++;
        }
        
        if(counter==minerPositions.size()){
            return true;
        }
    }
    
    
    return false;
}

void Graph::PushToStack(int index, int possibleMinerIndex){
    BranchData branchData;
    branchData.index = index;
    branchData.possibleMinerIndex = possibleMinerIndex;
    branchStack.push(branchData);
    branchCount++;
    depthCount++;
}

void Graph::WriteFile(std::string fileName){
    nodes[nodeCount-1]->miningSite->CalculateConstraints();
    nodes[nodeCount-1]->miningSite->WriteMap(fileName);
}
