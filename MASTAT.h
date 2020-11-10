//
//  PCB.h
//  cis_450_p2
//
//  Created by Nathan Carey on 11/07/20.
//  Copyright � 2020 Nathan Carey. All rights reserved.
//

#ifndef MSTAT_h
#define MSTAT_h

#include <string>
#include "PCB.h"
//#include "MAS.h"

using namespace std;

/*
struct stats_heap_elements {
	int job_id;
	int heap_element_id;
};
*/

class MASTAT {
private:
	int succesful_heap_allocations;
	int total_memory_lost;
	bool lost_object_sim;
	string test_name, algorithm;
	int memory_defined, number_memory_units, num_small_jobs, num_medium_jobs, num_large_jobs, mem_unit_size;

	ofstream output;

public:
	MASTAT(bool lost_object, string sim_name, string algorithm_type, int total_memory_defined, int total_number_memory_units, int small_jobs, int medium_jobs, int large_jobs, const string &output_file, const int &memory_unit_size) {
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
		//
		mem_unit_size = memory_unit_size;

		output.open(output_file);
	}

	
	// Description: method to get the total amound of memory allocated
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int memory_allocated(PCB &pcb, vector<int> &active_jobs, vector<heap_elements> &heap_elements) {
		int allocated_memory = 0;

		for (int i = 0; i < active_jobs.size(); i++) {
			allocated_memory += pcb.retrieve_allocated_memory(active_jobs[i], mem_unit_size);
		}
		for (int j = 0; j < heap_elements.size(); j++) {
			allocated_memory += pcb.retrieve_allocated_heap_memory(heap_elements[j].job_id, heap_elements[j].element_id, mem_unit_size);
		}

		return allocated_memory;
	}

