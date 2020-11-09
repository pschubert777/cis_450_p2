//
//  PCB.h
//  cis_450_p2
//
//  Created by Peter Schubert on 10/24/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#ifndef PCB_h
#define PCB_h

#include <cmath>
#include <fstream>
#include <time.h>
#include "MAS.h"


struct heap_elements {
    int job_id;
    int element_id;
};

class PCB{
private:
    bool lost_object_simulation;
    int total_running_time;
    int total_jobs;
    int num_small_jobs;
    int num_medium_jobs;
    int num_large_jobs;
    int memory_unit_size;
    vector<job_details> jobs;
    
    ofstream log;
    
public:
    PCB(const double &small_job_distribution, const double &medium_job_distribution, const double &large_job_distribution, const int &total_run_time, const int &memory_unit_size_in, const bool& run_lost_object_simulation, const string& log_file){
        //assign total_run_time to total_running_time
        total_running_time = total_run_time;
        
        // calculate total number of jobs
        total_jobs = total_running_time/3;
        
        // calculate the number of small jobs
        num_small_jobs =  round(total_jobs*(small_job_distribution/100));
        
        //calculate the number of medium jobs
        num_medium_jobs =  round(total_jobs*(medium_job_distribution/100));
        
        //calculate the number of large jobs
        num_large_jobs =  round(total_jobs*(large_job_distribution/100));
        
        memory_unit_size= memory_unit_size_in;
        
        lost_object_simulation = run_lost_object_simulation;
        
        // in the case that total jobs is more than  the jobs combined
        total_jobs = num_medium_jobs+num_small_jobs+num_large_jobs;
        
        log.open(log_file);
        
    }
    // Description: method for randomly assigning jobs
    // Pre-condition: a valid vector of type job struct
    // Post-condition: creats new jobs with unique id's and creats for each job a job struct (stored in queue) and job_details struct (stored in jobs struct private variable), and witin the job_details a vector of heap info to detail the allocation and arrival time of the heap elements
    // Author: Peter Schubert
    void job_assignments(vector<job> &queue){
        
        int i =0; // number of jobs
        int tmp_small=num_small_jobs, tmp_medium=num_medium_jobs, tmp_large=num_large_jobs;
        int range_span = 5,initial_value_range = 1; // range and initial value for arrival times
        
        // count the number of each of the jobs to determine every 100th job to be a job simulated with lost objects
        int count_num_small_jobs =0,  count_num_medium_jobs=0, count_num_large_jobs=0;
        
        
        while (i <total_jobs) {
            job_details new_job;
            job new_job_for_queue;
            
            //assign job id and job type
            new_job.job_id=i;
            new_job_for_queue.job_id =i;
            new_job.type = assign_job_type(tmp_small, tmp_medium, tmp_large);
            
            //incrment counters if using lost object simulation
            increment_job_type_counters_for_lost_object(new_job.type, count_num_small_jobs, num_medium_jobs, num_large_jobs);
            
            // set the initial heap  group element starting point at index 0
            new_job.current_heap_element_group=0;
            
             // calculate the arrival time
            new_job_for_queue.job_arrival_time = calculate_arrival_time(range_span, initial_value_range);
            new_job.job_arrival_time = new_job_for_queue.job_arrival_time;
            
            
           
            new_job.running_time = calculate_run_time(new_job.type);
            //**calculate code size method should go here**
            new_job.code_size  = calculate_code_size(new_job.type);
            //**calculate stack size method should go here**
            new_job.stack_size= calculate_stack_size(new_job.type);
            //**calculate heap elements should go here**
            calculate_num_heap_elements(new_job.type, new_job);
            calculate_heap_time(new_job, new_job_for_queue.job_arrival_time);
            
            calculate_memory_unit_size_stack_and_code(new_job);
            
            // determine if a particular job will lose all of its heap elements (if 100th element
            determine_if_job_is_lost_object(new_job,count_num_small_jobs, count_num_medium_jobs, count_num_large_jobs);
            
            
            //initialize code and stack locations
            new_job.code_location = -1;
            new_job.stack_location= -1;
            
            
            jobs.push_back(new_job);
            queue.push_back(new_job_for_queue);
            i++;
        }
    }
   
