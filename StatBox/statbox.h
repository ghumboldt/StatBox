#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <math.h>

#define DEFAULT_CAPACITY 100
#define DEFAULT_NAME "Value"
#define DEFAULT_UNIT ""

using namespace std;

class StatBox
{
public:

	// Constructors

	StatBox();
	StatBox(std::string name_);
	StatBox(std::string name_, std::string unit_);
	StatBox(std::string name_, std::string unit_, size_t capacity_);
	~StatBox();

	// Methods

	void push(double const& value_);
	void reset();

	// Getters

	double get_last_value();
	double get_mean();
	double get_std();
	double get_min();
	double get_max();
	size_t get_num_values();
	std::string get_string();
	std::string get_name();
	std::string get_unit();

	// Setters

	void set_format(int format_width_, int format_precision_);

private:

	size_t _capacity;
	bool _is_mean_valid;
	bool _is_min_max_valid;

	double _mean;
	double _min, _max;

	int _num_width;
	int _num_precision;

	std::vector<double> _elems;
	std::string _name;
	std::string _unit;

	void calc_min_max();
};

