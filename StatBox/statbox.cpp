#include "statbox.h"

StatBox::StatBox(std::string name_, std::string unit_, size_t capacity_, int values_to_drop_)
{
	_name = name_;
	_unit = unit_;
	_values_capacity = capacity_;

	_is_cache_mean_valid = false;
	_is_cache_min_max_valid = false;

	_values_to_drop = values_to_drop_;
	_values_dropped = 0;

	_cached_mean = 0.0;
	_cached_min = 0.0;
	_cached_max = 0.0;

	_numeric_width = 0;
	_numeric_precision = 0;

	_values.reserve(_values_capacity);
}

StatBox::~StatBox()
{
}

void StatBox::push(double value)
{
	_is_cache_mean_valid = false;
	_is_cache_min_max_valid = false; 

	if (_values_dropped >= _values_to_drop)
	{
		if (get_sample_size() >= _values_capacity)
		{
			_values.erase(_values.begin());
		}

		_values.push_back(value);
	}
	else
	{
		_values_dropped++;
	}

}

void StatBox::reset()
{
	_values.clear();
	_values_dropped = 0;
	_is_cache_mean_valid = false;
	_is_cache_min_max_valid = false;
}

bool StatBox::has_stats() const
{
	return get_sample_size() > 0;
}

double StatBox::get_last_value() const
{
	if (!has_stats()) { return 0.0; }

	return _values.back();
}

double StatBox::get_mean() const
{
	if (!has_stats()) { return 0.0; }

	if (!_is_cache_mean_valid)
	{
		const double sum = std::accumulate(_values.cbegin(), _values.cend(), 0.0);

		_cached_mean = sum / get_sample_size();
		_is_cache_mean_valid = true;
	}

	return _cached_mean;

}

double StatBox::get_std() const
{
	if (get_sample_size() <= 1)
	{
		return 0.0;
	}

	double m = get_mean();
	double accum = 0.0;

	std::for_each(_values.cbegin(), _values.cend(), [&](const double d)
	{
		accum += (d - m)*(d - m);
	});

	return sqrt( accum / static_cast<double>(get_sample_size()-1) );
}

double StatBox::get_min() const
{
	if (!has_stats()) { return 0.0; }

	_cache_min_max();
	return _cached_min;
}

double StatBox::get_max() const
{
	if (!has_stats()) { return 0.0; }

	_cache_min_max();
	return _cached_max;
}

size_t StatBox::get_sample_size() const { return _values.size(); }

std::string StatBox::get_name() const { return _name; }

std::string StatBox::get_unit() const { return _unit; }

std::string StatBox::get_string() const
{
	if (!has_stats()) { return NO_STATS_STRING; }

	std::stringstream ss;

	ss.setf(std::ios::fixed, std::ios::floatfield);

	ss << std::setprecision(_numeric_precision)
		<< get_name() << ": " << std::setw(_numeric_width) << get_mean()
		<< " +- " << std::setw(_numeric_width) << get_std() << " " << get_unit() << " "
		<< "(" << std::setw(_numeric_width) << get_min()
		<< " to " << std::setw(_numeric_width) << get_max() << " " << get_unit() << ")"
		<< ", used " << get_sample_size() << " samples";

	return ss.str();
}

void StatBox::set_format(int format_width_, int format_precision_)
{
	_numeric_width = format_width_;
	_numeric_precision = format_precision_;
}

void StatBox::_cache_min_max() const
{
	if (!_is_cache_min_max_valid)
	{
		auto result = std::minmax_element(_values.cbegin(), _values.cend());

		_cached_min = *result.first;
		_cached_max = *result.second;

		_is_cache_min_max_valid = true;
	}
}

