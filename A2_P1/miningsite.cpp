//
//  miningsite.cpp
//  project1
//
//  Created by Hasan Eroglu on 10.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//
#define MINER -3
#define MINE -2
#define EMPTY -1
#define MINE_FILLED -4
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "miningsite.h"

MiningSite::MiningSite(){
    minerCount = 0;
    minerNeeded = 0;
    minerPositionCount = 0;
}

MiningSite::MiningSite(std::string fileName){
    minerCount = 0;
    minerNeeded = 0;
    minerPositionCount = 0;
    ReadMap(fileName);
    FindMinerPositions();
}

MiningSite::~MiningSite(){
    map.clear();
    miner_row.clear();
    miner_col.clear();
    minerPositions.clear();
}

void MiningSite::Clone(MiningSite *oldMiningSite){
    minerCount = oldMiningSite->minerCount;
    minerNeeded = oldMiningSite->minerNeeded;
    minerPositionCount = oldMiningSite->minerPositionCount;
    row_size = oldMiningSite->row_size;
    col_size = oldMiningSite->col_size;
    CopyMap(oldMiningSite->map);
    CopyMinerPositions(oldMiningSite->minerPositions);
    CopyConstraints(oldMiningSite->miner_row, oldMiningSite->miner_col);
}

void MiningSite::ReadMap(std::string fileName){
    std::ifstream map_file(fileName);
    if(map_file.is_open()){
        map_file>>col_size;
        map_file>>row_size;
        miner_row.resize(row_size);
        miner_col.resize(col_size);
        for(int i=0; i<col_size; i++){
            map_file>>miner_col[i];
            minerNeeded += miner_col[i];
        }
        for(int i=0; i<row_size; i++){
            std::vector<int> mapRow;
            mapRow.resize(col_size);
            for(int j=-1; j<col_size; j++){
                if(j==-1)
                    map_file>>miner_row[i];
                else{
                    char mapChar;
                    map_file>>mapChar;
                    if(mapChar == 's')
                        mapRow[j] = MINE;
                    else
                        mapRow[j] = EMPTY;
                }
            }
            map.push_back(mapRow);
        }
    }
    map_file.close();
}

void MiningSite::WriteMap(std::string fileName){
    std::ofstream output_stream;
    output_stream.open(fileName);
    
    if(output_stream.is_open()){
        output_stream<<row_size<<"\t"<<col_size<<std::endl;
        output_stream<<"\t";
        for(int i=0; i<miner_col.size(); i++)
            output_stream<<miner_col[i]<<"\t";
        output_stream<<std::endl;
        
        for(int i=0; i<row_size; i++){
            for(int j=-1; j<col_size; j++){
                if(j==-1){
                    output_stream<<miner_row[i]<<"\t";
                    continue;
                }
                if(map[i][j] == MINE || map[i][j] == MINE_FILLED)
                    output_stream<<"s\t";
                if(map[i][j] == MINER)
                    output_stream<<"m\t";
                if(map[i][j] >= EMPTY)
                    output_stream<<".\t";
            }
            output_stream<<std::endl;
        }
       
    }
    else{
        return;
    }
    std::cout<<"Solution is written to the file"<<std::endl;
}

void MiningSite::CopyMap(const std::vector<std::vector<int> > oldMap){
    for(int i=0; i<row_size; i++){
        std::vector<int> mapRow;
        mapRow.resize(col_size);
        for(int j=0; j<col_size; j++){
            mapRow[j] = oldMap[i][j];
        }
        map.push_back(mapRow);
    }
}

void MiningSite::CopyMinerPositions(const std::vector<MinerSpace> oldMinerPositions){
    minerPositions.resize(oldMinerPositions.size());
    for(int i=0; i<minerPositionCount; i++){
        minerPositions[i].pos_x = oldMinerPositions[i].pos_x;
        minerPositions[i].pos_y = oldMinerPositions[i].pos_y;
        minerPositions[i].isFilled = oldMinerPositions[i].isFilled;
        minerPositions[i].minePosition = oldMinerPositions[i].minePosition;
    }
}

