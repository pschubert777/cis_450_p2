//
//  MAC.h
//  cis_450_p2
//
//  Created by Peter Schubert on 11/5/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#ifndef MAC_h
#define MAC_h


#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <utility> 
using namespace std;
enum job_type {small =0, medium =1, large = 2};

struct job{
    int job_id;
    int job_arrival_time;
};

struct heap_info {
    int allocation; // the amount of memory this element takes up
    int heap_location; // location where the heap is allocated
    int heap_memory_units_allocated; // memory units allocated for heap
    int arrival_time; // time that this element will be processed
    int life_time; // the length of a heap elements life
};
struct job_details {
    bool lost_objects;
    int job_id; // will grab id from job struct
    int job_arrival_time; // arrival time of the job
    int running_time; // generate running time. Small == 5 +/- 1, Medium == 10 +/- 1, Large == 25 +/-1
    int code_size; // generate code size. Small == 60 +/- 20, Medium == 90 +/- 30, Large == 170 +/-50
    int stack_size; // generate stack size. Small == 30 +/- 10, Medium == 60 +/- 20, Large == 90 +/-30
    
    int stack_memory_units_allocated; // memory units allocated for stack
    int code_memory_units_allocated; // memory units allocated for code
    
    int code_location; // starting point where the code is allocated
    int stack_location;// starting point where the stack is allocated
    int current_heap_element_group;
    vector<heap_info> heap; // each index is a heap element holding heap specific info
    job_type type;
};
class MemoryAllocationSystem {
private:

    int *memory_data_structure;
    
    
public:
    
    
    
};

#endif /* MAC_h */
