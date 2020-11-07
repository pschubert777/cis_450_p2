//
//  test_allocation_deallocation.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 11/7/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//

#include <stdio.h>
#include "PCB.h"
#include "unit_test_framework.h"


bool compare(const job & first, const job &second) {
        
        
        return first.job_arrival_time < second.job_arrival_time;
    }

TEST(test_1){
    vector<job>queue;
    PCB test1(100, 0, 0, 26, 32, false, "test1.txt");
    MemoryAllocationSystem system (10000, 32, "firstFit");
    
    
    test1.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    test1.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
    test1.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <50; i++) {
        test1.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test1.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test1.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <50; i++) {
           test1.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
    test1.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <50; i++) {
            test1.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test1.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*3rd Job */
    cout << "Finished test" << endl;
    
    
    
    
    
}











TEST_MAIN();
