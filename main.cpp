//
//  main.cpp
//  cis_450_p2
//
//  Created by Peter Schubert on 10/20/20.
//  Copyright © 2020 Peter Schubert. All rights reserved.
//
// testing that this worked

#include "PCB.h"


vector<int> request_job_distribtution() {
	vector<int> job_distro;
	int small = 0, medium = 0, large = 0, sum = 0;
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
	job_distro.push_back(large);
	job_distro.push_back(medium);
	job_distro.push_back(small);

	return job_distro;
}


int request_sim_duration(const vector<int> job_distro) {
	int duration = 0, num_jobs = 0;
	int num_small = 0, num_medium = 0, num_large = 0;
	cout << "Please enter the duration of the simulation: ";
	cin >> duration;

	// check that duration is valid
	while (duration <= 0) {
		cout << "ERROR. The duration of the simulation must be greater than 0. Please enter a new distribution." << endl;
		cin >> duration;
	}
	num_jobs = duration / 3;

	num_small = round(num_jobs * (job_distro[0] / 100));
	num_medium = round(num_jobs * (job_distro[1] / 100));
	num_medium = round(num_jobs * (job_distro[2] / 100));

	// chack that the number of each type of job is a whole number.

	return duration;
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



int main() {

	int small = 0, medium = 0, large = 0, run_time;
	vector<job>queue;

	do {
		cout << "Please enter a small job distribution" << endl;
		cin >> small;
		cout << "Please enter a medium job distribution" << endl;
		cin >> medium;

		cout << "Please enter a large job distribution" << endl;
		cin >> large;

	} while (small + medium + large != 100);

	cout << "How long should the program run?" << endl;
	cin >> run_time;




	PCB myval(small, medium, large, run_time);
	myval.job_assignments(queue);



	return 0;
}
