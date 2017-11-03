#include <iostream>
#include <conio.h>
#include "StatBox.h"

void show_stats(StatBox* stats_)
{
	std::cout 
		<< stats_->size() << " elements, "
		<< "last pushed " << stats_->last()
		<< ", mean = " << stats_->mean()
		<< ", stddev = " << stats_->stddev()
		<< ", min = " << stats_->min()
		<< ", max = " << stats_->max()
		<< std::endl;
}

void main(void)
{
	size_t capacity = 10;

	std::cout << "Capacity of box set to " << capacity << std::endl;

	StatBox* stats = new StatBox(capacity);

	for(int k = 0; k < 15; k++)
	{
		stats->push(float(k+1));
		show_stats(stats);
	}

	stats->reset();
	std::cout << "reset()" << std::endl;

	stats->push(20.5);
	show_stats(stats);

	stats->push(30.5);
	show_stats(stats);

	stats->push(10.5);
	show_stats(stats);


	_getch();
}