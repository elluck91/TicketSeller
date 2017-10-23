#include <iostream>
#include "customer.h"

using namespace std;

customer::customer()
{
	generate_arrival_time();
}

void customer::generate_arrival_time()
{
	arrival_time = rand() % 60;
}

bool operator<(const customer& c1, const customer& c2)
{
	return c1.arrival_time > c2.arrival_time;
}