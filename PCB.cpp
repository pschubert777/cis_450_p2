//
//  PCB.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/24/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#include "PCB.h"



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
        calculate_heap_time(new_job);
        

        
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
    else{ tmp_large-=1; }
    
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
              code_size = rand()%41+40;
           }
           else if (type==medium){
               code_size = rand()%61+60;
           }
           else{
                code_size = rand()%101+120;
           }
           
    return code_size;
}


int PCB:: calculate_stack_size(const job_type &type) {
    int stack_size = 0;

    if (type == large) {
        stack_size = rand() % 21 + 20;
    }
    else if (type == medium) {
        stack_size = rand() % 41 + 40;
    }
    else {
        stack_size = rand() % 61 + 60;
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
       for (int i = 0; i <= num_heap_elements; i++) { // should run for # of heap elements.
           heap_info heap_element;
           heap_element.allocation = rand() % 21 + 30;
           job_details.heap.push_back(heap_element);
       }
      
   }

void  PCB:: calculate_heap_time(job_details& job_info) {
      /* Notes:
          -heap elements lifetime = duration of heap element. From 1 to end of run time
          -lifetime randomly distibuted across heap elements
          -# of heap elements allocated evenly across run time. This is # heap elements / run time. e.g. 250 elements over 5 time units == 250 / 5 = 50 elements per time unit
      
          - how is this done?
          --randomly choose each duration per index of vector. Until # of that duration is 0
      */
      vector<int> duration; // will hold an index of each time unit within run time
      
      int jobs_per_time = 0;
      jobs_per_time = int(job_info.heap.size() / job_info.running_time);

      // doing in descending order to use .push_back function
      for (int i = job_info.running_time; i >= 0; i--) {
          duration.push_back(jobs_per_time); // allocates # heap elements per time unit. (time unit = index of duration)
      }
      // post: -The number of indexes should equal the run time. Each index should contain the numebr of heap elements per that time unit. Should be evenly distributed

      /* Notes:
      -randomly select an index from duration and assign that index to heap[i].arrival time.
      -then decrement the amount of the index of duration
      
      */
      int random_duration = 0;
      for (int j = 0; j < job_info.heap.size(); j++) {
          random_duration = int(rand() % 1 + duration.size()); // random number from range of 1 to number of indecies in duration == number of time units

          job_info.heap[j].arrival_time = random_duration;

          if (duration[random_duration] != 0) { // need to check if that index has been used (elements per time) times
              job_info.heap[j].arrival_time = random_duration;
          }
          else {
              while (random_duration == 0) { // random until we get a new duration that is not 0. Not very efficient.
                  random_duration = int(rand() % 1 + duration.size());
              }
              job_info.heap[j].arrival_time = random_duration;
          }
          duration[random_duration]--; // decrement one from the amount of elements that can have this duration length
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
