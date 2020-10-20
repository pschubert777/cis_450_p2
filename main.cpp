//
//  main.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/20/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
using namespace  std;

enum job_sizes {small =0, medium =1, large = 2};

struct job{
    int job_id;
    int job_arrival_time;
};

class PCB{
private:
    int total_running_time;
    int total_jobs;
    int num_small_jobs;
    int num_medium_jobs;
    int num_large_jobs;
    
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
    void job_assignments(){
        
        int i =0, tmp_small=num_small_jobs, tmp_medium=num_medium_jobs, tmp_large=num_large_jobs, arrival_time =0;
        // lower and upper seed
        int current_arrival_lower_seed = 2,currrent_arrival_upper_seed = 5;
        job_sizes j;
        
        while (i <total_jobs) {
            // calculate the arrival time
            arrival_time = calculate_arrival_time(current_arrival_lower_seed, currrent_arrival_upper_seed);
            j = assign_job_type(tmp_small, tmp_medium, tmp_large);
            
            i++;
        }
        
        
    }
    
    job_sizes assign_job_type(int& tmp_small, int& tmp_medium, int& tmp_large){
        job_sizes tmp_val;
        
        // select the job type
        if (tmp_small >0 && tmp_medium>0 && tmp_large>0) { tmp_val =job_sizes(rand()%3); }
        else if (tmp_small >0 && tmp_medium>0){tmp_val = job_sizes(rand()%2); }
        else if (tmp_small >0 && tmp_large>0){ tmp_val = (rand()%2==0)? small: large ;}
        else if (tmp_medium >0 && tmp_large>0){ tmp_val = job_sizes(rand()%2+1);}
        else if (tmp_small >0){ tmp_val = small; }
        else if (tmp_medium>0){ tmp_val = medium;}
        else { tmp_val = large;}
        
        // subtract the number of available job types. Will update due to pass by reference
        
        if (tmp_val== large) { tmp_large-=1; }
        else if (tmp_val == medium){ tmp_medium-=1;}
        else{ tmp_large-=1; }
        
        return tmp_val;
    }
    
    int calculate_arrival_time(int &current_arrival_lower_seed, int &current_arrival_upper_seed){
        
       int arrival_result=rand()%current_arrival_lower_seed + current_arrival_upper_seed;
        
       current_arrival_upper_seed+=3;
       current_arrival_lower_seed+=3;
        
        return arrival_result;
        
    }
    
    int calculate_run_time(){
        
        return 0;
    }
    
    
    
};

int main() {
    
    
    

    return 0;
}
