#include <iostream>
#include <time.h>
#include <queue>
#include <functional>
#include <thread>
#include <string>
#include <cstdlib>
#include <sstream>
#include "customer.h"
#include "seller.h"
#include "high_seller.h"
#include "mid_seller.h"
#include "constants.h"

using namespace std;


int main()
{
	string usr_input;
	int N;

	srand(time(0));
	cout << "Enter number of customers per seller: ";
	getline(cin, usr_input);
	istringstream(usr_input) >> N;

	// size of the sellers array depends on the num of currently implemented sellers
	// if currently have 4, enter 4; larger size will lead to segmentation faul
	seller* sellers[4];

	high_seller high_sel("High-first");
	mid_seller mid_sel1("Medium-first");
	mid_seller mid_sel2("Medium-second");
	mid_seller mid_sel3("Medium-third");

	sellers[0] = &high_sel;
	sellers[1] = &mid_sel1;
	sellers[2] = &mid_sel2;
	sellers[3] = &mid_sel3;

	for (const auto& sel : sellers)
	{
		// generate customers for every seller
		sel->generate_customers(N);
		//fucking neat, right?
	}

	while (bar::TIME <= 59)
	{
		for (const auto& sel : sellers)
		{
			thread thr(&seller::serve_customer, sel);
			thr.join();
		}
		bar::TIME++;
	}
	sellers[0]->print_seats();
	for (const auto& sel : sellers)
	{
		cout << sel->generate_rejected_str() << endl;
	}
}