void MiningSite::CopyConstraints(const std::vector<int> constraint_row, const std::vector<int> constraint_col){
    for(int i=0; i<row_size; i++){
        miner_row.push_back(constraint_row[i]);
    }
    
    for(int i=0; i<col_size; i++){
        miner_col.push_back(constraint_col[i]);
    }
}


void MiningSite::PrintMap(){
    for(int i=0; i<row_size; i++){
        for(int j=0; j<col_size; j++){
            if(map[i][j] == MINE || map[i][j] == MINE_FILLED)
                std::cout<<"s ";
            if(map[i][j] == MINER)
                std::cout<<"m ";
            if(map[i][j] >= EMPTY)
                std::cout<<". ";
        }
        std::cout<<std::endl;
    }
}

void MiningSite::PrintConstraints(){
    std::cout<<"Row Constraints:"<<std::endl;
    for(int i=0; i<row_size;i++)
        std::cout<<miner_row[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Column Constraints:"<<std::endl;
    for(int i=0; i<col_size;i++)
        std::cout<<miner_col[i]<<" ";
    std::cout<<std::endl;
}

void MiningSite::FindMinerPositions(){
    for(int i=0; i<row_size; i++){
        for(int j=0; j<col_size; j++){
            if(ConstraintsHold(i, j)){
                AddMinerPosition(i, j);
            }
        }
    }
}

void MiningSite::AddMinerPosition(int coord_x, int coord_y){
    MinerSpace minerSpace;
    minerSpace.isFilled = false;
    minerSpace.pos_x = coord_x;
    minerSpace.pos_y = coord_y;
    //LEFT
    if(IsIndexInBounds(coord_x,coord_y - 1) && map[coord_x][coord_y-1] == MINE){
        minerSpace.minePosition = LEFT;
        minerPositions.push_back(minerSpace);
        minerPositionCount++;
    }
    if(IsIndexInBounds(coord_x,coord_y + 1) && map[coord_x][coord_y+1] == MINE){
        minerSpace.minePosition = RIGHT;
        minerPositions.push_back(minerSpace);
        minerPositionCount++;
    }
    if(IsIndexInBounds(coord_x - 1,coord_y) && map[coord_x-1][coord_y] == MINE){
        minerSpace.minePosition = UP;
        minerPositions.push_back(minerSpace);
        minerPositionCount++;
    }
    if(IsIndexInBounds(coord_x + 1,coord_y) && map[coord_x+1][coord_y] == MINE){
        minerSpace.minePosition = DOWN;
        minerPositions.push_back(minerSpace);
        minerPositionCount++;
    }
}

int MiningSite::PossibleMinerPositionCount(){
    int count=0;
    for(int i=0; i<minerPositions.size(); i++)
        if(CanPlaceMiner(i))
            count++;
    return count;
}

bool MiningSite::PlaceMiner(int index){
    int coord_x = minerPositions[index].pos_x;
    int coord_y = minerPositions[index].pos_y;
    std::string minePosition;
    if(ConstraintsHold(coord_x, coord_y)){
        switch (minerPositions[index].minePosition) {
            case UP:
                if(IsIndexInBounds(coord_x-1, coord_y) && map[coord_x-1][coord_y] == MINE){
                    map[coord_x-1][coord_y] = MINE_FILLED;
                    minerPositions[index].isFilled = true;
                    map[coord_x][coord_y] = MINER;
                    miner_row[coord_x]--;
                    miner_col[coord_y]--;
                    minePosition = "UP";
                    minerCount++;
                }
                break;
            case DOWN:
                if(IsIndexInBounds(coord_x+1, coord_y) && map[coord_x+1][coord_y] == MINE){
                    map[coord_x+1][coord_y] = MINE_FILLED;
                    minerPositions[index].isFilled = true;
                    map[coord_x][coord_y] = MINER;
                    miner_row[coord_x]--;
                    miner_col[coord_y]--;
                    minePosition = "DOWN";
                    minerCount++;
                }
                break;
            case LEFT:
                if(IsIndexInBounds(coord_x, coord_y-1) && map[coord_x][coord_y-1] == MINE){
                    map[coord_x][coord_y-1] = MINE_FILLED;
                    minerPositions[index].isFilled = true;
                    map[coord_x][coord_y] = MINER;
                    miner_row[coord_x]--;
                    miner_col[coord_y]--;
                    minePosition = "LEFT";
                    minerCount++;
                }
                break;
            case RIGHT:
                if(IsIndexInBounds(coord_x, coord_y+1) && map[coord_x][coord_y+1] == MINE){
                    map[coord_x][coord_y+1] = MINE_FILLED;
                    minerPositions[index].isFilled = true;
                    map[coord_x][coord_y] = MINER;
                    miner_row[coord_x]--;
                    miner_col[coord_y]--;
                    minePosition = "RIGHT";
                    minerCount++;
                }
                break;
            default:
                break;
        }
        
        return true;
    }
    std::cout<<"Miner placement failed"<<std::endl;
    return false;
}

bool MiningSite::ConstraintsHold(int coord_x, int coord_y){
    if(miner_row[coord_x] != 0 && miner_col[coord_y] != 0 && map[coord_x][coord_y] >= EMPTY
       && !AdjacentMinersExist(coord_x, coord_y) && AdjacentMinesExist(coord_x, coord_y))
        return true;
    
    return false;
}

bool MiningSite::CanPlaceMiner(int index){
    return !minerPositions[index].isFilled && ConstraintsHold(minerPositions[index].pos_x, minerPositions[index].pos_y)
    && AdjacentMineExistOn(minerPositions[index].pos_x, minerPositions[index].pos_y, minerPositions[index].minePosition);
}

bool MiningSite::AdjacentMinersExist(int coord_x, int coord_y){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(i==1 && j==1)
                continue;
            if(IsIndexInBounds(coord_x - 1 + i,coord_y - 1 + j)){
                if(map[coord_x - 1 + i][coord_y - 1 + j] == MINER)
                    return true;
            }
        }
    }

    return false;
}

