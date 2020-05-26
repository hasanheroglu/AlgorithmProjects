//
//  main.cpp
//  analysisofalgorithms
//  Student ID: 150150058
//  Student name: Hasan H. Eroglu
//  Course: Analysis of Algorithms 1 / BLG335E
//  Created by Hasan Hüsamettin Eroğlu on 11/10/2018.
//  Copyright © 2018 Hasan Hüsamettin Eroğlu. All rights reserved.
//  use this command to compile with no errors and warnings:
//  g++ main.cpp -std=c++11

#include <iostream>
//to use vector
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>

void ReadFile(std::vector<std::string> &);
void WriteFile(std::vector<std::string> &);
float ConvertTimeStampToNumber(const std::string, const std::string);
std::vector<float> GetTimeStamps(std::vector<std::string> &);
std::vector<float> GetPrices(std::vector<std::string> &);
void InsertionSort(std::vector<std::string> &, std::vector<float> &);
void MergeSort(std::vector<std::string> &, std::vector<float> &);

int main(int argc, const char * argv[]) {
    
    char algorithm = 'a';
    char feature = 'f';
    int size = 1;
    
    //Check # of commands
    if(argc == 7){ std::cout<<"All arguments are checked. Starting the program..."<<std::endl; }
    else{
        std::cout<<"Missing arguments in the command line. Check your command and try again!"<<std::endl;
        return 0;
    }
    
    for(int i=1; i<7; i++){
        switch(i){
            case 1:
                if(std::strcmp(argv[i],"-algo") != 0){
                    std::cout<<"Could not find algorithm argument. Terminating the program..."<<std::endl;
                    return 0;
                }
                break;
            case 2:
                if((std::strcmp(argv[i],"m") != 0 && std::strcmp(argv[i],"i") != 0)){
                    std::cout<<"Undefined algorithm type. Terminating the program..."<<std::endl;
                    return 0;
                }
                else{
                    if(std::strcmp(argv[i],"m") == 0)
                       algorithm = 'm';
                    else
                       algorithm = 'i';
                }
                break;
            case 3:
                if(std::strcmp(argv[i],"-feature") != 0){
                    std::cout<<"Could not find feature argument. Terminating the program..."<<std::endl;
                    return 0;
                }
                break;
            case 4:
                if((std::strcmp(argv[i],"t") != 0 && std::strcmp(argv[i],"p") != 0)){
                    std::cout<<"Undefined feature type. Terminating the program..."<<std::endl;
                    return 0;
                }
                else{
                    if(std::strcmp(argv[i],"t") == 0)
                        feature = 't';
                    else
                        feature = 'p';
                }
                break;
            case 5:
                if(std::strcmp(argv[i],"-size") != 0){
                    std::cout<<"Could not find size argument. Terminating the program..."<<std::endl;
                    return 0;
                }
                break;
            case 6:
                size = std::stoi(argv[i]);
                if(size > 1000000){
                    std::cout<<"Size is too large. Terminating the program..."<<std::endl;
                }
                break;
            default:
                //do nothing
                break;
        }
    }
    
    std::vector<std::string> rows(size);
    std::vector<float> time_stamps;
    std::vector<float> prices;
    clock_t time;
    ReadFile(rows);
    
    switch(feature){
        case 't':
            time_stamps.reserve(size);
            time_stamps = GetTimeStamps(rows);
            switch(algorithm){
                case 'i':
                    std::cout<<"Initiating Insertion Sort..."<<std::endl;
                    time = clock();
                    InsertionSort(rows, time_stamps);
                    time = clock() - time;
                    std::cout<<"It took "<<(float)time/CLOCKS_PER_SEC<<" seconds for program to sort with Insertion sort."<<std::endl;
                    break;
                case 'm':
                    std::cout<<"Initiating Merge Sort..."<<std::endl;
                    time = clock();
                    std::cout<<"Merge sort is initiated."<<std::endl;
                    MergeSort(rows, time_stamps);
                    std::cout<<"Merge sort is completed."<<std::endl;
                    time = clock() - time;
                    std::cout<<"It took "<<(float)time/CLOCKS_PER_SEC<<" seconds for program to sort with Merge sort."<<std::endl;
                    break;
                default:
                    std::cout<<"Algorithm type undefined. Terminating the program..."<<std::endl;
                    break;
            }
            break;
        case 'p':
            prices.reserve(size);
            GetPrices(rows);
            prices = GetPrices(rows);
            switch(algorithm){
                case 'i':
                    std::cout<<"Initiating Insertion Sort..."<<std::endl;
                    time = clock();
                    InsertionSort(rows, prices);
                    time = clock() - time;
                    std::cout<<"It took "<<(float)time/CLOCKS_PER_SEC<<" seconds for program to sort with Insertion sort."<<std::endl;
                    break;
                case 'm':
                    std::cout<<"Initiating Merge Sort..."<<std::endl;
                    time = clock();
                    std::cout<<"Merge sort is initiated."<<std::endl;
                    MergeSort(rows, prices);
                    std::cout<<"Merge sort is completed."<<std::endl;
                    time = clock() - time;
                    std::cout<<"It took "<<(float)time/CLOCKS_PER_SEC<<" seconds for program to sort with Merge sort."<<std::endl;
                    break;
                default:
                    std::cout<<"Algorithm type undefined. Terminating the program..."<<std::endl;
                    break;
            }
            break;
        default:
            std::cout<<"Feature type undefined. Terminating the program..."<<std::endl;
            break;
    }
    
    WriteFile(rows);
    
    return 0;
}

