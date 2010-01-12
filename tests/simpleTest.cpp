/**
 * The most basic test for Einhard
 *
 * Copyright 2010 Matthias Bach <marix@marix.org>
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

#include <einhard/einhard.hpp>

using namespace einhard;

int main( int argc, char* argv[] )
{
	Logger<> baseLogger;

	baseLogger.trace() << "Trace output";
	baseLogger.trace() << 2 << " times traced";
	baseLogger.debug() << "Debug output";
	baseLogger.info() << "Info output";
	baseLogger.warn() << "Warning output";
	baseLogger.error() << "Error output";
	baseLogger.fatal() << "Fatal output";

	if( baseLogger.beTrace() )
		return 1;
	if( baseLogger.beDebug() )
		return 1;
	if( baseLogger.beInfo() )
		return 1;
	if( ! baseLogger.beWarn() )
		return 1;
	if( ! baseLogger.beError() )
		return 1;
	if( ! baseLogger.beFatal() )
		return 1;

	baseLogger.setVerbosity( ALL );

	baseLogger.info() << "The verbosity has now been set to " << baseLogger.getVerbosity() << " which is " << baseLogger.getVerbosityString();

	baseLogger.trace() << "Trace output";
	baseLogger.trace() << 2 << " times traced";
	baseLogger.debug() << "Debug output";
	baseLogger.info() << "Info output";
	baseLogger.warn() << "Warning output";
	baseLogger.error() << "Error output";
	baseLogger.fatal() << "Fatal output";

	if( ! baseLogger.beTrace() )
		return 1;
	if( ! baseLogger.beDebug() )
		return 1;
	if( ! baseLogger.beInfo() )
		return 1;
	if( ! baseLogger.beWarn() )
		return 1;
	if( ! baseLogger.beError() )
		return 1;
	if( ! baseLogger.beFatal() )
		return 1;

	// No news are good news
	return 0;
}

