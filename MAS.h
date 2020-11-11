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
#include <queue>
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
class comparator{
public:
    bool operator()(const job & job1, const job &job2) const{
        return job1.job_arrival_time > job2.job_arrival_time;
    }
    
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
public:
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
    // Best Fit:  first value- location of the free memory, second value- size of the free memory
    map<int, int>best_fit_memory_locations;
    // Worst Fit: first value- location of the free memory, second value- size of the free memory
    map<int, int>worst_fit_memory_locations;
    
    // next fit current index for getting the next free space that fits
     map<int, int>:: iterator  next_fit_current_index;
    
    //memory_unit_size
    int memory_unit_size;
    
    //number memory units
    int num_memory_units;
    
    // memory data structure
    vector<int> memory_data_structure;
     
    
public:
      // Description: constructor
       // Pre-condition: the number of memory units to be defined(int), the memory unit size (int), the type of memory allocaation algirthm (string)
       // Post-condition: initializes the type of memory allocation algorithm, the number of memory units, the memory unit size, initializes the memory data structure to be all -1, initializes the map to store the free locations according to the memory allocation algorithm
       // Author: Peter Schubert
    MemoryAllocationSystem(const int &number_memory_units_in, const int &memory_unit_size_in, const string &memory_allocation_algorithm_type_in){
        // assign respective private attributes
        memory_unit_size = memory_unit_size_in;
        num_memory_units = number_memory_units_in;
        memory_allocation_algorithm_type = memory_allocation_algorithm_type_in;
        
        //resize the vector from empty to the size containing the respective number of memory units
        memory_data_structure.resize(num_memory_units, -1);
        
        //set the initial free areas of memory
        if (memory_allocation_algorithm_type=="firstfit") {
            //first fit memory algorithm
            first_fit_memory_locations.insert(make_pair(0, num_memory_units));
        }
        else if (memory_allocation_algorithm_type=="nextfit"){
            //next fit memory algorithm
            
            next_fit_memory_locations.insert(make_pair(0, num_memory_units));
            next_fit_current_index = next_fit_memory_locations.begin();
        }
        else if(memory_allocation_algorithm_type=="bestfit"){
            //best fit memory algorithm
            best_fit_memory_locations.insert(make_pair(0,num_memory_units ));
        }
        else{
            // worst fit memory algorithm
            worst_fit_memory_locations.insert(make_pair(0,num_memory_units ));
        }
    }
    // Description: method that allocates the memory data structure with the respective job id
    // Pre-condition: the starting point of the element to be allocated, the end point of the element to be allocated, and the job id
    // Post-condition: the memory data structure for a certain number of elements, is filled with the job id that allocates it
    // Author: Peter Schubert
    void fill_memory_data_structure(const int& starting_point, const int& end_point, const int&job_id){
            for (int j = starting_point; j < end_point; j++) {
                           memory_data_structure[j]=job_id;
                       }
        
    }
    // Description: method to calculate the memory units remaining
    // Pre-condition: the number of memor units needed and the number of memory units available
    // Post-condition: returns the subtraction memory units available - memory units needed to get the amount of memory units free
    // Author: Nathan Carey
    int calculate_memory_units_remaining(const int &memory_units_needed, const int&memory_units_available){
        
        return memory_units_available-memory_units_needed;
    }
    // Description: method that allocates a code, staack, or heap element to memory based on the type of memory algorithm
    // Pre-condition: the number of memory units and the job id
    // Post-condition: calls a helper method firstfit, nextfit, bestfit, or worstfit, depending on the algorithm in use, allocates memory via the helper method and returns the result of that memory allocation
    // Author: Peter Schubert
    int MallocFF(const int &num_memory_units, const int &job_id){
        
        if (memory_allocation_algorithm_type=="firstfit") {
            //first fit memory algorithm
            return firstFit(num_memory_units, job_id);
        }
        else if (memory_allocation_algorithm_type=="nextfit"){
            //next fit memory algorithm
            return nextFit(num_memory_units, job_id);
        }
        else if(memory_allocation_algorithm_type=="bestfit"){
            //best fit memory algorithm
            return bestFit(num_memory_units, job_id);
        }
        else{
            // worst fit memory algorithm
            return worstFit(num_memory_units, job_id);
        }
        
        
        return 0;
    }
       // Description: method that allocates a code, stack, or heap element to memory based on the firstfit algorithm
       // Pre-condition: the number of memory units and the job id
       // Post-condition: searches for the first available open spot, starting at the beginning. If the allocation was sucessful returns the starting location of that memory, other wise returns -1
       // Author: Peter Schubert
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
        
