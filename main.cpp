//
//  main.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/20/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//
// testing that this worked

#include "PCB.h"
using namespace  std;



int main() {

    int small=0, medium=0, large =0, run_time;
    vector<job>queue;
    
    do {
        cout << "Please enter a small job distribution" << endl;
        cin >> small;
        cout << "Please enter a medium job distribution" << endl;
        cin  >> medium;
        
        cout << "Please enter a large job distribution" << endl;
        cin >> large;
        
    } while (small +medium+large !=100);
    
    cout << "How long should the program run?" << endl;
    cin >> run_time;
    
    
    
    
    PCB myval(small, medium, large, run_time);
    myval.job_assignments(queue);
    
    

    return 0;
}
