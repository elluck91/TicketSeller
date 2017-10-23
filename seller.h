#pragma once
#include <queue>
#include "customer.h"
#include <mutex> 

using namespace std;


class seller
{
protected:
	int rejected_customers;
	int freeze_time;
	static mutex mtx;
	static vector<vector<string>> seats;
	priority_queue<customer, vector<customer>> queue;
	virtual string generate_customer_name() = 0; // make children class implement this
	virtual int generate_random_time() = 0; // make children implement this
	string seller_name;
public:
	virtual void serve_customer() = 0; // make children classes implement this
	void print_seats();
	void generate_customers(int N);
	string generate_time_str();
	string generate_rejected_str();
};