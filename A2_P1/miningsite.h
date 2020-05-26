//
//  miningsite.h
//  project1
//
//  Created by Hasan Eroglu on 10.03.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//
/*
 =========================
 =========================
 */
#include <vector>

#ifndef miningsite_h
#define miningsite_h
struct MinerSpace{
    int pos_x;
    int pos_y;
    bool isFilled;
    int minePosition;
};

class MiningSite{
private:
    void FindMinerPositions();
    void AddMinerPosition(int coord_x, int coord_y);
    bool AdjacentMinersExist(int coord_x, int coord_y);
    int AdjacentMinesExist(int coord_x, int coord_y);
    bool AdjacentMineExistOn(int coord_x, int coord_y, int position);
    bool IsIndexInBounds(int coord_x, int coord_y);
    bool IsMine(int coord_x, int coord_y);
    bool IsMiner(int coord_x, int coord_y);
    void PlaceOn(int coord_x, int coord_y);
public:
    std::vector<std::vector<int> > map;
    std::vector<int> miner_row, miner_col;
    std::vector<MinerSpace> minerPositions;
    int minerCount, minerNeeded, minerPositionCount;
    int row_size, col_size;
    MiningSite();
    MiningSite(std::string fileName);
    ~MiningSite();
    void Clone(MiningSite * oldMiningSite);
    void ReadMap(std::string fileName);
    void WriteMap(std::string fileName);
    void CopyMap(const std::vector<std::vector<int> >  oldMap);
    void CopyMinerPositions(const std::vector<MinerSpace> oldMinerPositions);
    void CopyConstraints(const std::vector<int> constraint_row, const std::vector<int> constraint_col);
    int PossibleMinerPositionCount();
    void PrintMap();
    bool PlaceMiner(int index);
    bool ConstraintsHold(int coord_x, int coord_y);
    bool CanPlaceMiner(int index);
    void PrintConstraints();
    void CalculateConstraints(); 
};

#endif /* miningsite_h */