    // Description: method for  aassigning job types
    // Pre-condition: the number of remaining small, medium, and large jobs
    // Post-condition: a randomly assign job type and return the type that was selected based on the number (distribution of each type remaning)
    // Author: Peter Schubert
    job_type assign_job_type(int& tmp_small, int& tmp_medium, int& tmp_large){
        job_type tmp_val;
        
        // select the job type
        if (tmp_small >0 && tmp_medium>0 && tmp_large>0) { tmp_val =job_type(rand()%3); }
        else if (tmp_small >0 && tmp_medium>0){tmp_val = job_type(rand()%2); }
        else if (tmp_small >0 && tmp_large>0){ tmp_val = (rand()%2==0)? small: large ;}
        else if (tmp_medium >0 && tmp_large>0){ tmp_val = job_type(rand()%2+1);}
        else if (tmp_small >0){ tmp_val = small; }
        else if (tmp_medium>0){ tmp_val = medium;}
        else { tmp_val = large;}
        
        // subtract the number of available job types. Will update due to pass by reference
        
        if (tmp_val== large) { tmp_large-=1; }
        else if (tmp_val == medium){ tmp_medium-=1;}
        else{ tmp_small-=1; }
        
        return tmp_val;
    }
    
    void calculate_memory_unit_size_stack_and_code(job_details &new_job){
        
        new_job.code_memory_units_allocated = ceil(new_job.code_size/double(memory_unit_size));
        new_job.stack_memory_units_allocated= ceil(new_job.stack_size/double(memory_unit_size));
    }
    
    void determine_if_job_is_lost_object(job_details &new_job, const int& num_small_jobs, const int& num_medium_jobs, const int& num_large_jobs){
        
        if (lost_object_simulation && new_job.type== small && num_small_jobs%100 ==0 && num_small_jobs >0 ) {
            new_job.lost_objects = true;
        }else if (lost_object_simulation && new_job.type== medium && num_medium_jobs%100 ==0&& num_medium_jobs >0) {
            new_job.lost_objects = true;
        }
        else if (lost_object_simulation && new_job.type== large && num_large_jobs %100 ==0&& num_large_jobs >0) {
            new_job.lost_objects = true;
            }
        else {
            new_job.lost_objects = false;
        }
        
    }
    void increment_job_type_counters_for_lost_object(const job_type &type, int &num_small_jobs, int&num_medium_jobs, int &num_large_jobs ){
        
        if (lost_object_simulation && type ==small) {
            num_small_jobs++;
        }
        else if (lost_object_simulation && type ==medium){
            num_medium_jobs++;
        }
        else if (lost_object_simulation && type ==large){
            num_large_jobs++;
        }
        
        
    }
    
