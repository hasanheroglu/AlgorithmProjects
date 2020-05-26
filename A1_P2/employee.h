//
//  employee.h
//  project2
//  Analysis of Algorithms Project 2
//  Heapsort Analysis
//  Hasan H. Eroğlu
//  150150058
//  Created by Hasan Hüsamettin Eroğlu on 01/11/2018.
//  Copyright © 2018 Hasan Hüsamettin Eroğlu. All rights reserved.
//

#ifndef employee_h
#define employee_h

class Employee {
public:
    int id;
    int callCount;
    int posCount;
    int negCount;
    int performance;
    
    Employee(){
        id = 0;
        callCount = 0;
        posCount = 0;
        negCount = 0;
        Evaluate();
    }
    Employee(int _id, int _callCount, int _posCount, int _negCount, int index){
        id = _id;
        callCount = _callCount;
        posCount = _posCount;
        negCount = _negCount;
        Evaluate();
    }
    Employee(const Employee &_employee){
        id = _employee.id;
        callCount = _employee.callCount;
        posCount = _employee.posCount;
        negCount = _employee.negCount;
        Evaluate();
    }
    void Evaluate(){
        performance = (2 * callCount) + posCount - negCount;
    }
    Employee & operator +=(const Employee &_employee){
        id = _employee.id;
        callCount += _employee.callCount;
        posCount += _employee.posCount;
        negCount += _employee.negCount;
        Evaluate();

        return *this;
    }
};

#endif /* employee_h */
