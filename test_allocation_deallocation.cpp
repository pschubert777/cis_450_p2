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

TEST(test_1_firstFit){
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
     /*1st Job */
    cout << "Finished test" << endl;
    

    
}

TEST(test_2_firstFit){
    vector<job>queue;
    PCB test2(25, 50, 25, 26, 32, false, "test2.txt");
    MemoryAllocationSystem system (10000, 32, "firstFit");
    
    int job0=0, job1 =0, job2=0;
    
    test2.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    if ( test2.get_job_type(queue[0].job_id )== large) {
        job0 = 250;
    }
    else if (test2.get_job_type(queue[0].job_id )== medium){
        job0=100;
    }
    else{
        job0=50;
    }
    if ( test2.get_job_type(queue[1].job_id )== large) {
           job1 = 250;
       }
    else if (test2.get_job_type(queue[1].job_id )== medium){
           job1=100;
       }
    else{
           job1=50;
       }
    if ( test2.get_job_type(queue[2].job_id )== large) {
           job2 = 250;
       }
       else if (test2.get_job_type(queue[2].job_id )== medium){
           job2=100;
       }
       else{
           job2=50;
       }
   test2.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
   test2.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <job0; i++) {
        test2.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test2.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test2.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <job1; i++) {
    test2.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
   test2.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <job2; i++) {
            test2.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test2.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;
    
}

TEST(test_3_nextFit){
    vector<job>queue;
    PCB test3(100, 0, 0, 26, 32, false, "test3.txt");
    MemoryAllocationSystem system (200, 32, "nextFit");
    
    
    test3.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    test3.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
    
    test3.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <50; i++) {
        test3.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test3.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test3.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <50; i++) {
           test3.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
    test3.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <50; i++) {
            test3.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test3.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;
    

    
}

TEST(test_4_nextFit){
    vector<job>queue;
    PCB test4(25, 50, 25, 26, 32, false, "test4.txt");
    MemoryAllocationSystem system (10000, 32, "nextFit");
    
    int job0=0, job1 =0, job2=0;
    
    test4.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    if ( test4.get_job_type(queue[0].job_id )== large) {
        job0 = 250;
    }
    else if (test4.get_job_type(queue[0].job_id )== medium){
        job0=100;
    }
    else{
        job0=50;
    }
    if ( test4.get_job_type(queue[1].job_id )== large) {
           job1 = 250;
       }
    else if (test4.get_job_type(queue[1].job_id )== medium){
           job1=100;
       }
    else{
           job1=50;
       }
    if ( test4.get_job_type(queue[2].job_id )== large) {
           job2 = 250;
       }
       else if (test4.get_job_type(queue[2].job_id )== medium){
           job2=100;
       }
       else{
           job2=50;
       }
   test4.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
   test4.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <job0; i++) {
        test4.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test4.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test4.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <job1; i++) {
    test4.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
   test4.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <job2; i++) {
            test4.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test4.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;
    
}
TEST(test_5_bestFit){
    vector<job>queue;
    PCB test5(100, 0, 0, 26, 32, false, "test5.txt");
    MemoryAllocationSystem system (200, 32, "bestFit");
    
    
    test5.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    test5.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
    
    test5.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <50; i++) {
        test5.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test5.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test5.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <50; i++) {
           test5.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
    test5.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <50; i++) {
            test5.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test5.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;

}
TEST(test_6_bestFit){
    vector<job>queue;
    PCB test6(25, 50, 25, 26, 32, false, "test6.txt");
    MemoryAllocationSystem system (10000, 32, "bestFit");
    
    int job0=0, job1 =0, job2=0;
    
    test6.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    if ( test6.get_job_type(queue[0].job_id )== large) {
        job0 = 250;
    }
    else if (test6.get_job_type(queue[0].job_id )== medium){
        job0=100;
    }
    else{
        job0=50;
    }
    if ( test6.get_job_type(queue[1].job_id )== large) {
           job1 = 250;
       }
    else if (test6.get_job_type(queue[1].job_id )== medium){
           job1=100;
       }
    else{
           job1=50;
       }
    if (test6.get_job_type(queue[2].job_id )== large) {
           job2 = 250;
       }
       else if (test6.get_job_type(queue[2].job_id )== medium){
           job2=100;
       }
       else{
           job2=50;
       }
   test6.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
   test6.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <job0; i++) {
        test6.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test6.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
    test6.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <job1; i++) {
    test6.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
   test6.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <job2; i++) {
            test6.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test6.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;
    
}
TEST(test_7_worstFit){
    vector<job>queue;
    PCB test7(100, 0, 0, 26, 32, false, "test7.txt");
    MemoryAllocationSystem system (200, 32, "worstFit");
    
    
    test7.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    test7.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
    
    test7.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <50; i++) {
        test7.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test7.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
   test7.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <50; i++) {
           test7.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
    test7.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <50; i++) {
            test7.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
     test7.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;

}
TEST(test_8_worstFit){
    vector<job>queue;
    PCB test8(25, 50, 25, 26, 32, false, "test8.txt");
    MemoryAllocationSystem system (10000, 32, "worstFit");
    
    int job0=0, job1 =0, job2=0;
    
    test8.job_assignments(queue);
    
    sort(queue.begin(), queue.end(), compare);
    
    if ( test8.get_job_type(queue[0].job_id )== large) {
        job0 = 250;
    }
    else if (test8.get_job_type(queue[0].job_id )== medium){
        job0=100;
    }
    else{
        job0=50;
    }
    if ( test8.get_job_type(queue[1].job_id )== large) {
           job1 = 250;
       }
    else if (test8.get_job_type(queue[1].job_id )== medium){
           job1=100;
       }
    else{
           job1=50;
       }
    if (test8.get_job_type(queue[2].job_id )== large) {
           job2 = 250;
       }
       else if (test8.get_job_type(queue[2].job_id )== medium){
           job2=100;
       }
       else{
           job2=50;
       }
   test8.allocate_new_job(queue[0].job_id, system, queue[0].job_arrival_time);
   test8.allocate_new_job(queue[1].job_id, system, queue[1].job_arrival_time);
    /*1st Job */
    for (int i =0; i <job0; i++) {
        test8.deallocate_heap(queue[0].job_id, i, system, queue[0].job_arrival_time);
        
    }
    test8.deallocate_job(queue[0].job_id, system, queue[0].job_arrival_time+50);
     /*1st Job */
    
     test8.allocate_new_job(queue[2].job_id, system, queue[2].job_arrival_time);
    
     /*2nd Job */
    for (int i =0; i <job1; i++) {
     test8.deallocate_heap(queue[1].job_id, i, system, queue[1].job_arrival_time);
           
       }
    
    
    test8.deallocate_job(queue[1].job_id, system, queue[1].job_arrival_time+50);
     /*2nd Job */
    
     /*3rd Job */
    for (int i =0; i <job2; i++) {
             test8.deallocate_heap(queue[2].job_id, i, system, queue[2].job_arrival_time);
            
        }
     
     
      test8.deallocate_job(queue[2].job_id, system, queue[2].job_arrival_time+50);
     /*1st Job */
    cout << "Finished test" << endl;
    
}



TEST_MAIN();
