#pragma once
class customer
{
public:
	int arrival_time;
	friend bool operator< (const customer &c1, const customer &c2);
	customer();
private:
	void generate_arrival_time();
};