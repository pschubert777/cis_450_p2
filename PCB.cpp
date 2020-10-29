//
//  PCB.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/24/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#include "PCB.h"
#include <time.h>



PCB:: PCB(const double &small_job_distribution, const double &medium_job_distribution, const double &large_job_distribution, const int &total_run_time){
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
    
    
    // in the case that total jobs is more than  the jobs combined 
    total_jobs = num_medium_jobs+num_small_jobs+num_large_jobs;
    
}
void PCB:: job_assignments(vector<job> &queue){
    
    int i =0, tmp_small=num_small_jobs, tmp_medium=num_medium_jobs, tmp_large=num_large_jobs;
    // lower and upper seed
    int range_span = 5,initial_value_range = 1;
    
    while (i <total_jobs) {
        job_details new_job;
        job new_job_for_queue;
        
        //assign job id and job type
        new_job.job_id=i;
        new_job.type = assign_job_type(tmp_small, tmp_medium, tmp_large);
        
        
         // calculate the arrival time
        new_job_for_queue.job_id =i;
        new_job_for_queue.job_arrival_time = calculate_arrival_time(range_span, initial_value_range);
        
        
       
        new_job.running_time = calculate_run_time(new_job.type);
        //**calculate code size method should go here**
        new_job.code_size  = calculate_code_size(new_job.type);
        //**calculate stack size method should go here**
        new_job.stack_size= calculate_stack_size(new_job.type);
        //**calculate heap elements should go here**
        calculate_num_heap_elements(new_job.type, new_job);
        calculate_heap_time(new_job, new_job_for_queue.job_arrival_time);
        

        
        jobs.push_back(new_job);
        queue.push_back(new_job_for_queue);
        i++;
    }
}



job_type PCB:: assign_job_type(int& tmp_small, int& tmp_medium, int& tmp_large){
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


int PCB:: calculate_arrival_time(const int &range_span, int &initial_value_range){
       
      int arrival_result=rand()%range_span+ initial_value_range;
       
       initial_value_range+=3;
       
       return arrival_result;
       
   }


int PCB:: calculate_run_time(const job_type& type){
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


int PCB:: calculate_code_size(const job_type &type){
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


int PCB:: calculate_stack_size(const job_type &type) {
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



void PCB:: calculate_num_heap_elements(const job_type &type, job_details &job_details) {
      
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
           job_details.heap.push_back(heap_element);
       }
      
   }

void  PCB:: calculate_heap_time(job_details& job_info, int job_arrival_time) {
	// seed the random numbers
	srand(time(0));
     
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

// get helper function for testing.
// delete after probably
void PCB::get_stack_size(vector<int>&run_time, vector<job_type>&job_type, vector<int>&stack_size) {
	for (int i = 0; i < jobs.size(); i++) {
		job_type.push_back(jobs[i].type);
		stack_size.push_back(jobs[i].stack_size);
	}
}

void PCB::get_heap_elements(vector<int>&run_time, vector<job_type>&job_type, vector<int>&num_heap_elements, vector<vector<heap_info>>&job_heap, vector<int>&running_time) {
	
	
	for (int i = 0; i < jobs.size(); i++) {
		job_type.push_back(jobs[i].type);
		running_time.push_back(jobs[i].running_time);
		num_heap_elements.push_back(jobs[i].heap.size());
		
		// index i of heap_element_sizes map to index i of heap_element_time.
		// will be in reverse order i beleive
		
		// these two will be of size heap.size() much greater than jobs.size()!!!
		// job heap will contain at index i, job[i]'s heap. The heap is a vector of heap_info structs with attributes allocation and arrival time.
		// for testing we can cycle through job_heap[i][j] and check values are withing bounds at j
		job_heap.push_back(jobs[i].heap);
			
		
	}
}


void PCB:: print_job_info() {
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