int MiningSite::AdjacentMinesExist(int coord_x, int coord_y){
    if(IsIndexInBounds(coord_x - 1,coord_y) && map[coord_x-1][coord_y]== MINE)
        return UP;
    if(IsIndexInBounds(coord_x + 1,coord_y) && map[coord_x+1][coord_y]== MINE)
        return DOWN;
    if(IsIndexInBounds(coord_x,coord_y - 1) && map[coord_x][coord_y-1]== MINE)
        return LEFT;
    if(IsIndexInBounds(coord_x,coord_y + 1) && map[coord_x][coord_y+1]== MINE)
        return RIGHT;
    
    return 0;
}

bool MiningSite::AdjacentMineExistOn(int coord_x, int coord_y, int position){
    switch (position) {
        case UP:
            if(IsIndexInBounds(coord_x-1, coord_y) && map[coord_x-1][coord_y] == MINE)
                return true;
            break;
        case DOWN:
            if(IsIndexInBounds(coord_x+1, coord_y) && map[coord_x+1][coord_y] == MINE)
                return true;
            break;
        case LEFT:
            if(IsIndexInBounds(coord_x, coord_y-1) && map[coord_x][coord_y-1] == MINE)
                return true;
            break;
        case RIGHT:
            if(IsIndexInBounds(coord_x, coord_y+1) && map[coord_x][coord_y+1] == MINE)
                return true;
            break;
        default:
            return false;
            break;
    }
    
    return false;
}


bool MiningSite::IsIndexInBounds(int coord_x, int coord_y){
    if((coord_x >= 0 && coord_x < row_size) && (coord_y >= 0 && coord_y < col_size))
        return true;
    
    return false;
}

void MiningSite::CalculateConstraints(){
    for(int i=0; i<row_size;i++){
        for(int j=0; j<col_size;j++){
            if(map[i][j] == MINER)
                miner_row[i]++;
        }
    }
    
    for(int i=0; i<row_size;i++){
        for(int j=0; j<col_size;j++){
            if(map[j][i] == MINER)
                miner_col[i]++;
        }
    }
}
