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

namespace einhard
{
	static char const * const VERSION = "0.1";
	
	static char const ANSI_ESCAPE = 27;
	static char const * const ANSI_COLOR_WARN = "[33m"; // yellow
	static char const * const ANSI_COLOR_ERROR = "[31m"; // red
	static char const * const ANSI_COLOR_FATAL = "[31m"; // red
	static char const * const ANSI_COLOR_CLEAR = "[0m";

	enum LogLevel{ ALL, TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF };

	inline char const * getLogLevelString( const LogLevel level );

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

		public:
			OutputFormatter( std::ostream * const out, bool const colorize ) : out( out ), colorize( colorize )
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
								*out << ANSI_ESCAPE << ANSI_COLOR_WARN;
								break;
							case ERROR:
								*out << ANSI_ESCAPE << ANSI_COLOR_ERROR;
								break;
							case FATAL:
								*out << ANSI_ESCAPE << ANSI_COLOR_FATAL;
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
				}
			}

			template<typename T> inline const OutputFormatter<VERBOSITY>& operator<<( T msg ) const
			{
				// output the log message
				if( out != 0 )
					*out << msg;

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

					if( colorize ) {
						// reset color according to log level
						switch ( VERBOSITY ) {
							case WARN:
							case ERROR:
							case FATAL:
								*out << ANSI_ESCAPE << ANSI_COLOR_CLEAR;
								break;
							default:
								// in other cases color is still default anyways
								break;
						}
					}
					
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
			Logger( const LogLevel verbosity = WARN, const bool colorize = true ) : verbosity( verbosity ), colorize( colorize ) { };

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

// vim: ts=4 sw=4 tw=100 noet
