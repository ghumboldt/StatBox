#include "statbox.h"

StatBox::StatBox() : StatBox(DEFAULT_NAME, DEFAULT_UNIT, DEFAULT_CAPACITY) {}

StatBox::StatBox(std::string name_) : StatBox(name_, DEFAULT_UNIT, DEFAULT_CAPACITY) {}

StatBox::StatBox(std::string name_, std::string unit_) : StatBox(name_, unit_, DEFAULT_CAPACITY) {}

StatBox::StatBox(std::string name_, std::string unit_, size_t capacity_)
{
	_name = name_;
	_unit = unit_;
	_capacity = capacity_;

	_is_mean_valid = false;
	_is_min_max_valid = false;

	_mean = 0.0;
	_min = 0.0;
	_max = 0.0;

	_num_width = 0;
	_num_precision = 0;

	_elems.reserve(_capacity);
}

StatBox::~StatBox()
{
}

void StatBox::push(double const & elem)
{
	_is_mean_valid = false;
	_is_min_max_valid = false; 

	if (get_num_values() >= _capacity)
	{
		_elems.erase(_elems.begin());
	}

	_elems.push_back(elem);
}

void StatBox::reset()
{
	_elems.clear();
	_is_mean_valid = false;
	_is_min_max_valid = false;
}

double StatBox::get_last_value()
{
	return _elems.back();
}

double StatBox::get_mean()
{
	if (!_is_mean_valid)
	{
		double sum		= std::accumulate(_elems.cbegin(), _elems.cend(), 0.0);
		
		_mean			= sum / get_num_values();
		_is_mean_valid	= true;
	}

	return _mean;
}

double StatBox::get_std()
{
	if (get_num_values() <= 1)
	{
		return 0.0;
	}

	double m = get_mean();
	double accum = 0.0;

	std::for_each(_elems.cbegin(), _elems.cend(), [&](const double d)
	{
		accum += (d - m)*(d - m);
	});

	return sqrt( accum / double(get_num_values()-1) );
}

double StatBox::get_min()
{
	calc_min_max();
	return _min;
}

double StatBox::get_max()
{
	calc_min_max();
	return _max;
}

size_t StatBox::get_num_values() { return _elems.size(); }

std::string StatBox::get_name() { return _name; }
std::string StatBox::get_unit() { return _unit; }


std::string StatBox::get_string()
{
	stringstream ss;

	ss << std::setprecision(_num_precision)
		<< get_name() << " = " << std::setw(_num_width) << get_mean()
		<< " +- " << std::setw(_num_width) << get_std() << " " << get_unit() << " "
		<< "(" << std::setw(_num_width) << get_min()
		<< " to " << std::setw(_num_width) << get_max() << " " << get_unit() << ")";

	return ss.str();
}

void StatBox::set_format(int format_width_, int format_precision_)
{
	_num_width = format_width_;
	_num_precision = format_precision_;
}

void StatBox::calc_min_max()
{
	if (!_is_min_max_valid)
	{
		auto result = std::minmax_element(_elems.cbegin(), _elems.cend());

		_min = *result.first;
		_max = *result.second;

		_is_min_max_valid = true;
	}
}