    // Description: method for calculating  the arrival time of a job
    // Pre-condition: range span, initial value range
    // Post-condition: returns the arrival time result, based on an inital range of time units 1-5, and increment by 3
    // Author: Peter Schubert
    int calculate_arrival_time(const int &range_span, int &initial_value_range){
        
       int arrival_result=rand()%range_span+ initial_value_range;
        
        initial_value_range+=3;
        
        return arrival_result;
        
    }

    
    // Description: method for calculating run time
    // Pre-condition: a valid job type
    // Post-condition: returns a randomly assigned run time for a job based on the job type
    // Author: Peter Schubert
    int calculate_run_time(const job_type& type){
        int run_time=0;
        if (type == large) {
            run_time = rand()%3+24;
        }
        else if (type==medium){
             run_time = rand()%3+9;
        }
        else{
             run_time = rand()%3+4;
        }
        
        return run_time;
    }
    // Description: method for calculating code size
    // Pre-condition: a valid job type
    // Post-condition: returns the code size of the job based on the job type
    // Author: Peter Schubert
    int calculate_code_size(const job_type &type){
        int code_size=0;
               if (type == large) {
                  code_size = rand()%101+120;
               }
               else if (type==medium){
                   code_size = rand()%61+60;
               }
               else{
                    code_size = rand()%41+40;
               }
               
        return code_size;
    }

    
    // Description: method for calculating stack size.
    // Pre-condition: What do input do you need for the function to work
    // Post-condition: What is the end result of the function or what do you get out of the function
    // Author: Nathan Carey
    int calculate_stack_size(const job_type &type){
        int stack_size = 0;

        if (type == large) {
            stack_size = rand() % 61 + 60;
        }
        else if (type == medium) {
            stack_size = rand() % 41 + 40;
        }
        else {
            stack_size = rand() % 21 + 20;
        }

        return stack_size;
    }


    // Description: method for calculating heap element information
    // Pre-condition: Needs a struct object of heap_info. Empty Struct object needs to be created beforehand!!!
    // Post-condition: return the number of heap elements for this job, assign values to job_heap object for allocation and arrival_time
    // Author: Nathan Carey
    void calculate_num_heap_elements(const job_type &type, job_details &job_details){
       
        int num_heap_elements = 0; // return value

        if (type == large) {
            num_heap_elements = job_details.running_time * 250;
        }
        else if (type == medium) {
            num_heap_elements = job_details.running_time * 100;
        }
        else {
            num_heap_elements = job_details.running_time * 50;
        }
        
        // add the random allocation size of heap element to the object, as well as add that object into the vector of heap_info in job_details.
        for (int i = 0; i <= num_heap_elements - 1; i++) { // should run for # of heap elements.
            heap_info heap_element;
            heap_element.allocation = rand() % 21 + 30;
            // added by peter, calculates the memory units needed to be allocated
            heap_element.heap_memory_units_allocated = ceil(heap_element.allocation/double(memory_unit_size));
            heap_element.heap_location = -1;
            job_details.heap.push_back(heap_element);
        }
       
    }

    // Description: method for calculating heap element information
    // Pre-condition: needs a job_details object to already have its vector of heap_info created
    // Post-condition: assigns jobs heap elements arrival times.
    // Author: Nathan Carey
    void calculate_heap_time(job_details& job_info, int job_arrival_time){
      // seed the random numbers
      srand(static_cast<unsigned int>(time(0)));
       
        vector<int> duration; // will hold an index of each time unit within run time
        
        int jobs_per_time = 0; // the number of jobs per time unit. (aka heap groups)
        jobs_per_time = int(job_info.heap.size() / job_info.running_time);
          
       
        int heap_group = 0; // used for indexing a heap element
        
        for (int i = 0; i < job_info.running_time; i++) {
            int beginning_time = job_arrival_time + i;
            int end_time = job_arrival_time + job_info.running_time;
            
            for (int j = 0; j < jobs_per_time; j++) {
                int random_lifetime = rand() % (end_time - beginning_time) + 1;
                job_info.heap[heap_group].arrival_time = beginning_time;
                job_info.heap[heap_group].life_time = random_lifetime;
                heap_group++;
            }
        }
    }


	// helper function for testing
	void get_stack_size(vector<int>&run_time, vector<job_type>&job_type, vector<int>&stack_size) {
        for (int i = 0; i < jobs.size(); i++) {
            job_type.push_back(jobs[i].type);
            stack_size.push_back(jobs[i].stack_size);
        }
    }

