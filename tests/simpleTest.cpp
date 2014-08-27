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

#include "einhard.hpp"

#include <cstring>
#include <stdio.h>
//#include <io.h>

using namespace einhard;

int main( int, char** )
{
	Logger<> baseLogger;
	baseLogger.setAreaName( "base" );

	baseLogger.trace() << "Trace output";
	baseLogger.trace() << 2 << " times traced";
	baseLogger.debug() << "Debug output";
	baseLogger.info() << "Info output";
	baseLogger.warn() << "Warning output";
	baseLogger.error() << "Error output";
	baseLogger.fatal() << "Fatal output";

	if( baseLogger.isEnabled<TRACE>() )
		return 1;
	if( baseLogger.isEnabled<DEBUG>() )
		return 1;
	if( baseLogger.isEnabled<INFO>() )
		return 1;
	if( ! baseLogger.isEnabled<WARN>() )
		return 1;
	if( ! baseLogger.isEnabled<ERROR>() )
		return 1;
	if( ! baseLogger.isEnabled<FATAL>() )
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
	baseLogger.info() << "Test some colors: " << Blue() << "blue " << "normal "
	    << ~Cyan() << "cyan " << "cyan " << NoColor() << "normal";
	baseLogger.info() << "Test all colors: "
            << DGray()  << "darkgray "
            << Black()  << "black "
            << Red()    << "red "
            << DRed()   << "darkred "
            << Green()  << "green "
            << DGreen() << "darkgreen "
            << Yellow() << "yellow "
            << Orange() << "orange "
            << Blue()   << "blue "
            << DBlue()    << "darkblue "
            << Magenta()  << "magenta "
            << DMagenta() << "darkmagenta "
            << Cyan()     << "cyan "
            << DCyan()    << "darkcyan "
            << White()    << "white "
            << Gray()     << "gray "
            ;
	baseLogger.info() << "Testing\nMultiline\nOutput with color\n";


	baseLogger.setColorize( false );
	baseLogger.info() << "Color is switched off now";

	baseLogger.trace() << "Trace output";
	baseLogger.trace() << 2 << " times traced";
	baseLogger.debug() << "Debug output";
	baseLogger.info() << "Info output";
	baseLogger.warn() << "Warning output";
	baseLogger.error() << "Error output";
	baseLogger.fatal() << "Fatal output";
	baseLogger.info() << "Test some colors: " << Blue() << "blue " << "normal "
	    << ~Cyan() << "cyan " << "cyan " << NoColor() << "normal";

	baseLogger.info() << "Exponential float " << std::scientific << 1.0f;
	baseLogger.info() << "Default float " << 1.0f;
	baseLogger.info() << "Testing\nMultiline\nOutput without color\n";


#ifdef NDEBUG
	if( baseLogger.isEnabled<TRACE>() )
		return 1;
	if( baseLogger.isEnabled<DEBUG>() )
		return 1;
#else
	if( ! baseLogger.isEnabled<TRACE>() )
		return 1;
	if( ! baseLogger.isEnabled<DEBUG>() )
		return 1;
#endif
	if( ! baseLogger.isEnabled<INFO>() )
		return 1;
	if( ! baseLogger.isEnabled<WARN>() )
		return 1;
	if( ! baseLogger.isEnabled<ERROR>() )
		return 1;
	if( ! baseLogger.isEnabled<FATAL>() )
		return 1;

	// No news are good news
	return 0;
}

