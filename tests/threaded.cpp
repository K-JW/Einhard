/**
 * Tests Einhard output if multipel threads are involved
 *
 * Copyright 2012 Matthias Bach <marix@marix.org>
 *
 * This file is part of Einhard.
 * 
 * Einhard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Einhard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Einhard.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/thread.hpp>
#include "einhard.hpp"

struct callable
{
	private:
		const unsigned id;
		einhard::Logger<einhard::ALL, true>& logger;
	public:
		callable(const unsigned id, einhard::Logger<einhard::ALL, true>& logger) : id(id), logger(logger) { };
		void operator()();
};

int main( int, char** )
{
	einhard::Logger<einhard::ALL, true> logger(einhard::INFO);

	boost::thread t1(callable(1,logger));
	boost::thread t2(callable(2,logger));
	boost::thread t3(callable(3,logger));
	boost::thread t4(callable(4,logger));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

void callable::operator()()
{
	for(unsigned i = 0; i < 100; ++i) {
		logger.info() << "Iteration " << i << " of thread " << id;
	}
}

// vim: ts=4 sw=4 tw=100 noet