	// helper function for testing
	// get number of heap elements and size of each element
	void get_heap_elements(vector<int>&run_time, vector<job_type>&job_type, vector<int>&num_heap_elements, vector<vector<heap_info>>&job_heap, vector<int>&running_time){
        
        
        for (int i = 0; i < jobs.size(); i++) {
            job_type.push_back(jobs[i].type);
            running_time.push_back(jobs[i].running_time);
            num_heap_elements.push_back(int(jobs[i].heap.size()));
            
            // index i of heap_element_sizes map to index i of heap_element_time.
            // will be in reverse order i beleive
            
            // these two will be of size heap.size() much greater than jobs.size()!!!
            // job heap will contain at index i, job[i]'s heap. The heap is a vector of heap_info structs with attributes allocation and arrival time.
            // for testing we can cycle through job_heap[i][j] and check values are withing bounds at j
            job_heap.push_back(jobs[i].heap);
                
            
        }
    }
    
    //helper method for testing
    void get_num_of_each_job(vector<int>&num_job){
     
        num_job.push_back(num_small_jobs);
        num_job.push_back(num_medium_jobs);
        num_job.push_back(num_large_jobs);
        num_job.push_back(total_jobs);
    }
          //helper method for testing
    void get_run_code_size(vector<int>&run_time,vector<job_type>&job__type, vector<int>&code_size ){
        for (int i =0; i< jobs.size(); ++i) {
            run_time.push_back(jobs[i].running_time);
            job__type.push_back(jobs[i].type);
            code_size.push_back(jobs[i].code_size);
            
        }
    }

    // Description: method for printing out job information to file
    // Pre-condition: What do input do you need for the function to work
    // Post-condition: What is the end result of the function or what do you get out of the function
    // Author: Nathan Carey
    void print_job_info() {
         ofstream out_file;
         out_file.open("test_file.txt");
         

         if (!out_file) {
             cout << "Could not open output file" << endl;
             exit(1);
         }
         for (int i = 0; i < jobs.size(); i++) { // using PCB jobs vector
             int heap_element_factor = 0;
             if (jobs[i].type == large) {
                 heap_element_factor = 250;
             }
             else if (jobs[i].type == medium) {
                 heap_element_factor = 100;
             }
             else {
                 heap_element_factor = 50;
             }

             int jobs_per_time = 0;
             jobs_per_time = int(jobs[i].heap.size() / jobs[i].running_time);

             // NOTE: not showing "# memeory units allocate for all # time units" yet.
             cout << jobs[i].type << " job" << endl;
             cout << "Run Time: " << jobs[i].running_time << " time units" << endl;
             cout << "Code Size: " << jobs[i].code_size << " memory" << endl;
             cout << "Stack Size: " << jobs[i].stack_size << " memory units" << endl;
             cout << "Heap Elements: " << jobs[i].running_time << " * " << heap_element_factor << " = " << jobs[i].heap.size() << " heap elements" << endl;
             cout << jobs_per_time << " heap elements arrive each time unit" << endl << endl;

             for (int j = 0; j < jobs[i].heap.size(); j++) {
                 // NOTE: not showing memory units lifetime still
                 cout << "Heap element " << j << ": " << jobs[i].heap[j].allocation << "\t" << jobs[i].heap[j].arrival_time << " time unts" << endl;
             }

         }
     }
    
