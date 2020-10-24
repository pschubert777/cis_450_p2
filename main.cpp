//
//  main.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/20/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//
// testing that this worked
#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
using namespace  std;

enum job_type {small =0, medium =1, large = 2};

struct job{
    int job_id;
    int job_arrival_time;
};

struct heap_info {
    int allocation; // the amount of memory this element takes up
    int arrival_time; // time that this element will be processed
};

struct job_details {
	int job_id; // will grab id from job struct
	int running_time; // generate running time. Small == 5 +/- 1, Medium == 10 +/- 1, Large == 25 +/-1
	int code_size; // generate code size. Small == 60 +/- 20, Medium == 90 +/- 30, Large == 170 +/-50
	int stack_size; // generate stack size. Small == 30 +/- 10, Medium == 60 +/- 20, Large == 90 +/-30
	vector<heap_info> heap; // each index is a heap element holding heap specific info
    job_type type;
};



class PCB{
private:
    int total_running_time;
    int total_jobs;
    int num_small_jobs;
    int num_medium_jobs;
    int num_large_jobs;
    vector<job_details> jobs;
    
public:
    PCB(const double &small_job_distribution, const double &medium_job_distribution, const double &large_job_distribution, const int &total_run_time){
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
        
        
    };
    // Description: method for randomly assigning jobs
    // Pre-condition: a valid vector of type job struct
    // Post-condition: creats new jobs with unique id's and creats for each job a job struct (stored in queue) and job_details struct (stored in jobs struct private variable), and witin the job_details a vector of heap info to detail the allocation and arrival time of the heap elements
    // Author: Peter Schubert
    void job_assignments(vector<job> &queue){
        
        int i =0, tmp_small=num_small_jobs, tmp_medium=num_medium_jobs, tmp_large=num_large_jobs, arrival_time =0, run_time;
        // lower and upper seed
        int range_span = 5,initial_value_range = 1;
        job_type j;
        
        while (i <total_jobs) {
            job_details new_job;
            job new_job_for_queue;
            // calculate the arrival time
            arrival_time = calculate_arrival_time(range_span, initial_value_range);
            j = assign_job_type(tmp_small, tmp_medium, tmp_large);
            run_time = calculate_run_time(j);
            //**calculate stack size method should go here**
            
            
            //**calculate heap elements should go here**
            
            
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
        else{ tmp_large-=1; }
        
        return tmp_val;
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
    
	// Description: method for calculating stack size.
	// Pre-condition: What do input do you need for the function to work
	// Post-condition: What is the end result of the function or what do you get out of the function
	// Author: Nathan Carey
	int calculate_stack_size(const job_type &type) {
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


	// Description: method for calculating heap element information
	// Pre-condition: Needs a struct object of heap_info. Empty Struct object needs to be created beforehand!!!
	// Post-condition: return the number of heap elements for this job, assign values to job_heap object for allocation and arrival_time
	// Author: Nathan Carey
	int calculate_num_heap_elements(const job_type &type, job_details job_details, heap_info heap_element) {
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
			heap_element.allocation = rand() % 21 + 30;
			job_details.heap.push_back(heap_element);
		}

	}

	// Description: method for calculating heap element information
	// Pre-condition: needs a job_details object to already have its vector of heap_info created
	// Post-condition: assigns jobs heap elements arrival times.
	// Author: Nathan Carey
	void calculate_heap_time(job_details job_info) {
		/* Notes:
			-heap elements lifetime = duration of heap element. From 1 to end of run time
			-lifetime randomly distibuted across heap elements
			-# of heap elements allocated evenly across run time. This is # heap elements / run time. e.g. 250 elements over 5 time units == 250 / 5 = 50 elements per time unit
		
			- how is this done?
			--randomly choose each duration per index of vector. Until # of that duration is 0
		*/
		vector<int> duration; // will hold an index of each time unit within run time
		
		int jobs_per_time = 0;
		jobs_per_time = job_info.heap.size() / job_info.running_time;

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
			random_duration = rand() % 1 + duration.size(); // random number from range of 1 to number of indecies in duration == number of time units

			job_info.heap[j].arrival_time = random_duration;

			if (duration[random_duration] != 0) { // need to check if that index has been used (elements per time) times
				job_info.heap[j].arrival_time = random_duration;
			}
			else {
				while (random_duration == 0) { // random until we get a new duration that is not 0. Not very efficient.
					random_duration = rand() % 1 + duration.size();
				}
				job_info.heap[j].arrival_time = random_duration;
			}
			duration[random_duration]--; // decrement one from the amount of elements that can have this duration length
		}

		return;
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
			jobs_per_time = jobs[i].heap.size() / jobs[i].running_time;

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
};

int main() {
    
    
    

    return 0;
}
