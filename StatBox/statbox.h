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
#define NO_STATS_STRING "No statistics available."

class StatBox
{
public:

	// Constructor

	StatBox(std::string name_ = DEFAULT_NAME, std::string unit_ = DEFAULT_UNIT, size_t capacity_ = DEFAULT_CAPACITY, int values_to_drop_ = 0);
	~StatBox();

	// Methods

	void push(double value_);
	void reset();
	bool has_stats() const;

	// Getters

	double get_last_value() const;
	double get_mean() const;
	double get_std() const;
	double get_min() const;
	double get_max() const;
	size_t get_sample_size() const;
	std::string get_string() const;
	std::string get_name() const;
	std::string get_unit() const;

	// Setters

	void set_format(int format_width_, int format_precision_);

private:

	size_t _values_capacity;
	std::vector<double> _values;	// vector of values pushed to the statbox
	
	int _values_to_drop;			// number of pushed first values to be ignored (e.g. to allow for warmups in timing statistics)
	int _values_dropped;
	
	mutable bool _is_cache_mean_valid;
	mutable bool _is_cache_min_max_valid;
	mutable double _cached_mean, _cached_min, _cached_max;

	int _numeric_width, _numeric_precision;	// width and precision for string formatting of numbers

	std::string _name;
	std::string _unit;

	void _cache_min_max() const;
};

