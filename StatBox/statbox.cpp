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

	_elems.reserve(_capacity);
}

StatBox::~StatBox()
{
}

void StatBox::push(double const & elem)
{
	_is_mean_valid = false;
	_is_min_max_valid = false; 

	if (size() >= _capacity)
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
		
		_mean			= sum / size();
		_is_mean_valid	= true;
	}

	return _mean;
}

double StatBox::stddev()
{
	if (size() <= 1)
	{
		return 0.0;
	}

	double m = mean();
	double accum = 0.0;

	std::for_each(std::cbegin(_elems), std::cend(_elems), [&](const double d)
	{
		accum += (d - m)*(d - m);
	});

	return sqrt( accum / double(size()-1) );
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

size_t StatBox::size() { return _elems.size(); }

std::string StatBox::name() { return _name; }
std::string StatBox::unit() { return _unit; }


std::string StatBox::format()
{
	ostringstream os;

	if (_num_precision != 0 && _num_width != 0)
	{
		os.setf(ios::fixed, ios::floatfield);
	}

	os << std::setprecision(_num_precision)
		<< name() << " = " << std::setw(_num_width) << mean()
		<< " +- " << std::setw(_num_width) << stddev() << " " << unit() << " "
		<< "(" << std::setw(_num_width) << min()
		<< " to " << std::setw(_num_width) << max() << " " << unit() << ")";

	return os.str();
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
		auto result = std::minmax_element(_elems.begin(), _elems.end());

		_min = *result.first;
		_max = *result.second;

		_is_min_max_valid = true;
	}
}



