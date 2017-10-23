#include <iostream>
#include <string>
#include "seller.h"
#include "mid_seller.h"
#include "constants.h"

using namespace std;

mid_seller::mid_seller(string name)
{
	seller_name = name;
	freeze_time = 0;
	rejected_customers = 0;
	current_row = 4;
	customer_num = 0;
	seat = 0;

	if (seats.size() == 0)
	{
		seats.resize(10);
		for (auto &v : seats)
		{
			v.resize(10);
			fill(v.begin(), v.end(), "|--|");
		}
		// this should be done in every seller class
	}
}
void mid_seller::serve_customer()
{
	if (queue.empty())
		return;

	mtx.lock();
	cout << endl << seller_name << ":" << endl;;
	cout << "Time is " << generate_time_str() << endl;

	// check if we sold all the tickets
	if (seat >= 100)
	{
		cout << "Sorry, I don't have tickets left. Please, leave right now" << endl;
		queue.pop();
		rejected_customers++;
		mtx.unlock();
		return;
	}
	// if it is last minute
	if (bar::TIME == 58)
	{
		// get rid of all customers except one
		while (queue.size() > 1)
		{
	        cout << "\n\n\n*** CUTOMER ARRIVED TOO LATE ***\n\n\n";

			//cout << seller_name << " popping client" << endl;
			queue.pop();
			rejected_customers++;
		}
	}
	if (freeze_time != 0)
	{
		if (bar::TIME == 58)
		{
	        cout << "\n\n\n*** CUTOMER ARRIVED TOO LATE ***\n\n\n";
			queue.pop();
			rejected_customers++;
		}
		freeze_time--;
		if (freeze_time == 0)
		{
			cout << "The customer has just finished purchasing a ticket and left." << endl;
		}
		//cout  << seller_name << ":: still serving a customer" << endl;
		mtx.unlock();
		return;
	}
	// if arrival time of next customer is greater than current time
	if (queue.top().arrival_time > bar::TIME)
	{
		//cout << seller_name << ":: waiting for new customers" << endl;
		//cout << endl;
		mtx.unlock();
		return;
	}
	//cout << seller_name << ":: looking at the customer with arrival time" << queue.top().arrival_time << endl;
	// imitate a new customer
	cout << "Customer has just arrived." << endl;
	queue.pop();
	int process_time = generate_random_time();
	//cout << "process time is " << process_time << endl;
	//cout << seller_name << ":: It will take me " << process_time << " to serve this customer." << endl;

	// appoint seat
	//mtx.lock();
	while (seat < 100)
	{

		int row = mid_seller::current_row;
		int seat_num = seat % 10;
		if (seats[row][seat_num] == "|--|")// check if it is empty
		{
			cout << "I will sell you a ticket in " << (row+1)
				<< " row and seat number " << (seat_num+1) << endl;
			seats[row][seat_num] = generate_customer_name();
			seat++;
			break;
		}
        seat++;
		if (!(seat % 10))
		    get_next_row(current_row);
	}
	customer_num++;
	//mtx.unlock();
	freeze_time = process_time - 1;
	if(freeze_time == 0)
		cout << "The customer has just finished purchasing a ticket and left." << endl;
	mtx.unlock();

}
int mid_seller::generate_random_time()
{
	// will return 2 or 4.
	return rand() % 3 + 2;
}

string mid_seller::generate_customer_name()
{
    int sel_num;
    if (seller_name.compare("Medium-first") == 0)
        sel_num = 0;
    else if (seller_name.compare("Medium-second") == 0)
        sel_num = 1;
    else if (seller_name.compare("Medium-third") == 0)
        sel_num = 2;

	switch (sel_num) {
	    case 0:
	        if (customer_num >= 10) {
        		return "M0" + to_string(customer_num);
        	}
        	return "M00" + to_string(customer_num);
	        break;
	    case 1:
	        if (customer_num >= 10) {
        		return "M1" + to_string(customer_num);
        	}
        	return "M10" + to_string(customer_num);
	        break;
	    case 2:
	        if (customer_num >= 10) {
        		return "M2" + to_string(customer_num);
        	}
        	return "M20" + to_string(customer_num);
	        break;
	}
	//string temp = "";
	//temp+=seller_name[0];
	//cout << "TEMP IS " << temp << endl;

}

int mid_seller::get_next_row(int& row_num) {
    switch(row_num) {
        case 4:
            row_num = 5;
            break;
        case 5:
            row_num = 3;
            break;
        case 3:
            row_num = 6;
            break;
        case 6:
            row_num = 2;
            break;
        case 2:
            row_num = 7;
            break;
        case 7:
            row_num = 1;
            break;
        case 1:
            row_num = 8;
            break;
        case 8:
            row_num = 0;
            break;
        case 0:
            row_num = 9;
            break;
        default:
            break;
    }
}