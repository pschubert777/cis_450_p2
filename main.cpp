//
//  main.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/20/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//  Copyright © 2020 Nathan Carey. All rights reserved.
//
// testing that this worked

#include "PCB.h"


vector<double> request_job_distribtution() {
	vector<double> job_distro;
	double small = 0, medium = 0, large = 0, sum = 0;
	bool valid_input = false;
	while (!valid_input) {
		cout << "Please enter the job distribution for the simulation (small, medium, large)." << endl;
		cout << "Small = ";
		cin >> small;
		cout << endl << "Medium = ";
		cin >> medium;
		cout << endl << "Large = ";
		cin >> large;
		if (small + medium + large != 100) {
			cout << "ERROR. The distribution did not total 100%!" << endl;
			cout << "Please re-enter your values." << endl;
		}
		else {
			valid_input = true;
		}
	}

	// small == index 0, medium == index 1, large == index 2
	job_distro.push_back(small);
	job_distro.push_back(medium);
	job_distro.push_back(large);

	return job_distro;
}


int request_sim_duration(const vector<double> job_distro) {
	double duration = 0, num_jobs = 0;
	int num_small = 0, num_medium = 0, num_large = 0, return_duration = 0;
	cout << "Please enter the duration of the simulation: ";
	cin >> duration;

	// check that duration is valid
	while (duration <= 0) {
		cout << "ERROR. The duration of the simulation must be greater than 0. Please enter a new distribution." << endl;
		cin >> duration;
	}
	num_jobs = duration / 3;


	num_small = (num_jobs * (job_distro[0] / 100));
	num_medium = (num_jobs * (job_distro[1] / 100));
	num_medium = (num_jobs * (job_distro[2] / 100));

	while (num_small % 1 != 0 && num_medium % 1 != 0 && num_large % 1 != 0) {
		cout << "The distribution did not result whole values for the amount of jobs. Please enter a new distribution: ";
		cin >> duration;
		// check that duration is valid
		while (duration <= 0) {
			cout << "ERROR. The duration of the simulation must be greater than 0. Please enter a new distribution." << endl;
			cin >> duration;
		}
		num_jobs = duration / 3;

		num_small = (num_jobs * (job_distro[0] / 100));
		num_medium = (num_jobs * (job_distro[1] / 100));
		num_medium = (num_jobs * (job_distro[2] / 100));
	}
	
	return_duration = duration;
	return return_duration;
}


int request_memory_unit_size() {
	int memory_unit_size = 0;

	cout << "Please enter the memory unit size that is a multiple of 8. e.g. 8, 16, 24, 32, 40, etc.. " << endl;
	cin >> memory_unit_size;

	while (memory_unit_size % 8 != 0) {

		cout << "ERROR. The memory unit size entered was not a multiple of 8. Please enter a valid memory unit size." << endl;
		cin >> memory_unit_size;
	}


	return memory_unit_size;
}


int request_memory_units_available() {
	int memory_units = 0;

	cout << "Please enter the amount of memory units available for this simulation. *must be greater than 0." << endl;
	cin >> memory_units;

	while (memory_units <= 0) {
		cout << "ERROR. The amount of memory units available must be greater than 0." << endl;
		cin >> memory_units;
	}

	return memory_units;
}


bool request_lost_objects() {
	bool is_lost_objects;
	string user_input;

	cout << "Would you like to simulate lost objects in this simulation? Enter yes or no" << endl;
	cin >> user_input;

	while (user_input != "yes" || user_input != "no") {
		cout << "ERROR. Please enter yes or no if you would like to simulate lost objects or not." << endl;
		cin >> user_input;
	}


	if (user_input == "yes") {
		is_lost_objects = true;
	}
	else if (user_input == "no") {
		is_lost_objects = false;
	}



	return is_lost_objects;
}

string request_algorithm() {
	string algo;

	cout << "Please enter the algorithm you would like to use for this simulation. Either firstfit, nextfit, bestfit, or worstfit" << endl;
	cin >> algo;

	while (algo != "firstfit" || algo != "nextfit" || algo != "bestfit" || algo != "worstfit") {
		cout << "ERROR. Please enter the name of one of the algorithms for this simulation. Either firstfit, nextfit, bestfit, or worstfit" << endl;
		cin >> algo;
	}
	return algo;
}

// sort here by arrival time


struct heap_elements {
	int job_id;
	int element_id;
};

int main() {
	// main variables
	double small = 0, medium = 0, large = 0, run_time;
	vector<job>queue;
	int time_counter;
	vector<int>active_jobs;
	vector<heap_elements>active_heap_elements;
	// variables to hold method vals
	vector<double>distribution; // small == index 0, medium == index 1, large == index 2
	int distribution = 0, duration = 0, memory_unit_size = 0, num_memory_units = 0;
	bool is_lost_objects;
	string algorithm_to_run;
	// variables for files
	string test_name;
	string log_file_name, output_file_name;
	ofstream log_file, output_file;


	cout << "Please enter the name of the simulation: ";
	cin >> test_name;

	cout << "Please enter the name of the log file for the simulation: ";
	cin >> log_file_name;

	log_file.open(log_file_name);

	cout << "Please enter the name of the output file for the simulation: ";
	cin >> output_file_name;

	output_file.open(output_file_name);


	distribution = request_job_distribtution();
	duration = request_sim_duration(distribution);
	memory_unit_size = request_memory_unit_size();
	num_memory_units = request_memory_units_available();
	is_lost_objects = request_lost_objects();
	algorithm_to_run = request_algorithm();
	
	small = distribution[0];
	medium = distribution[1];
	large = distribution[2];
	run_time = duration;


	PCB myPCB(small, medium, large, run_time, memory_unit_size, is_lost_objects);
	// queue holds jobs before sim begins
	myPCB.job_assignments(queue);

	// sort here -----------------
	// need to sort queue here. Have to add my compare function but waiting to talk to peter becaue I need to add it into PCB i beleive and dont want merge conflicts

	MemoryAllocationSystem myMAS(num_memory_units, memory_unit_size, algorithm_to_run);
	time_counter = 0;
	while (time_counter < duration) {
		try {
			// allocate new jobs
			for (int i = 0; i < active_jobs.size(); i++) {
				myPCB.allocate_and_return_heap_elements(active_jobs[i], myMAS, time_counter);
			}

			// 
			for (int j = 0; j < queue.size(); j++) {
				if (queue[j].job_arrival_time == time_counter) {
					myPCB.allocate_new_job(queue[j].job_id, myMAS, time_counter);
				}
				else if (queue[j].job_arrival_time > time_counter) {
					break;
				}
			}
		}
		catch (invalid_argument) {
			// log/ print something here
			cout << "Error thrown, system ran out of memory. Ending simulation." << endl;
			break;
		}
		

		// !!
		// if running for 2000 time units print stats
		// !!

		for (int i = 0; i < active_heap_elements.size(); i++) {
			if (myPCB.check_heap_deallocation(active_heap_elements[i].job_id, active_heap_elements[i].element_id, time_counter)) {
				myPCB.deallocate_heap(active_heap_elements[i].job_id, active_heap_elements[i].element_id, myMAS, time_counter);
			}
		}

		for (int i = 0; i < active_jobs.size(); i++) {
			if (myPCB.check_job_deallocation(active_jobs[i], myMAS, time_counter)) {
				myPCB.deallocate_job(active_jobs[i], myMAS, time_counter);
			}
		}

	}

	// print final statistics!!


	return 0;
}