    // Description: method that allocates a code, stack, or heap element to memory based on the nextfit algorithm
    // Pre-condition: the number of memory units and the job id
    // Post-condition: searches for the next available open spot based on a pointer which keeps track where in memory the next available spot is. If the allocation was sucessful returns the starting location of that memory, other wise returns -1
    // Author: Peter Schubert
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
       
        if(!found_spot_in_first_loop){
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
             
             if (next_fit_current_index == free_memory_to_erase) {
                 next_fit_current_index =  next_fit_memory_locations.erase(free_memory_to_erase);}
             else{
                  next_fit_memory_locations.erase(free_memory_to_erase);
             }
            
                
             if (!next_fit_memory_locations.empty() ) {
                
                 
                 if (next_fit_current_index == next_fit_memory_locations.end()) {
                     next_fit_current_index = next_fit_memory_locations.begin();
                 }
                 else{
                      map<int, int>:: iterator tmp(next_fit_current_index);
                 
                     tmp++;
                        if (tmp == next_fit_memory_locations.end()) {
                           
                           next_fit_current_index = next_fit_memory_locations.begin();
                                        }
                        else{
                            next_fit_current_index++;
                    }
                 }
                   
                            
                }
             else{
                 next_fit_current_index = next_fit_memory_locations.end();
             }
        }
           
        
        
        
        return location;
    }
    // Description: method that allocates a code, stack, or heap element to memory based on the bestfit algorithm
    // Pre-condition: the number of memory units and the job id
    // Post-condition: searches for the best available spot that is the smallest available spot that fits the memory being allocated. If the allocation was sucessful returns the starting location of that memory, other wise returns -1
    // Author: Peter Schubert
    int bestFit(const int &num_memory_units, const int &job_id){
        int location = -1;
        int memory_remaining =0;
        pair<int, int> new_free_space;
        map<int, int>:: iterator best_memory_space =best_fit_memory_locations.end();
        bool found_space =false;
        for (auto i = best_fit_memory_locations.begin(); i != best_fit_memory_locations.end(); i++){
            
            if (num_memory_units <= i->second && best_memory_space == best_fit_memory_locations.end()) {
                location = i->first;
                best_memory_space = i;
                               
                found_space = true;
              //if the space exactly fits then break, no need to search anymore
             if (num_memory_units ==best_memory_space->second) { break;}
            }
            else if (num_memory_units <= i->second && best_memory_space->second >i->second ) {
                location = i->first;
                best_memory_space = i;
                
                found_space = true;
                //if the space exactly fits then break, no need to search anymore
                if (num_memory_units ==best_memory_space->second) { break;}
            }
            
            
            
        }
        
        if (found_space) {

            fill_memory_data_structure(best_memory_space->first, best_memory_space->first+num_memory_units, job_id);
                                        
            // calculate the memory units remaining
            memory_remaining = calculate_memory_units_remaining(num_memory_units, best_memory_space->second);
            // if the memory remaining does not equal 0, then create a new smaller free space
            if (memory_remaining >0) { new_free_space= make_pair(best_memory_space->first+num_memory_units, memory_remaining); }
        }

        
        if (location != -1 && memory_remaining>0) {
                   best_fit_memory_locations.erase(best_memory_space);
                   best_fit_memory_locations.insert(new_free_space);
               }
       else if(location != -1&& memory_remaining ==0){
                   best_fit_memory_locations.erase(best_memory_space);
               }
        
        return location;
    }
    // Description: method that allocates a code, stack, or heap element to memory based on the worstfit algorithm
    // Pre-condition: the number of memory units and the job id
    // Post-condition: searches for the largest available spot in the memory data structure . If the allocation was sucessful returns the starting location of that memory, other wise returns -1
    // Author: Peter Schubert
    int worstFit(const int &num_memory_units, const int &job_id){
        int location = -1;
        int memory_remaining =0;
        pair<int, int> new_free_space;
        map<int, int>:: iterator worst_memory_space =worst_fit_memory_locations.end();
        bool found_space =false;
        for (auto i = worst_fit_memory_locations.begin(); i != worst_fit_memory_locations.end(); i++){
                      
            
            if (num_memory_units <= i->second &&  worst_memory_space== worst_fit_memory_locations.end()) {
                location = i->first;
               worst_memory_space = i;
                      
                found_space = true;
            }
             else if (num_memory_units <= i->second && worst_memory_space->second < i->second ) {
                    location = i->first;
                    worst_memory_space = i;
                          
                    found_space = true;
                    //if the space exactly fits then break, no need to search anymore
                
                }
                      
                      
                      
        }
                  
        if (found_space) {

            fill_memory_data_structure(worst_memory_space->first, worst_memory_space->first+num_memory_units, job_id);
                                                  
            // calculate the memory units remaining
            memory_remaining = calculate_memory_units_remaining(num_memory_units, worst_memory_space->second);
            // if the memory remaining does not equal 0, then create a new smaller free space
            if (memory_remaining >0) { new_free_space= make_pair(worst_memory_space->first+num_memory_units, memory_remaining); }
            
            }

                  
           if (location != -1 && memory_remaining>0) {
           worst_fit_memory_locations.erase(worst_memory_space);
           worst_fit_memory_locations.insert(new_free_space);
            }
            else if(location != -1&& memory_remaining ==0){
                worst_fit_memory_locations.erase(worst_memory_space);
            }
                  
            return location;
    }
    
    // Description: method that deallocates a code, stack, or heap element and puts that memory back into the firstfit or nextfit map that keeps track of the free space
    // Pre-condition: the starting location and the number of memory units
    // Post-condition: inserts the element, determines if there are any other free areas next to it and  if so merges the free spaces next to the newly inserted free space
    // Author: Peter Schubert
    void deallocate_firstFit_nextFit(const int& starting_location, const int & num_memory_units){
        pair<int, int>new_deallocated_free_space;
        if (memory_allocation_algorithm_type=="firstfit") {
            new_deallocated_free_space = make_pair(starting_location, num_memory_units);
            first_fit_memory_locations.insert(new_deallocated_free_space);
            map<int,int>::iterator inserted_element = first_fit_memory_locations.find(starting_location);
            
            map<int,int>::iterator prior_element((inserted_element == first_fit_memory_locations.begin())? first_fit_memory_locations.end():inserted_element);
            
            map<int,int>::iterator later_element(inserted_element);
            
            if (prior_element !=first_fit_memory_locations.end() ) {  prior_element--; }
    
            later_element++;
            
            //checking if the element is on the left most end of the memory
            
            if (prior_element == first_fit_memory_locations.end() &&later_element==first_fit_memory_locations.end() ) {
                
            }
            else if (prior_element == first_fit_memory_locations.end() &&later_element!=first_fit_memory_locations.end()&& inserted_element->first+inserted_element->second ==later_element->first) {
                first_fit_memory_locations[inserted_element->first]+=later_element->second;
                first_fit_memory_locations.erase(later_element);
            }
            //checking if the element is on the right most end of the memory
            else if (later_element==first_fit_memory_locations.end() && prior_element != first_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                first_fit_memory_locations[prior_element->first]+=inserted_element->second;
                first_fit_memory_locations.erase(inserted_element);
            }
            else if (prior_element != first_fit_memory_locations.end() && later_element!=first_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first && inserted_element->first+inserted_element->second ==later_element->first){
                first_fit_memory_locations[prior_element->first]+=inserted_element->second+later_element->second;
                first_fit_memory_locations.erase(inserted_element);
                first_fit_memory_locations.erase(later_element);
                
            }
            else if (prior_element != first_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                first_fit_memory_locations[prior_element->first]+=inserted_element->second;
                first_fit_memory_locations.erase(inserted_element);
            }
            else if(later_element!=first_fit_memory_locations.end() && inserted_element->first+inserted_element->second ==later_element->first ){
                first_fit_memory_locations[inserted_element->first]+=+later_element->second;
                first_fit_memory_locations.erase(later_element);
            }
        }
         else {

               new_deallocated_free_space = make_pair(starting_location, num_memory_units);
                    next_fit_memory_locations.insert(new_deallocated_free_space);
                    map<int,int>::iterator inserted_element = next_fit_memory_locations.find(starting_location);
                    
                    map<int,int>::iterator prior_element((inserted_element == next_fit_memory_locations.begin())? next_fit_memory_locations.end():inserted_element);
                    
                    map<int,int>::iterator later_element(inserted_element);
                    
                    if (prior_element !=next_fit_memory_locations.end() ) {  prior_element--; }
            
                    later_element++;
                    
                    //checking if the element is on the left most end of the memory
                    
                    if (prior_element == next_fit_memory_locations.end() &&later_element==next_fit_memory_locations.end() ) {
                        
                    }
                    else if (prior_element == next_fit_memory_locations.end() &&later_element!=next_fit_memory_locations.end()&& inserted_element->first+inserted_element->second ==later_element->first) {
                        if (next_fit_current_index ==later_element) { next_fit_current_index= inserted_element; }
                        next_fit_memory_locations[inserted_element->first]+=later_element->second;
                        next_fit_memory_locations.erase(later_element);
                    }
                    //checking if the element is on the right most end of the memory
                    else if (later_element==next_fit_memory_locations.end() && prior_element != next_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                        
                        if (next_fit_current_index ==inserted_element) { next_fit_current_index= prior_element; }
                        next_fit_memory_locations[prior_element->first]+=inserted_element->second;
                        next_fit_memory_locations.erase(inserted_element);
                    }
                    else if (prior_element != next_fit_memory_locations.end() && later_element!=next_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first && inserted_element->first+inserted_element->second ==later_element->first){
                        if (next_fit_current_index ==inserted_element || next_fit_current_index ==later_element) { next_fit_current_index= prior_element; }
                        next_fit_memory_locations[prior_element->first]+=inserted_element->second+later_element->second;
                        next_fit_memory_locations.erase(inserted_element);
                        next_fit_memory_locations.erase(later_element);
                        
                    }
                    else if (prior_element != next_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                        if (next_fit_current_index ==inserted_element) { next_fit_current_index= prior_element; }
                        next_fit_memory_locations[prior_element->first]+=inserted_element->second;
                        next_fit_memory_locations.erase(inserted_element);
                    }
                    else if(later_element!=next_fit_memory_locations.end() && inserted_element->first+inserted_element->second ==later_element->first ){
                        if (next_fit_current_index ==later_element) { next_fit_current_index= inserted_element; }
                        next_fit_memory_locations[inserted_element->first]+=+later_element->second;
                        next_fit_memory_locations.erase(later_element);
                    }
        }

}
    // Description: method that deallocates a code, stack, or heap element and puts that memory back into the bestfit or worstfit map that keeps track of the free space
       // Pre-condition: the starting location and the number of memory units
       // Post-condition: inserts the element, determines if there are any other free areas next to it and  if so merges the free spaces next to the newly inserted free space
       // Author: Peter Schubert
    void deallocate_bestFit_worstFit(const int& starting_location, const int & num_memory_units){
        
       pair<int, int>new_deallocated_free_space;
       if (memory_allocation_algorithm_type=="bestfit") {
           new_deallocated_free_space = make_pair(starting_location, num_memory_units);
           best_fit_memory_locations.insert(new_deallocated_free_space);
          map<int,int>::iterator inserted_element = best_fit_memory_locations.find(starting_location);
                          
          map<int,int>::iterator prior_element((inserted_element == best_fit_memory_locations.begin())? best_fit_memory_locations.end():inserted_element);
                          
          map<int,int>::iterator later_element(inserted_element);
                          
           if (prior_element !=best_fit_memory_locations.end() ) {  prior_element--; }
                  
            later_element++;
                          
           //checking if the element is on the left most end of the memory
                          
           if (prior_element == best_fit_memory_locations.end() &&later_element==best_fit_memory_locations.end() ) {
                              
                }
           else if (prior_element == best_fit_memory_locations.end() &&later_element!=best_fit_memory_locations.end()&& inserted_element->first+inserted_element->second ==later_element->first) {
                    best_fit_memory_locations[inserted_element->first]+=later_element->second;
                    best_fit_memory_locations.erase(later_element);
           }
            //checking if the element is on the right most end of the memory
           else if (later_element==best_fit_memory_locations.end() && prior_element != best_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
               best_fit_memory_locations[prior_element->first]+=inserted_element->second;
               best_fit_memory_locations.erase(inserted_element);
           }
           else if (prior_element != best_fit_memory_locations.end() && later_element!=best_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first && inserted_element->first+inserted_element->second ==later_element->first){
               best_fit_memory_locations[prior_element->first]+=inserted_element->second+later_element->second;
               best_fit_memory_locations.erase(inserted_element);
               best_fit_memory_locations.erase(later_element);
                              
                }
           else if (prior_element != best_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
               best_fit_memory_locations[prior_element->first]+=inserted_element->second;
               best_fit_memory_locations.erase(inserted_element);
                }
           else if(later_element!=best_fit_memory_locations.end() && inserted_element->first+inserted_element->second ==later_element->first ){
               best_fit_memory_locations[inserted_element->first]+=+later_element->second;
               best_fit_memory_locations.erase(later_element);
            }
        }
       else {
               new_deallocated_free_space = make_pair(starting_location, num_memory_units);
                worst_fit_memory_locations.insert(new_deallocated_free_space);
                map<int,int>::iterator inserted_element = worst_fit_memory_locations.find(starting_location);
                                           
                map<int,int>::iterator prior_element((inserted_element == worst_fit_memory_locations.begin())? worst_fit_memory_locations.end():inserted_element);
                                           
                map<int,int>::iterator later_element(inserted_element);
                                           
                if (prior_element !=worst_fit_memory_locations.end() ) {  prior_element--; }
                                   
                later_element++;
                                           
                //checking if the element is on the left most end of the memory
                                           
                if (prior_element == worst_fit_memory_locations.end() &&later_element==worst_fit_memory_locations.end() ) {   }
                else if (prior_element == worst_fit_memory_locations.end() &&later_element!=worst_fit_memory_locations.end()&& inserted_element->first+inserted_element->second ==later_element->first) {
                        worst_fit_memory_locations[inserted_element->first]+=later_element->second;
                        worst_fit_memory_locations.erase(later_element);
                }
                             //checking if the element is on the right most end of the memory
               else if (later_element==worst_fit_memory_locations.end() && prior_element != worst_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                        worst_fit_memory_locations[prior_element->first]+=inserted_element->second;
                       worst_fit_memory_locations.erase(inserted_element);
                }
              else if (prior_element != worst_fit_memory_locations.end() && later_element!=worst_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first && inserted_element->first+inserted_element->second ==later_element->first){
                    worst_fit_memory_locations[prior_element->first]+=inserted_element->second+later_element->second;
                    worst_fit_memory_locations.erase(inserted_element);
                    worst_fit_memory_locations.erase(later_element);
                                               }
                else if (prior_element != worst_fit_memory_locations.end() && prior_element->first+prior_element->second ==inserted_element->first){
                    worst_fit_memory_locations[prior_element->first]+=inserted_element->second;
                    worst_fit_memory_locations.erase(inserted_element);
              }
                else if(later_element!=worst_fit_memory_locations.end() && inserted_element->first+inserted_element->second ==later_element->first ){
                    worst_fit_memory_locations[inserted_element->first]+=+later_element->second;
                    worst_fit_memory_locations.erase(later_element);
                             }
              }

        
        
        
        
    }
    
    // Description: method that resets the memory data structurre area being deallocate to -1 and adds a new free space to the map of firstfit, nextfit, bestfit, or worstfit
       // Pre-condition: the starting location and the number of memory units
       // Post-condition: inserts the element, determines if there are any other free areas next to it and  if so merges the free spaces next to the newly inserted free space
       // Author: Peter Schubert
    void freeFF(const int &starting_location, const int& num_memory_units){
        
        for (int i=starting_location; i< starting_location +num_memory_units; ++i) {
            memory_data_structure[i]= -1;
        }
        
        
        if (memory_allocation_algorithm_type =="firstfit" ||memory_allocation_algorithm_type=="nextfit" ) {
            deallocate_firstFit_nextFit(starting_location, num_memory_units);
        }
 
        else{
            deallocate_bestFit_worstFit(starting_location, num_memory_units);
        }
        
    }

    // Description: method that retrieves the number of allocations
       // Pre-condition: the currrent time via time counter
       // Post-condition: retrieves the number of allocation requests at that specified time
       // Author: Nathan Carey
	int get_number_allocations(const int &time_counter) {
		return num_allocation_requests[time_counter];
	}

    // Description: method that retrieves the number of free requests
        // Pre-condition: the currrent time via time counter
        // Post-condition: retrieves the number of free requests at the specified time
        // Author: Nathan Carey
	int get_number_free_requests(const int &time_counter) {
		return num_free_requests[time_counter];
	}
    // Description: method that retrieves the number of free operations
           // Pre-condition: the currrent time via time counter
           // Post-condition: retrieves the number of free operations done  at the specified time
           // Author: Nathan Carey
	int get_number_free_operations(const int &time_counter) {
		return total_num_free_operations[time_counter];
	}

    // Description: method that retrieves the number of allocation operations
    // Pre-condition: the currrent time via time counter
    // Post-condition: retrieves the number of allocation operation at the specified time
    // Author: Nathan Carey
	int get_number_allocation_operations(const int &time_counter) {
		return total_num_allocation_operations[time_counter];
	}
    
    // Description: method that retrieves the average number of allocation operations
    // Pre-condition: the currrent time via time counter
    // Post-condition: retrieves the average number of allocation operation at the specified for the length of the time recorded so far
    // Author: Nathan Carey
	int get_number_avg_allocation_operations(const int &time_counter) {
		int number_operations = 0, sum_operations = 0;

		number_operations = time_counter + 1;

		for (int i = 0; i < time_counter; i++) {
			sum_operations += total_num_allocation_operations[i];
		}

		return (sum_operations / number_operations);

	}

    // Description: method that retrieves the average number of free operations
      // Pre-condition: the currrent time via time counter
      // Post-condition: retrieves the average number of free operation at the specified for the length of the time recorded so far
      // Author: Nathan Carey
	int get_number_avg_free_operations(const int &time_counter) {
		int number_operations = 0, sum_operations = 0;

		number_operations = time_counter + 1;

		for (int i = 0; i < time_counter; i++) {
			sum_operations += total_num_free_operations[i];
		}

		return (sum_operations / number_operations);
	}
    
      // Description: method that retrieves the external fragmentation
      // Pre-condition: the memory allocation algorithm type
      // Post-condition: retrieves the size of the map of the corresponding memory allocation algorithm type to get the number of open space
      // Author: Nathan Carey
	int calculate_external_fragmentation(string &algorithm_type) {
		int num_external_fragmentation = 0;


		if (algorithm_type == "firstfit") {
			num_external_fragmentation = int(first_fit_memory_locations.size()); 
		}
		else if (algorithm_type == "nextfit") {
			num_external_fragmentation = int(next_fit_memory_locations.size());
		}
		else if (algorithm_type == "bestfit") {
			num_external_fragmentation = int(best_fit_memory_locations.size());
		}
		else { // worstfit
			num_external_fragmentation =int( worst_fit_memory_locations.size());
		}

		return num_external_fragmentation;
	}

    // Description: method that retrieves the largest free space
      // Pre-condition: the memory allocation algorithm type
      // Post-condition: searches the map of the corresponding algorithm for the largest free space and returns its size as an integer
      // Author: Nathan Carey
	int find_largest_free_space(string &algorithm_type) {
		int current_largest_space = 0;


		if (algorithm_type == "firstfit") {
			for (auto i = first_fit_memory_locations.begin(); i != first_fit_memory_locations.end(); i++) {

				if (current_largest_space < i->second) {
					current_largest_space = i->second;
				}

			}
		}
		else if (algorithm_type == "nextfit") {
			for (auto i = next_fit_memory_locations.begin(); i != next_fit_memory_locations.end(); i++) {

				if (current_largest_space < i->second) {
					current_largest_space = i->second;
				}
			}
		}
		else if (algorithm_type == "bestfit") {
			for (auto i = best_fit_memory_locations.begin(); i != best_fit_memory_locations.end(); i++) {

				if (current_largest_space < i->second) {
					current_largest_space = i->second;
				}
			}
		}
		else { // worstfit
			for (auto i = worst_fit_memory_locations.begin(); i != worst_fit_memory_locations.end(); i++) {

				if (current_largest_space < i->second) {
					current_largest_space = i->second;
				}
			}
		}

		return current_largest_space;
	}
        // Description: method that retrieves the smallest free space
         // Pre-condition: the memory allocation algorithm type
         // Post-condition: searches the map of the corresponding algorithm for the smallest free space and returns its size as an integer
         // Author: Nathan Carey
	int find_smallest_free_space(string &algorithm_type) {
		int current_smallest_space = INT_MAX;


		if (algorithm_type == "firstfit") {
			for (auto i = first_fit_memory_locations.begin(); i != first_fit_memory_locations.end(); i++) {

				if (current_smallest_space > i->second) {
					current_smallest_space = i->second;
				}

			}
		}
		else if (algorithm_type == "nextfit") {
			for (auto i = next_fit_memory_locations.begin(); i != next_fit_memory_locations.end(); i++) {

				if (current_smallest_space > i->second) {
					current_smallest_space = i->second;
				}
			}
		}
		else if (algorithm_type == "bestfit") {
			for (auto i = best_fit_memory_locations.begin(); i != best_fit_memory_locations.end(); i++) {

				if (current_smallest_space > i->second) {
					current_smallest_space = i->second;
				}
			}
		}
		else { // worstfit
			for (auto i = worst_fit_memory_locations.begin(); i != worst_fit_memory_locations.end(); i++) {

				if (current_smallest_space > i->second) {
					current_smallest_space = i->second;
				}
			}
		}

		return current_smallest_space;
	}


};

#endif /* MAC_h */
