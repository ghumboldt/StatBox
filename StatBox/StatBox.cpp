#include "StatBox.h"

StatBox::StatBox() : StatBox(DEFAULT_CAPACITY) {}

StatBox::StatBox(size_t capacity_)
{
	_capacity = capacity_;

	_is_mean_valid = false;
	_is_min_max_valid = false;

	_mean = 0.0;
	_min = 0.0;
	_max = 0.0;

	_elems.reserve(_capacity);
}

StatBox::~StatBox()
{
}

void StatBox::push(double const & elem)
{
	_is_mean_valid = false;
	_is_min_max_valid = false; 

	if (_elems.size() >= _capacity)
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

double StatBox::last()
{
	return _elems.back();
}

double StatBox::mean()
{
	if (!_is_mean_valid)
	{
		double sum		= std::accumulate(std::cbegin(_elems), std::cend(_elems), 0.0);
		
		_mean			= sum / _elems.size();
		_is_mean_valid	= true;
	}

	return _mean;
}

double StatBox::stddev()
{
	if (_elems.size() <= 1)
	{
		return 0.0;
	}

	double m = mean();
	double accum = 0.0;

	std::for_each(std::cbegin(_elems), std::cend(_elems), [&](const double d)
	{
		accum += (d - m)*(d - m);
	});

	return sqrt( accum / double(_elems.size()-1) );
}

double StatBox::min()
{
	calc_min_max();
	return _min;
}

double StatBox::max()
{
	calc_min_max();
	return _max;
}

size_t StatBox::size()
{
	return _elems.size();
}

void StatBox::calc_min_max()
{
	if (!_is_min_max_valid)
	{
		auto result = std::minmax_element(_elems.begin(), _elems.end());

		_min = *result.first;
		_max = *result.second;

		_is_min_max_valid = true;
	}
}



