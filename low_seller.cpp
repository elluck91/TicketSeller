#include <iostream>
#include <string>
#include "seller.h"
#include "low_seller.h"
#include "constants.h"

using namespace std;

int low_seller::seat = 0;
low_seller::low_seller(string name)
{
	seller_name = name;
	freeze_time = 0;
	rejected_customers = 0;
	seat = 0;
        customer_num = 1;

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
void low_seller::serve_customer()
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
	if (bar::TIME == 59)
	{
		// get rid of all customers except one
		while (queue.size() > 1)
		{
			//cout << seller_name << " popping client" << endl;
			queue.pop();
			rejected_customers++;
		}
	}
	if (freeze_time != 0)
	{
		if (bar::TIME == 59)
		{
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
		int row = (99 - seat) / 10;
		int seat_num = seat % 10;
		if (seats[row][seat_num] == "|--|")// check if it is empty
		{
			cout << "I will sell you a ticket in " << row
				<< " row and seat number " << seat_num << endl;
			seats[row][seat_num] = generate_customer_name();
			seat++;
			break;
		}
		seat++;
	}
	customer_num++;
	//mtx.unlock();
	freeze_time = process_time - 1;
	if(freeze_time == 0)
		cout << "The customer has just finished purchasing a ticket and left." << endl;
	mtx.unlock();

}
int low_seller::generate_random_time()
{
	// will return 4, 5, 6, 7.
	return rand() % 4 + 4;
}

string low_seller::generate_customer_name()
{
	//string temp = "";
	//temp+=seller_name[0];
	//cout << "TEMP IS " << temp << endl;
	if (customer_num >= 10)
	{
		return get_sel_num() + to_string(customer_num);
	}
	return get_sel_num() + "0" + to_string(customer_num);
}

string low_seller::get_sel_num()
{
	if(seller_name.compare("Low-first") == 0)
	{
		return "L0";
	}
	if(seller_name.compare("Low-second") == 0)
	{
		return "L1";
	}
	if(seller_name.compare("Low-third") == 0)
	{
		return "L2";
	}
	if(seller_name.compare("Low-fourth") == 0)
	{
		return "L3";
	}
	if(seller_name.compare("Low-fifth") == 0)
	{
		return "L4";
	}
	if(seller_name.compare("Low-sixth") == 0)
	{
		return "L5";
	}
}