void ReadFile(std::vector<std::string> &rows){
    std::ifstream stock_market("log_inf.csv");
    if(stock_market.is_open()){
        std::cout<<"Reading the data from the file..."<<std::endl;
        for(int i=0; i < rows.size() + 1; i++){
            std::string line;
            if(i == 0){
                std::getline(stock_market, line);
            }
            else{
                std::getline(stock_market, line);
                rows[i-1] = line;
            }
        }
    }
    else{
        std::cout<<"Could not open the file. Terminating the program."<<std::endl;
        return;
    }
    
    std::cout<<"Completed the reading. Closing the file."<<std::endl;

    stock_market.close();
}

void WriteFile(std::vector<std::string> &rows){
    std::ofstream output_stream;
    std::string filename = "output_log.csv";
    output_stream.open(filename);
    
    if(output_stream.is_open()){
        std::cout<<"Writing sorted values to the output file..."<<std::endl;
        for(int i=0; i<rows.size(); i++){
            output_stream << rows[i] << std::endl;
        }
    }
    else{
        std::cout<<"Could not open the file. Terminating the program."<<std::endl;
        return;
    }
    std::cout<<"Completed the writing. Program is terminated."<<std::endl;
}

float ConvertTimeStampToNumber(const std::string date,const std::string time){
    std::stringstream datestream(date);
    std::stringstream timestream(time);
    std::string s_year;
    std::string s_month;
    std::string s_day;
    std::string s_hour;
    std::string s_min;
    std::string s_sec;
    
    int i_year;
    int i_month;
    int i_day;
    int i_hour;
    int i_min;
    float f_sec;
    
    std::getline(datestream, s_year, '-');
    i_year = std::stoi(s_year);
    std::getline(datestream, s_month, '-');
    i_month = std::stoi(s_month);
    std::getline(datestream, s_day);
    i_day = std::stoi(s_day);
    
    std::getline(timestream, s_hour, ':');
    i_hour = std::stoi(s_hour);
    std::getline(timestream, s_min, ':');
    i_min = std::stoi(s_min);
    std::getline(timestream, s_sec, ':');
    f_sec = std::stoi(s_sec);
    
    
    float total = (((((((i_year * 12 + i_month) * 31) + i_day) * 24) + i_hour) * 60) + i_min) * 60 + f_sec;
    return total;
}

std::vector<float> GetTimeStamps(std::vector<std::string> &rows){
    std::vector<float> time_stamps(rows.size());
    for(int i=0; i < rows.size(); i++){
        if(rows[i] == ""){
            time_stamps[i] = 0;
        }
        else{
            std::stringstream rowstream(rows[i]);
            std::string date;
            std::string time;
            std::getline(rowstream, date, ' ');
            std::getline(rowstream, time, ',');
            time_stamps[i] = ConvertTimeStampToNumber(date, time);
        }
        
    }
    
    return time_stamps;
}

std::vector<float> GetPrices(std::vector<std::string> &rows){
    std::vector<float> prices(rows.size());
    for(int i = 0; i < rows.size(); i++){
        if(rows[i] == ""){
            prices[i] = 0;
        }
        else{
            std::stringstream rowstream(rows[i]);
            std::string line;
            std::string price;
            std::getline(rowstream, line, ',');
            std::getline(rowstream, line, ',');
            std::getline(rowstream, price, ',');
            prices[i] = std::stof(price);
        }
        
    }
    
    return prices;
}

void InsertionSort(std::vector<std::string> &rows, std::vector<float> &numberstosort){
    std::cout<<"Insertion sort is initiated."<<std::endl;
    int k;
    for(int i=1; i < rows.size(); i++){
        k = i;
        for(int j=i-1; j >= 0; j--){
            if(numberstosort[k] < numberstosort[j]){
                float f_temp;
                std::string s_temp;
                f_temp = numberstosort[j];
                s_temp = rows[j];
                numberstosort[j] = numberstosort[k];
                rows[j] = rows[k];
                numberstosort[k] = f_temp;
                rows[k] = s_temp;
                k--;
            }
            else{
                break;
            }
        }
    }
    std::cout<<"Insertion sort is completed."<<std::endl;
}



void MergeSort(std::vector<std::string> &rows, std::vector<float> &numberstosort){
    if(rows.size() <= 1){
        return;
    }
    
    std::vector<std::string> rows_lo(rows.begin(), rows.begin() + (rows.size()/2));
    std::vector<std::string> rows_hi(rows.begin() + (rows.size()/2), rows.end());
        
    std::vector<float> numberstosort_lo(numberstosort.begin(), numberstosort.begin() + numberstosort.size()/2);
    std::vector<float> numberstosort_hi(numberstosort.begin() + numberstosort.size()/2, numberstosort.end());
        
    
    MergeSort(rows_lo, numberstosort_lo);
    MergeSort(rows_hi, numberstosort_hi);
        
        
    int j = 0, k = 0;
    for(int i=0; i < rows.size(); i++){
        if(j >= numberstosort_lo.size()){
            numberstosort[i] = numberstosort_hi[k];
            rows[i] = rows_hi[k];
            k++;
        }
        else if(k >= numberstosort_hi.size()){
            numberstosort[i] = numberstosort_lo[j];
            rows[i] = rows_lo[j];
            j++;
        }
        else{
            if(numberstosort_lo[j] <= numberstosort_hi[k]){
                numberstosort[i] = numberstosort_lo[j];
                rows[i] = rows_lo[j];
                j++;
            }
            else{
                numberstosort[i] = numberstosort_hi[k];
                rows[i] = rows_hi[k];
                k++;
            }
        }
    }
}