	// Description: method to get the current memory in use
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements, total simulation memory
	// Post-condition: sum of the amount of all memory currently in use
	// Author: Nathan Carey
	double memory_in_use(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {
		double used_memory = 0;
		double allocated_memory = 0;

		allocated_memory = memory_allocated(pcb, active_jobs, heap_elements);
		used_memory = allocated_memory / memory_defined;

		return used_memory * 100;
	}

	// Description: method to get the amount of required memory based on the list of active jobs and active heap elements
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all required memory
	// Author: Nathan Carey
	int required_memory(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {
		int required_memory = 0;

		for (int i = 0; i < active_jobs.size(); i++) {
			required_memory += pcb.retrieve_required_memory(active_jobs[i], heap_elements[i].element_id);
		}
		for (int j = 0; j < heap_elements.size(); j++) {
			required_memory += pcb.retrieve_allocated_heap_memory(heap_elements[j].job_id, heap_elements[j].element_id, mem_unit_size);
		}

		return required_memory;

	}

	// Description: method to get the percentage of internal fragmentation currently in the simulation
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements, total simulation memory
	// Post-condition: percentage of internal fragmentation
	// Author: Nathan Carey
	double percent_internal_fragmentaion(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements) {
		double allocated_memory = 0, req_memory = 0;
		double internal_fragmentation = 0;

		allocated_memory = memory_allocated(pcb, active_jobs, heap_elements);
		if (allocated_memory > 0) {
			//memory_use = memory_in_use(pcb, active_jobs, heap_elements);
			req_memory = required_memory(pcb, active_jobs, heap_elements);

			internal_fragmentation = allocated_memory - req_memory;
			internal_fragmentation = internal_fragmentation / allocated_memory;
		}
		else {
			internal_fragmentation = 0;
		}

		// return as percentage
		return internal_fragmentation * 100;
	}


	// Description: method to get the amount of memory currently free in the simulation
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements, total amount of simulation memory
	// Post-condition: the amount of free memory in the simulation
	// Author: Nathan Carey
	double amount_memory_free(PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements, MemoryAllocationSystem &mas) {
		double free_memory = 0, allocated = 0;

		allocated = memory_allocated(pcb, active_jobs, heap_elements);
		if (allocated > 0) {
			free_memory = memory_defined - allocated;
			free_memory = free_memory / memory_defined;
		}
		else {
			free_memory = 0;
		}
	
		// return as percentage
		return free_memory * 100;
	}

	// Description: use MAS method to get size of memory locations depending on algorithm type
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int external_fragmentation(MemoryAllocationSystem &mas, string &algorithm_type) {
		int ext_frag = 0;

		ext_frag = mas.calculate_external_fragmentation(algorithm_type);
		
		return ext_frag;
	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int largest_free_space(MemoryAllocationSystem &mas, string &algorithm_type) {
		int largest_space = 0;

		largest_space = mas.find_largest_free_space(algorithm_type);

		return largest_space;
	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int smallest_free_space(MemoryAllocationSystem &mas, string &algorithm_type) {
		int smallest_space = 0;

		smallest_space = mas.find_smallest_free_space(algorithm_type);

		return smallest_space;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int retrieve_heap_allocations(int number_succesful_heap_allocations) {
		succesful_heap_allocations += number_succesful_heap_allocations;
		return number_succesful_heap_allocations;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int retrieve_number_size_lost_objects(vector<heap_elements> &heap_elements, PCB &pcb, int current_time) {


        return 0;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int percent_memory_lost_objects(int total_memory_lost, int memory_defined) {


        return 0;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_allocations(MemoryAllocationSystem &mas) {


        return 0;
	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_allocation_operations(MemoryAllocationSystem &mas) {


        return 0;

	}



	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int average_number_allocation_operations(MemoryAllocationSystem &mas) {



        return 0;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_free_requests(MemoryAllocationSystem &mas) {


        return 0;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int number_free_operations(MemoryAllocationSystem &mas) {


        return 0;
	}

	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int avg_number_free_operations(MemoryAllocationSystem &mas) {



        return 0;
	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int average_free_space(MemoryAllocationSystem &mas) {


        return 0;
	}


	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
    /*
	vector<int> simulation_internal_fragmentation(PCB &pcb, vector<int> active_jobs, vector<heap_elements> heap_elements) {


        return 0;
	}

*/
	// Description: 
	// Pre-condition: PCB parameter, list of active jobs, list of heap elements
	// Post-condition: sum of the amount of all memory allocated
	// Author: Nathan Carey
	int allocation_threshold(PCB &pcb, vector<int> active_jobs) {

        return 0; 
	}


	void print_statistics(const int &time, PCB &pcb, vector<int> active_jobs, vector<heap_elements> &heap_elements, MemoryAllocationSystem &mas, string algorithm, const int &heap_allocations, const int &current_time) {
        
		int mem_allocated = 0, req_mem = 0, external_frag = 0, largest_free = 0, smallest_free = 0;
		double mem_use = 0, internal_frag = 0, free_mem = 0;

		mem_allocated = memory_allocated(pcb, active_jobs, heap_elements);
		mem_use = memory_in_use(pcb, active_jobs, heap_elements);
		req_mem = required_memory(pcb, active_jobs, heap_elements);
		internal_frag = percent_internal_fragmentaion(pcb, active_jobs, heap_elements);
		free_mem = amount_memory_free(pcb, active_jobs, heap_elements, mas);
		external_frag = external_fragmentation(mas, algorithm);
		largest_free = largest_free_space(mas, algorithm);
		smallest_free = smallest_free_space(mas, algorithm);
		retrieve_heap_allocations(heap_allocations);
		// use successful_heap_allocations to print this

		output << "Time Unit: " << current_time << " | Interum Statistics During Simulation ----------------------------" << endl;
		output << "Total amount of memory defined: " << memory_defined << endl;
		output << "amount of memory allocated: " << mem_allocated << endl;
		output << "% memory in use: " << mem_use << endl;
		output << "required amount of memory: " << req_mem << endl;
		output << "% internal fragmentation: " << internal_frag << endl;
		output << "% memory free: " << free_mem << endl;
		output << "external fragmentation: " << external_frag << endl;
		output << "largest free space: " << largest_free << endl;
		output << "smallest free space: " << smallest_free << endl;
		output << "number of heap allocation: " << heap_allocations << endl << endl;
	}


	void close_output() {
		output.close();
	}

};

#endif /* MSTAT_h */
