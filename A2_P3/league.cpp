//
//  league.cpp
//  project3
/*
 *   Student Name: Hasan H. Eroğlu
 *   Student ID: 150150058
 *   Analysis of Algorithms II - Project 3
 */
//  Created by Hasan Eroglu on 14.05.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//


#include "league.h"

League::League(){
    teamCount=0;
}

int League::SetWinCapacity(int teamNoX, int teamNoY){
    int winCapacity;
    winCapacity = teams[teamNoX].point + teams[teamNoX].remainingMatchCount - teams[teamNoY].point;
    if(winCapacity<0)
        winCapacity = 0;
    
    return winCapacity;
}


void League::ReadFile(std::string fileName){
    int remainingMatchCount;
    std::ifstream leagueInfo(fileName);
    if(leagueInfo.is_open()){
        leagueInfo>>teamCount;
        teams.resize(teamCount);
        for(int i=0; i<teamCount; i++){
            leagueInfo>>teams[i].point;
        }
        std::vector<int> matchRow;
        matchRow.resize(teamCount);
        for(int i=0; i<teamCount; i++){
            remainingMatchCount = 0;
            for(int j=0; j<teamCount; j++){
                leagueInfo>>matchRow[j];
                remainingMatchCount += matchRow[j];
                
            }
            matches.push_back(matchRow);
            teams[i].remainingMatchCount = remainingMatchCount;
        }
    }
    else{
        std::cout<<"Could not find the file."<<std::endl;
    }
}

void League::WriteFile(std::string fileName){
    std::ofstream outputFile(fileName);
    if(outputFile.is_open()){
        for(int i=0; i<eliminationList.size(); i++){
            outputFile<<eliminationList[i]<<" ";
        }
        outputFile<<"\n";
    }
    else{
        std::cout<<"Could not open the file."<<std::endl;
    }
}
