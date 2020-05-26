//
//  main.cpp
//  Analysis of Algorithms Project 2
//  Heapsort Analysis
//  Hasan H. Eroğlu
//  150150058
//  Created by Hasan Hüsamettin Eroğlu on 01/11/2018.
//  Copyright © 2018 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <ctime>

#include "employee.h"
#include "heap.h"


// int argc, const char * argv[]

void ReadFile(int, Heap<Employee> &, Heap<Employee> &, int *&, int *&, int &, int &);

void PrintDayStatistics(int, Heap<Employee> &, Heap<Employee> &, int);

void ReadNumbers(Heap<int> &, int *&);

void WriteFile(Employee *&, int, std::string);

void WriteFile(int *&, int, std::string);

int main() {
    
    int dayCount = 10;
    
    int heapSize = 800;
    int heapNumbersSize = 2000000;
    
    int *performances = new int[heapSize];
    int *calls = new int[heapSize];
    int *numbers = new int[heapNumbersSize];
    
    for(int i=0; i < heapSize; i++){
        performances[i] = 0;
        calls[i] = 0;
    }
    
    int maxId = 0;
    Heap<Employee> heapPerformance(heapSize);
    Heap<Employee> heapCalls(heapSize);
    Heap<int>   heapNumbers(heapNumbersSize);
    
    
    
    for(int i=1; i <= dayCount; i++){
        ReadFile(i, heapPerformance, heapCalls, performances, calls, heapSize, maxId);
    }
    
    ReadNumbers(heapNumbers, numbers);
    WriteFile(heapPerformance.heap, heapSize, "performance");
    WriteFile(heapCalls.heap, heapSize, "call");
    WriteFile(heapNumbers.heap, heapNumbersSize, "numbers");

    
    delete [] performances;
    delete [] calls;
    delete [] numbers;
    
    return 0;
}

void ReadFile(int dayCount, Heap<Employee> &heapPerformance, Heap<Employee> &heapCalls, int *& performances, int *& calls, int &heapSize, int &_maxId){
    
    int index = 0;
    Employee employee;
    bool isPresent = false;
    
    
    std::string dayLogFile = "day" + std::to_string(dayCount) + ".csv";
    std::cout<<"Reading "<<dayLogFile<<std::endl;
    std::ifstream dayLog(dayLogFile);
    if(dayLog.is_open()){
        std::string line;
        while(std::getline(dayLog, line, ',')){
            isPresent = false;
            employee.id = std::stoi(line);
            std::getline(dayLog, line, ',');
            employee.callCount = std::stoi(line);
            std::getline(dayLog, line, ',');
            employee.posCount = std::stoi(line);
            std::getline(dayLog, line, '\n');
            employee.negCount = std::stoi(line);
            employee.Evaluate();
            
            if(dayCount == 1){
                performances[index] = employee.performance;
                calls[index] = employee.callCount;
                heapPerformance.FillHeap(index, employee);
                heapCalls.FillHeap(index, employee);
            }
            
            else{
                if(employee.id <= _maxId){
                    for(int i=0; i < heapSize; i++){
                        if(employee.id == heapPerformance.heap[i].id){
                            heapPerformance.IncreaseKey(performances, i, employee.performance, employee);
                            break;
                        }
                    }
                    for(int i=0; i < heapSize; i++){
                        if(employee.id == heapCalls.heap[i].id){
                             heapCalls.IncreaseKey(calls, i, employee.callCount, employee);
                            break;
                        }
                    }
                }
                else{
                    int oldHeapSize = heapSize;
                    heapSize = heapPerformance.Insert(performances, employee.performance, employee, oldHeapSize);
                    heapSize = heapCalls.Insert(calls, employee.callCount, employee, oldHeapSize);
                }
             }
            
            if(employee.id > _maxId)
                _maxId = employee.id;
            
            index++;
        }
    }
    else
        std::cout<< "Could not open the file. Terminating the program." << std::endl;
    
    dayLog.close();
    
    heapPerformance.HeapSort(performances);
    heapCalls.HeapSort(calls);
    PrintDayStatistics(dayCount, heapPerformance, heapCalls, heapSize);
}

