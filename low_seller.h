#pragma once
#include "seller.h"

class low_seller : public seller
{
private:
	// i used this variable to signify the number of seats i have tried.
	// so for example i have sold 10 seats. Then i keep trying to find a new seat 
	// and i can't. customer_num will be still 10.
	// while seat would be increased to 100.
	// look into 
	static int seat;
	// customer_num is a real number of customers served,
	int customer_num;
	// i used it to generate the name of the seat.(look into generate customer name)
	string generate_customer_name();
	int generate_random_time();
	string get_sel_num();
public:
	void serve_customer();
	low_seller(string name);
};
