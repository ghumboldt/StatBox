#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#define DEFAULT_CAPACITY 100

using namespace std;

class StatBox
{
public:
	StatBox();
	StatBox(size_t capacity_);
	~StatBox();

	void push(double const&);
	void reset();

	double last();
	double mean();
	double stddev();
	double min();
	double max();

	size_t size();

	std::string to_string();


private:
	size_t _capacity;
	bool _is_mean_valid;
	bool _is_min_max_valid;

	double _mean;
	double _min, _max;

	std::vector<double> _elems;

	void calc_min_max();
};

