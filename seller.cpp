#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "customer.h"

#include "seller.h"
#include "constants.h"

using namespace std;

vector<vector<string>> seller::seats;
mutex seller::mtx;

string seller::generate_rejected_str()
{
	return this->seller_name + " rejected " + to_string(this->rejected_customers) + " customers.\n";
}

string seller::generate_time_str()
{
	string time = "";
	if (bar::TIME >= 10) time = "0:" + to_string(bar::TIME);
	else time = "0:0" + to_string(bar::TIME);
	return time;
}

void seller::generate_customers(int N)
{
	// generate bunch of customers with random arrival time.
	for (int i = 0; i < N; i++)
	{
		customer temp;
		queue.push(temp);
	}
}

void seller::print_seats()
{
	for (const auto& row : seats)
	{
		for (const auto& s : row)
		{
			cout << s << " ";
		}
		cout << endl;
	}
}

// use for medium in class
//int generate_random_time()
//{
//	// will return 2, 3, or 4.
//	return rand() % 3 + 2;
//}
//
//use for low
//int generate_random_time()
//{
//	// will return 4, 5, 6 or 7.
//	return rand() % 4 + 4;
//}
