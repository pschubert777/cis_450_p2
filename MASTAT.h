//
//  PCB.h
//  cis_450_p2
//
//  Created by Nathan Carey on 11/07/20.
//  Copyright © 2020 Nathan Carey. All rights reserved.
//

#ifndef MSTAT_h
#define MSTAT_h

#include <string>
#include "PCB.h"
#include "MAS.h"

using namespace std;

struct heap_elements {
	int job_id;
	int heap_element_id;
};

class MASTAT {
private:
	int number_heap_allocations;
	int total_memory_lost;
	bool lost_object_sim;
	string test_name, algorithm;
	int memory_defined, number_memory_units, num_small_jobs, num_medium_jobs, num_large_jobs;

public:
	MASTAT(bool lost_object, string sim_name, string algorithm_type, int total_memory_defined, int total_number_memory_units, int small_jobs, int medium_jobs, int large_jobs) {
		// are we simulating lost objects
		lost_object_sim = lost_object;
		// the name of the simulation
		test_name = sim_name;
		// the algorithm used
		algorithm = algorithm_type;
		// amount of memory defined
		memory_defined = total_memory_defined;
		// amound of memory units for this simulation
		number_memory_units = total_number_memory_units;
		// number of small jobs
		num_small_jobs = small_jobs;
		// number of medium jobs
		num_medium_jobs = medium_jobs;
		// number of large jobs
		num_large_jobs = large_jobs;
	}

	
	// Description: method to get the total amound of memory allocated
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int memory_allocated(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {
		int sum_memory;





		return;
	}

	// Description: method to get the current memory in use
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int memory_in_user(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {




		return;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int required_memory(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	void percent_internal_fragmentaion(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {




	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int amount_memory_free(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements, MemoryAllocationSystem &mas) {




	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int external_fragmentation(MemoryAllocationSystem &mas) {




	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int largest_free_space(MemoryAllocationSystem &mas) {



	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int smallest_free_space(MemoryAllocationSystem &mas) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int retrieve_heap_allocations(int number_succesful_heap_allocations) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int retrieve_number_size_lost_objects(vector<heap_elements> &heap_elements, PCB &pcb, int current_time) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int percent_memory_lost_objects(int total_memory_lost, int memory_defined) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_allocations(MemoryAllocationSystem &mas) {



	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_allocation_operations(MemoryAllocationSystem &mas) {




	}



	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int average_number_allocation_operations(MemoryAllocationSystem &mas) {




	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_free_requests(MemoryAllocationSystem &mas) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_free_operations(MemoryAllocationSystem &mas) {



	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int avg_number_free_operations(MemoryAllocationSystem &mas) {




	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int average_free_space(MemoryAllocationSystem &mas) {



	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	vector<int> simulation_internal_fragmentation(PCB &pcb, vector<int> active_jobs, vector<heap_elements> heap_elements) {



	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int allocation_threshold(PCB &pcb, vector<int> active_jobs) {


	}


};

#endif /* MSTAT_h */
