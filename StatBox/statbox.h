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

class StatBox
{
public:

	// Constructor

	StatBox(std::string name_ = DEFAULT_NAME, std::string unit_ = DEFAULT_UNIT, size_t capacity_ = DEFAULT_CAPACITY, int values_to_drop_ = 0);
	~StatBox();

	// Methods

	void push(double const& value_);
	void reset();

	// Getters

	double get_last_value() const;
	double get_mean();
	double get_std();
	double get_min();
	double get_max();
	size_t get_valid_values() const;
	std::string get_string();
	std::string get_name() const;
	std::string get_unit() const;

	// Setters

	void set_format(int format_width_, int format_precision_);

private:

	size_t _values_capacity;
	std::vector<double> _values;	// vector of values pushed to the statbox
	
	int _values_to_drop;			// number of pushed first values to be ignored (e.g. to allow for warmups in timing statistics)
	int _values_dropped;
	
	bool _is_mean_valid;
	bool _is_min_max_valid;

	double _mean, _min, _max;

	int _numeric_width, _numeric_precision;	// width and precision for string formatting of numbers

	std::string _name;
	std::string _unit;

	void calc_min_max();
};

