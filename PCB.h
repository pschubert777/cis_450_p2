//
//  PCB.h
//  cis_450_p2
//
//  Created by Peter Schubert on 10/24/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#ifndef PCB_h
#define PCB_h
#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
enum job_type {small =0, medium =1, large = 2};

struct job{
    int job_id;
    int job_arrival_time;
};

struct heap_info {
    int allocation; // the amount of memory this element takes up
    int arrival_time; // time that this element will be processed
	int life_time; // the length of a heap elements life
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
    PCB(const double &small_job_distribution, const double &medium_job_distribution, const double &large_job_distribution, const int &total_run_time);
    // Description: method for randomly assigning jobs
    // Pre-condition: a valid vector of type job struct
    // Post-condition: creats new jobs with unique id's and creats for each job a job struct (stored in queue) and job_details struct (stored in jobs struct private variable), and witin the job_details a vector of heap info to detail the allocation and arrival time of the heap elements
    // Author: Peter Schubert
    void job_assignments(vector<job> &queue);

    // Description: method for  aassigning job types
    // Pre-condition: the number of remaining small, medium, and large jobs
    // Post-condition: a randomly assign job type and return the type that was selected based on the number (distribution of each type remaning)
    // Author: Peter Schubert
    job_type assign_job_type(int& tmp_small, int& tmp_medium, int& tmp_large);
    
    // Description: method for calculating  the arrival time of a job
    // Pre-condition: range span, initial value range
    // Post-condition: returns the arrival time result, based on an inital range of time units 1-5, and increment by 3
    // Author: Peter Schubert
    int calculate_arrival_time(const int &range_span, int &initial_value_range);
    
    // Description: method for calculating run time
    // Pre-condition: a valid job type
    // Post-condition: returns a randomly assigned run time for a job based on the job type
    // Author: Peter Schubert
    int calculate_run_time(const job_type& type);
    // Description: method for calculating code size
    // Pre-condition: a valid job type
    // Post-condition: returns the code size of the job based on the job type
    // Author: Peter Schubert
    int calculate_code_size(const job_type &type);
    
    // Description: method for calculating stack size.
    // Pre-condition: What do input do you need for the function to work
    // Post-condition: What is the end result of the function or what do you get out of the function
    // Author: Nathan Carey
    int calculate_stack_size(const job_type &type);


    // Description: method for calculating heap element information
    // Pre-condition: Needs a struct object of heap_info. Empty Struct object needs to be created beforehand!!!
    // Post-condition: return the number of heap elements for this job, assign values to job_heap object for allocation and arrival_time
    // Author: Nathan Carey
    void calculate_num_heap_elements(const job_type &type, job_details &job_details);

    // Description: method for calculating heap element information
    // Pre-condition: needs a job_details object to already have its vector of heap_info created
    // Post-condition: assigns jobs heap elements arrival times.
    // Author: Nathan Carey
    void calculate_heap_time(job_details& job_info, int job_arrival_time);


	// helper function for testing
	void get_stack_size(vector<int>&run_time, vector<job_type>&job_type, vector<int>&stack_size);

	// helper function for testing
	// get number of heap elements and size of each element
	void get_heap_elements(vector<int>&run_time, vector<job_type>&job_type, vector<int>&num_heap_elements, vector<vector<heap_info>>&job_heap, vector<int>&running_time);

    // Description: method for printing out job information to file
    // Pre-condition: What do input do you need for the function to work
    // Post-condition: What is the end result of the function or what do you get out of the function
    // Author: Nathan Carey
    void print_job_info();
};









#endif /* PCB_h */
