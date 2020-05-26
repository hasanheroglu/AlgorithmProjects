//
//  league.h
//  project3
/*
 *   Student Name: Hasan H. Eroğlu
 *   Student ID: 150150058
 *   Analysis of Algorithms II - Project 3
 */
//  Created by Hasan Eroglu on 14.05.2019.
//  Copyright © 2019 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef league_h
#define league_h

class Team{
public:
    int point;
    int remainingMatchCount;
};


class League{
public:
    int teamCount;
    std::vector< std::vector<int> > matches;
    std::vector<Team> teams;
    std::vector<int> eliminationList;
    League();
    int SetWinCapacity(int, int);
    void ReadFile(std::string);
    void WriteFile(std::string);
};


#endif /* league_h */