void ReadNumbers(Heap<int> &heapNumbers, int *& numbers){
    
    int index = 0;
    int number = 0;
    
    std::string dayLogFile = "numbers.csv";
    std::cout<<"Reading "<<dayLogFile<<std::endl;
    std::ifstream dayLog(dayLogFile);
    if(dayLog.is_open()){
        std::string line;
        while(std::getline(dayLog, line, '\n')){
            number = std::stoi(line);
            
            
            numbers[index] = number;
            heapNumbers.FillHeap(index, number);
            
            index++;
        }
    }
    else
        std::cout<< "Could not open the file. Terminating the program." << std::endl;
    
    heapNumbers.BuildMaxHeap(numbers);
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 200000; j++){
            index--;
            heapNumbers.heap[index] = heapNumbers.ExtractMax(numbers);
        }
    }
    
    dayLog.close();

}

void PrintDayStatistics(int dayCount, Heap<Employee> &heapPerformance, Heap<Employee> &heapCalls, int heapSize){
    std::cout<<"AFTER DAY-"<<dayCount<<std::endl;
    
    std::cout<<"BEST PERFORMANCE(ID):  "<<heapPerformance.heap[heapSize - 1].id<<", "
    <<heapPerformance.heap[heapSize - 2].id<<", "<<heapPerformance.heap[heapSize - 3].id<<std::endl;
    std::cout<<"BEST PERFORMANCE:  "<<heapPerformance.heap[heapSize - 1].performance<<", "
    <<heapPerformance.heap[heapSize - 2].performance<<", "<<heapPerformance.heap[heapSize - 3].performance<<std::endl;
    
    if(dayCount == 10){
        std::cout<<"WORST PERFORMANCE(ID):   "<<heapPerformance.heap[0].id<<", "
        <<heapPerformance.heap[1].id<<", "<<heapPerformance.heap[2].id<<std::endl;
        std::cout<<"WORST PERFORMANCE:   "<<heapPerformance.heap[0].performance<<", "
        <<heapPerformance.heap[1].performance<<", "<<heapPerformance.heap[2].performance<<std::endl;
    }
    
    std::cout<<"MAXIMUM CALLS(ID):      "<<heapCalls.heap[heapSize - 1].id<<", "
    <<heapCalls.heap[heapSize - 2].id<<", "<<heapCalls.heap[heapSize - 3].id<<std::endl;
    std::cout<<"MAXIMUM CALLS:      "<<heapCalls.heap[heapSize - 1].callCount<<", "
    <<heapCalls.heap[heapSize - 2].callCount<<", "<<heapCalls.heap[heapSize - 3].callCount<<std::endl;
    
    if(dayCount == 10){
        std::cout<<"MINIMUM CALLS(ID):      "<<heapCalls.heap[0].id<<", "
        <<heapCalls.heap[1].id<<", "<<heapCalls.heap[2].id<<std::endl;
        std::cout<<"MINIMUM CALLS:      "<<heapCalls.heap[0].callCount<<", "
        <<heapCalls.heap[1].callCount<<", "<<heapCalls.heap[2].callCount<<std::endl;
    }
}


void WriteFile(Employee *& employees, int heapSize, std::string filePrefix){
    std::ofstream output_stream;
    std::string filename = "_output_log.csv";
    filename = filePrefix + filename;
    output_stream.open(filename);
    
    if(output_stream.is_open()){
        std::cout<<"Writing sorted values to the output file..."<<std::endl;
        for(int i=0; i<heapSize; i++){
            output_stream << employees[i].id <<","<<employees[i].callCount <<","<<employees[i].posCount <<","<<employees[i].negCount <<","<<employees[i].performance <<std::endl;
        }
    }
    else{
        std::cout<<"Could not open the file. Terminating the program."<<std::endl;
        return;
    }
    std::cout<<"Completed the writing. Program is terminated."<<std::endl;
}

void WriteFile(int *& numbers, int heapSize, std::string filePrefix){
    std::ofstream output_stream;
    std::string filename = "_output_log.csv";
    filename = filePrefix + filename;
    output_stream.open(filename);
    
    if(output_stream.is_open()){
        std::cout<<"Writing sorted values to the output file..."<<std::endl;
        for(int i=0; i<heapSize; i++){
            output_stream << numbers[i] <<std::endl;
        }
    }
    else{
        std::cout<<"Could not open the file. Terminating the program."<<std::endl;
        return;
    }
    std::cout<<"Completed the writing. Program is terminated."<<std::endl;
}