    void allocate_and_return_heap_elements(const int& job_id, MemoryAllocationSystem &system, vector<heap_elements> & active_heap_jobs ,const int &current_time_unit ){
          // ***NEED TO FINISH try catch block if no memory***
       
        try {
                   int heap_location = -1;
                   int job_group_size = int(jobs[job_id].heap.size())/jobs[job_id].running_time;
                   
                   int size =jobs[job_id].current_heap_element_group+job_group_size;
                   int i =jobs[job_id].current_heap_element_group;
                  
                   while (i < size) {
                       
                     
                      heap_location =  system.MallocFF(jobs[job_id].heap[i].heap_memory_units_allocated, job_id);
                       
                       if (heap_location == -1) {
                           throw invalid_argument("Memory Allocation System ran out of memory!");
                       }
                       else{
                           jobs[job_id].heap[i].heap_location = heap_location;
                       }
                       
                       log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Heap Element ID: "<<i<< " Memory Units Allocated: "<<jobs[job_id].heap[i].heap_memory_units_allocated << endl;
                       
                       i++;
                   }
                   for (int j = jobs[job_id].current_heap_element_group; j <size ; j++) {
                          heap_elements x;
                          x.job_id = job_id;
                          x.element_id= j;
                          active_heap_jobs.push_back(x);
                      }
                       jobs[job_id].current_heap_element_group = i;
        } catch (invalid_argument & message) {
            
            int job_group_size = int(jobs[job_id].heap.size())/jobs[job_id].running_time;
            int size =jobs[job_id].current_heap_element_group+job_group_size;
            
            for (int i =jobs[job_id].current_heap_element_group; i < size; i++) {
                if (jobs[job_id].heap[i].heap_location != -1) {
                    system.freeFF(jobs[job_id].heap[i].heap_location, jobs[job_id].heap[i].heap_memory_units_allocated);
                }
            }
            
            
            throw invalid_argument("The simulation has ended!");
        }
       
     
        
        
    }
    
    void allocate_new_job(const int& job_id, MemoryAllocationSystem &system,vector<int> &active_jobs, vector<heap_elements> & active_heap_jobs, const int &current_time_unit){
        try {
            
      
         // ***NEED TO FINISH try catch block if no memory***
        int stack_location =-1, code_location = -1, heap_location = -1;
        stack_location =  system.MallocFF(jobs[job_id].stack_memory_units_allocated, job_id);
        if (stack_location == -1) {
           throw invalid_argument("Memory Allocation System ran out of memory!");
        }
        else{
            jobs[job_id].stack_location = stack_location;
        }
        
        log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Code Memory Units Allocated:  "<<jobs[job_id].code_memory_units_allocated<< endl;
       
        code_location =  system.MallocFF(jobs[job_id].code_memory_units_allocated, job_id);
        
        if (code_location==-1) {
            throw invalid_argument("Memory Allocation System ran out of memory!");
        }
        else{
            jobs[job_id].code_location = code_location;
        }
        
         log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Stack Memory Units Allocated: "<<jobs[job_id].stack_memory_units_allocated<< endl;
        
        int job_group_size = int(jobs[job_id].heap.size())/jobs[job_id].running_time;
        
        int size =jobs[job_id].current_heap_element_group+job_group_size;
        int i =jobs[job_id].current_heap_element_group;
       
        while (i < size) {
            
          
           heap_location =  system.MallocFF(jobs[job_id].heap[i].heap_memory_units_allocated, job_id);
            
            if (heap_location == -1) {
                throw invalid_argument("Memory Allocation System ran out of memory!");
            }
            else{
                jobs[job_id].heap[i].heap_location = heap_location;
            }
            
            log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Heap Element ID: "<<i<< " Memory Units Allocated: "<<jobs[job_id].heap[i].heap_memory_units_allocated << endl;
            
            i++;
        }
            // add to active jobs list
            active_jobs.push_back(job_id);
            // add active heap elements
            for (int j = jobs[job_id].current_heap_element_group; j <size ; j++) {
                heap_elements x;
                x.job_id = job_id;
                x.element_id= j;
                active_heap_jobs.push_back(x);
            }
            
            jobs[job_id].current_heap_element_group = i;
            
            
      } catch (invalid_argument & message) {
                
          // deallocate (unit of work concept), then throw again to main
          if (jobs[job_id].stack_location != -1) {
              system.freeFF(jobs[job_id].stack_location, jobs[job_id].stack_memory_units_allocated);
               log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Stack Memory Units Deallocated: "<<jobs[job_id].stack_memory_units_allocated<< endl;
          }
          if (jobs[job_id].code_location != -1) {
              system.freeFF(jobs[job_id].code_location, jobs[job_id].code_memory_units_allocated);
               log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Code Memory Units Deallocated:  "<<jobs[job_id].code_memory_units_allocated<< endl;
          }
          
          int job_group_size = int(jobs[job_id].heap.size())/jobs[job_id].running_time;
          int size =jobs[job_id].current_heap_element_group+job_group_size;
          
          for (int i =jobs[job_id].current_heap_element_group; i < size; i++) {
              if (jobs[job_id].heap[i].heap_location != -1) {
                  system.freeFF(jobs[job_id].heap[i].heap_location, jobs[job_id].heap[i].heap_memory_units_allocated);
                  log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Heap Element ID: "<<i<< " Memory Units Deallocated: "<<jobs[job_id].heap[i].heap_memory_units_allocated << endl;
              }
          }
          
          
          throw invalid_argument("The simulation has ended!");
          
        }
        
    }
    void deallocate_heap(const int& job_id,const int &heap_element_id, MemoryAllocationSystem &system, const int &current_time_unit){
        
        system.freeFF(jobs[job_id].heap[heap_element_id].heap_location, jobs[job_id].heap[heap_element_id].heap_memory_units_allocated);
        log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Heap Element ID: "<<heap_element_id<< " Memory Units Deallocated: "<<jobs[job_id].heap[heap_element_id].heap_memory_units_allocated << endl;
        
        
    }
    void deallocate_job(const int& job_id,  MemoryAllocationSystem &system, const int &current_time_unit){
        
        
        system.freeFF(jobs[job_id].stack_location, jobs[job_id].stack_memory_units_allocated);
        
         log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Stack Memory Units Deallocated: "<<jobs[job_id].stack_memory_units_allocated<< endl;
        
         system.freeFF(jobs[job_id].code_location, jobs[job_id].code_memory_units_allocated);
        
         log<< "Time unit: "<< current_time_unit<<" Job ID: "<< job_id<< " Code Memory Units Deallocated:  "<<jobs[job_id].code_memory_units_allocated<< endl;
        
    }
    bool check_heap_deallocation(const int &job_id, const int&heap_element_id, const int& current_time){
        
        return  jobs[job_id].heap[heap_element_id].arrival_time+jobs[job_id].heap[heap_element_id].life_time == current_time+1;
    }
    bool check_job_deallocation(const int &job_id, const int& current_time){
        
        return jobs[job_id].job_arrival_time +jobs[job_id].running_time == current_time+1;
    }
    
