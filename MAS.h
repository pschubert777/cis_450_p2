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
#include <iterator>
#include <map>

using namespace std;
enum job_type {small =0, medium =1, large = 2};

struct free_memory_details{
    int size;
    int starting_index;
};
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
// custom comparator for the worst fir data structure
class worst_fit_compare{
    
    bool operator()(const int &first_key, const int&second_key)const {
        return first_key >second_key;
    }
    
};
class MemoryAllocationSystem {
private:
    // memory allocation algorithm type
    string memory_allocation_algorithm_type;
    
    // statistics variables
    vector<int>num_free_requests;
    vector<int>num_allocation_requests;
    vector<int>total_num_allocation_operations;
    vector<int>total_num_free_operations;
    
    // Free memory locations
    // First Fit: first value- location of the free memory, second value- size of the free memory
    map<int, int>first_fit_memory_locations;
    // Next Fit: first value- location of the free memory, second value- size of the free memory
    map<int, int>next_fit_memory_locations;
    // Best Fit: first value- size of the free memory(sorted with smallests size first), second value- location of the free memory
    map<int, int>best_fit_memory_locations;
    // Worst Fit: first value- second value- size of the free memory (sorted with largest size first), location of the free memory
    map<int, int, worst_fit_compare>worst_fit_memory_locations;
    
    // next fit current index for getting the next free space that fits
     map<int, int>:: iterator  next_fit_current_index;
    
    //memory_unit_size
    int memory_unit_size;
    
    //number memory units
    int num_memory_units;
    
    // memory data structure
    vector<int> memory_data_structure;
     
    
public:
    MemoryAllocationSystem(const int &number_memory_units_in, const int &memory_unit_size_in, const string &memory_allocation_algorithm_type_in){
        // assign respective private attributes
        memory_unit_size = memory_unit_size_in;
        num_memory_units = number_memory_units_in;
        memory_allocation_algorithm_type = memory_allocation_algorithm_type_in;
        
        //resize the vector from empty to the size containing the respective number of memory units
        memory_data_structure.resize(num_memory_units, -1);
        
        //set the initial free areas of memory
        if (memory_allocation_algorithm_type=="firstrFit") {
            //first fit memory algorithm
            first_fit_memory_locations.insert(make_pair(0, num_memory_units));
        }
        else if (memory_allocation_algorithm_type=="nextFit"){
            //next fit memory algorithm
            
            next_fit_memory_locations.insert(make_pair(0, num_memory_units));
            next_fit_current_index = next_fit_memory_locations.begin();
        }
        else if(memory_allocation_algorithm_type=="bestFit"){
            //best fit memory algorithm
            best_fit_memory_locations.insert(make_pair(num_memory_units, 0));
        }
        else{
            // worst fit memory algorithm
            worst_fit_memory_locations.insert(make_pair(num_memory_units, 0));
        }
    }
    void fill_memory_data_structure(const int& starting_point, const int& end_point, const int&job_id){
            for (int j = starting_point; j < end_point; j++) {
                           memory_data_structure[j]=job_id;
                       }
        
    }
    int calculate_memory_units_remaining(const int &memory_units_needed, const int&memory_units_available){
        
        return memory_units_available-memory_units_needed;
    }
    int MallocFF(const int &num_memory_units, const int &job_id){
        
        if (memory_allocation_algorithm_type=="firstrFit") {
            //first fit memory algorithm
            return firstFit(num_memory_units, job_id);
        }
        else if (memory_allocation_algorithm_type=="nextFit"){
            //next fit memory algorithm
        }
        else if(memory_allocation_algorithm_type=="bestFit"){
            //best fit memory algorithm
        }
        else{
            // worst fit memory algorithm
        }
        
        
        return 0;
    }
    int firstFit(const int &num_memory_units, const int &job_id){
        //using a for loop to find the first location available
        int location= -1;
        
        int memory_remaining =0;
        pair<int, int> new_free_space;
        map<int, int>:: iterator free_memory_to_erase;
        
        
        for(auto i = first_fit_memory_locations.begin(); i != first_fit_memory_locations.end(); i++){
            if (num_memory_units <= i->second) {
                location = i->first;
                free_memory_to_erase = i;
                
                // fill up the memory data structure with the job id of the job
                fill_memory_data_structure(i->first, i->first+num_memory_units, job_id);
                
                // calculate the memory units remaining
                memory_remaining = calculate_memory_units_remaining(num_memory_units, i->second);
                // if the memory remaining does not equal 0, then create a new smaller free space
                if (memory_remaining >0) { new_free_space= make_pair(i->first+num_memory_units, memory_remaining); }

                break;
            }
            
        }
        
        if (location != -1 && memory_remaining>0) {
            first_fit_memory_locations.erase(free_memory_to_erase);
            first_fit_memory_locations.insert(new_free_space);
        }
        else if(location != -1&& memory_remaining ==0){
            first_fit_memory_locations.erase(free_memory_to_erase);
        }
        
        
        return location;
    }
    int nextFit(const int &num_memory_units, const int &job_id){
        bool found_spot_in_first_loop= false;
        
        int location= -1;
        int memory_remaining =0;
        pair<int, int> new_free_space;
        map<int, int>:: iterator free_memory_to_erase;
        // first for loop
        for (auto i = next_fit_current_index; i != next_fit_memory_locations.end(); i++) {
            if (num_memory_units <= i->second) {
                location = i->first;
                free_memory_to_erase = i;

                // fill up the memory data structure with the job id of the job
                fill_memory_data_structure(i->first, i->first+num_memory_units, job_id);
                
                // calculate the memory units remaining
                memory_remaining = calculate_memory_units_remaining(num_memory_units, i->second);
                // if the memory remaining does not equal 0, then create a new smaller free space
                if (memory_remaining >0) { new_free_space= make_pair(i->first+num_memory_units, memory_remaining); }
                
                
                found_spot_in_first_loop = true;
                next_fit_current_index = i++;
                
                break;
            }
        }
       
        if(found_spot_in_first_loop){
            for (auto i = next_fit_memory_locations.begin(); i!= next_fit_current_index; i++) {
                if (num_memory_units <= i->second) {
                               location = i->first;
                               free_memory_to_erase = i;
                               
                               // fill up the memory data structure with the job id of the job
                               fill_memory_data_structure(i->first, i->first+num_memory_units, job_id);
                               
                               // calculate the memory units remaining
                               memory_remaining = calculate_memory_units_remaining(num_memory_units, i->second);
                               // if the memory remaining does not equal 0, then create a new smaller free space
                               if (memory_remaining >0) { new_free_space= make_pair(i->first+num_memory_units, memory_remaining); }
                               
                               break;
                           }
            }
        }
        
        
        
        if (location != -1 && memory_remaining>0) {
                  next_fit_memory_locations.erase(free_memory_to_erase);
                  next_fit_memory_locations.insert(new_free_space);
                  next_fit_current_index = next_fit_memory_locations.find(new_free_space.first);
              }
         else if(location != -1&& memory_remaining ==0){
             next_fit_memory_locations.erase(free_memory_to_erase);
                
             // check if the next index is at the end
             map<int, int>:: iterator tmp(next_fit_current_index);
             tmp++;
             if (tmp == next_fit_memory_locations.end()) {
                 next_fit_current_index = next_fit_memory_locations.begin();
             }
             else{
                 next_fit_current_index++;
             }
             
              }
        
        
        
        return location;
    }
    
    
};

#endif /* MAC_h */
