/**
 * This is the main include file for Einhard.
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

#include <iostream>
#include <iomanip>
#include <ctime>

// This C header is sadly required to check whether writing to a terminal or a file
#include <stdio.h>

namespace einhard
{
	static char const VERSION[] = "0.1";
	
	static char const ANSI_COLOR_WARN[]   = "\33[33m"; // orange
	static char const ANSI_COLOR_ERROR[]  = "\33[31m"; // red
	static char const ANSI_COLOR_FATAL[]  = "\33[31m"; // red
	static char const ANSI_COLOR_INFO[]   = "\33[32m"; // green
	static char const ANSI_COLOR_DEBUG[]  = "\33[01;34m"; // blue
	static char const ANSI_COLOR_CLEAR[]  = "\33[0m";

	enum LogLevel{ ALL, TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF };

	inline char const * getLogLevelString( const LogLevel level );

	template<typename Parent> struct Color
	{
		bool reset;
		Color() : reset(true) {}
		Color<Parent> operator~() const { Color<Parent> tmp(*this); tmp.reset = false; return tmp; }
		char const *ansiCode() const { return Parent::ANSI; }
		bool resetColor() const { return reset; }
	};
#define _COLOR(name, code) \
	struct _##name { static char const ANSI[]; }; \
	char const _##name::ANSI[] = "\33[" code "m"; \
	typedef Color<_##name> name

	_COLOR(Red,     "01;31");
	_COLOR(Green,   "01;32");
	_COLOR(Orange,  "00;33");
	_COLOR(Yellow,  "01;33");
	_COLOR(Blue,    "01;34");
	_COLOR(Magenta, "01;35");
	_COLOR(Cyan,    "01;36");
	_COLOR(NoColor, "0"    );
#undef _COLOR

	/**
	 * A utility class that does not print anywhere.
	 * This allows to not print stuff.
	 */
	template<LogLevel VERBOSITY> class OutputFormatter
	{
		private:
			// The output stream to print to
			std::ostream * const out;
			// Whether to colorize the output
			bool const colorize;
			mutable bool resetColor;

		public:
			OutputFormatter( std::ostream * const out, bool const colorize ) : out( out ), colorize( colorize ),
				resetColor(false)
			{
				if( out != 0 )
				{
					// Figure out current time
					time_t rawtime;
					tm * timeinfo;
					time( &rawtime );
					timeinfo = localtime( &rawtime );
					
					if( colorize )
					{
						// set color according to log level
						switch ( VERBOSITY ) {
							case WARN:
								*out << ANSI_COLOR_WARN;
								break;
							case ERROR:
								*out << ANSI_COLOR_ERROR;
								break;
							case FATAL:
								*out << ANSI_COLOR_FATAL;
								break;
							case INFO:
								*out << ANSI_COLOR_INFO;
								break;
							case DEBUG:
								*out << ANSI_COLOR_DEBUG;
								break;
							default:
								// in other cases we leave the default color
								break;
						}
					}

					// output it
					*out << '[';
					*out << std::setfill('0') << std::setw(2) << timeinfo->tm_hour;
					*out << ':';
					*out << std::setfill('0') << std::setw(2) << timeinfo->tm_min;
					*out << ':';
					*out << std::setfill('0') << std::setw(2) << timeinfo->tm_sec;
					*out << ']';
					// TODO would be good to have this at least .01 seconds
					// for non-console output pure timestamp would probably be better

					// output the log level of the message
					*out << ' ' << getLogLevelString( VERBOSITY ) << ": ";

					if( colorize ) {
						// reset color according to log level
						switch ( VERBOSITY ) {
							case INFO:
							case DEBUG:
							case WARN:
							case ERROR:
							case FATAL:
								*out << ANSI_COLOR_CLEAR;
								break;
							default:
								// in other cases color is still default anyways
								break;
						}
					}
				}
			}

			template<typename T> inline const OutputFormatter<VERBOSITY>& operator<<( const Color<T> &col ) const
			{
				if (out && colorize) {
					*out << col.ansiCode();
					resetColor = col.resetColor();
				}
				return *this;
			}

			template<typename T> inline const OutputFormatter<VERBOSITY>& operator<<( const T &msg ) const
			{
				// output the log message
				if( out != 0 ) {
					*out << msg;
					if (resetColor) {
						*out << ANSI_COLOR_CLEAR;
						resetColor = false;
					}
				}

				return *this;
			}

			~OutputFormatter( )
			{
				if( out != 0 )
				{
					// make sure there is no strange formatting set anymore
					*out << std::resetiosflags(  std::ios_base::floatfield  | std::ios_base::basefield
											   | std::ios_base::adjustfield | std::ios_base::uppercase
											   | std::ios_base::showpos     | std::ios_base::showpoint
											   | std::ios_base::showbase    |  std::ios_base::boolalpha );

					*out << std::endl; // TODO this would probably better be only '\n' as to not flush the buffers
				}
			}
	};

	template<LogLevel MAX = ALL> class Logger
	{
		private:
			LogLevel verbosity;
			bool colorize;

		public:
			Logger( const LogLevel verbosity = WARN ) : verbosity( verbosity ) {
				// use some, sadly not c++-ways to figure out whether we are writing ot a terminal
				// only colorize when we are writing ot a terminal
				colorize = isatty( fileno( stdout ) );
			};
			Logger( const LogLevel verbosity, const bool colorize ) : verbosity( verbosity ), colorize( colorize ) { };

			inline const OutputFormatter<TRACE> trace() const;
			inline const OutputFormatter<DEBUG> debug() const;
			inline const OutputFormatter<INFO> info() const;
			inline const OutputFormatter<WARN> warn() const;
			inline const OutputFormatter<ERROR> error() const;
			inline const OutputFormatter<FATAL> fatal() const;

			inline bool beTrace() const;
			inline bool beDebug() const;
			inline bool beInfo() const;
			inline bool beWarn() const;
			inline bool beError() const;
			inline bool beFatal() const;

			inline void setVerbosity( LogLevel verbosity )
			{
				this->verbosity = verbosity;
			}
			inline LogLevel getVerbosity( ) const
			{
				return this->verbosity;
			}
			inline char const * getVerbosityString( ) const
			{
				return getLogLevelString( this->verbosity );
			}
			inline void setColorize( bool colorize )
			{
				this->colorize = colorize;
			}
			inline void getColorize( ) const
			{
				return this->colorize;
			}
	};

	/*
	 * IMPLEMENTATIONS
	 */

	inline char const * getLogLevelString( const LogLevel level )
	{
		switch( level )
		{
			case ALL:
				return "ALL";
			case TRACE:
				return "TRACE";
			case DEBUG:
				return "DEBUG";
			case INFO:
				return "INFO";
			case WARN:
				return "WARNING";
			case ERROR:
				return "ERROR";
			case FATAL:
				return "FATAL";
			case OFF:
				return "OFF";
			default:
				return "--- Something is horribly broken - A value outside the enumation has been given ---";
		}
	}

	template<LogLevel MAX> const OutputFormatter<TRACE> Logger<MAX>::trace() const
	{
		if( beTrace() )
			return OutputFormatter<TRACE>( &std::cout, colorize );
		else
			return OutputFormatter<TRACE>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beTrace() const
	{
#ifdef NDEBUG
		return false;
#else
		return ( MAX <= TRACE && verbosity <= TRACE );
#endif
	}

	template<LogLevel MAX> const OutputFormatter<DEBUG> Logger<MAX>::debug() const
	{
		if( beDebug() )
			return OutputFormatter<DEBUG>( &std::cout, colorize );
		else
			return OutputFormatter<DEBUG>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beDebug() const
	{
#ifdef NDEBUG
		return false;
#else
		return ( MAX <= DEBUG && verbosity <= DEBUG );
#endif
	}

	template<LogLevel MAX> const OutputFormatter<INFO> Logger<MAX>::info() const
	{
		if( beInfo() )
			return OutputFormatter<INFO>( &std::cout, colorize );
		else
			return OutputFormatter<INFO>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beInfo() const
	{
		return ( MAX <= INFO && verbosity <= INFO );
	}

	template<LogLevel MAX> const OutputFormatter<WARN> Logger<MAX>::warn() const
	{
		if( beWarn() )
			return OutputFormatter<WARN>( &std::cout, colorize );
		else
			return OutputFormatter<WARN>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beWarn() const
	{
		return ( MAX <= WARN && verbosity <= WARN );
	}

	template<LogLevel MAX> const OutputFormatter<ERROR> Logger<MAX>::error() const
	{
		if( beError() )
			return OutputFormatter<ERROR>( &std::cout, colorize );
		else
			return OutputFormatter<ERROR>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beError() const
	{
		return ( MAX <= ERROR && verbosity <= ERROR );
	}

	template<LogLevel MAX> const OutputFormatter<FATAL> Logger<MAX>::fatal() const
	{
		if( beFatal() )
			return OutputFormatter<FATAL>( &std::cout, colorize );
		else
			return OutputFormatter<FATAL>( 0, colorize );
	}

	template<LogLevel MAX> bool Logger<MAX>::beFatal() const
	{
		return ( MAX <= FATAL && verbosity <= FATAL );
	}

}

#define EINHARD_STREAM(arg) \
template<einhard::LogLevel VERBOSITY> \
inline const einhard::OutputFormatter<VERBOSITY>& operator<<(const einhard::OutputFormatter<VERBOSITY> &out, arg)
#define EINHARD_STREAM_T1(T1, arg) \
template<einhard::LogLevel VERBOSITY, T1> \
inline const einhard::OutputFormatter<VERBOSITY>& operator<<(const einhard::OutputFormatter<VERBOSITY> &out, arg)
#define EINHARD_STREAM_T2(T1, T2, arg1, arg2) \
template<einhard::LogLevel VERBOSITY, T1, T2> \
inline const einhard::OutputFormatter<VERBOSITY>& operator<<(const einhard::OutputFormatter<VERBOSITY> &out, arg1, arg2)

// vim: ts=4 sw=4 tw=100 noet