    pair<int, int> retrieve_stack_allocated(const int &job_id){
        
        return make_pair(jobs[job_id].stack_size, jobs[job_id].stack_memory_units_allocated);
    }
    pair<int, int> retrieve_code_allocated(const int &job_id){
           
           return make_pair(jobs[job_id].code_size, jobs[job_id].code_memory_units_allocated);
       }
    pair<int, int> retrieve_heap_element_allocated(const int &job_id, const int &heap_element_id){
              
        return make_pair(jobs[job_id].heap[heap_element_id].allocation, jobs[job_id].heap[heap_element_id].heap_memory_units_allocated);
    }
    job_type get_job_type(int job_id){
        
        return jobs[job_id].type;
    }
    
	// Statistics helper methods
	int retrieve_allocated_memory(const int &job_id, const int &heap_element_id) {

		int total_memory = 0;

		total_memory += jobs[job_id].code_memory_units_allocated;
		total_memory += jobs[job_id].stack_memory_units_allocated;
		total_memory += jobs[job_id].heap[heap_element_id].allocation;
		
		return total_memory;
	}

	int retrieve_required_memory(const int &job_id, const int &heap_element_id) {

		int total_memory = 0;

		total_memory += jobs[job_id].code_size;
		total_memory += jobs[job_id].stack_size;
		total_memory += jobs[job_id].heap[heap_element_id].allocation;

		return total_memory;
	}



    ~PCB(){
        log.close();
        
    }
};


#endif /* PCB_h */
