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
        int current_arrival_lower_seed = 2 ;
        int currrent_arrival_upper_seed = 5;
        
        while (i <total_jobs) {
            // calculate the arrival time
            arrival_time = calculate_arrival_time(current_arrival_lower_seed, currrent_arrival_upper_seed);
            
            if (tmp_small >0 && tmp_medium>0 && tmp_large>0) {
              
            }
            else if (tmp_small >0 && tmp_medium>0){
                
            }
            else if (tmp_small >0 && tmp_large>0){
                
            }
            else if (tmp_medium >0 && tmp_large>0){
                
            }
            else if (tmp_small >0){
                
            }
            else if (tmp_medium>0){
                
            }
            else if (tmp_large>0){
                
            }
            
            
        }
        
        
    }
    int calculate_arrival_time(int &current_arrival_lower_seed, int &current_arrival_upper_seed){
        
       int arrival_result=rand()%current_arrival_lower_seed + current_arrival_upper_seed;
        
       current_arrival_upper_seed+=3;
       current_arrival_lower_seed+=3;
        
        return arrival_result;
        
    }
    
    
    
};

int main() {
    
    
    

    return 0;
}
