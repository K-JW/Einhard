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
#include <ctime>

namespace einhard
{
	static char const * const VERSION = "0.1";

	enum LogLevel{ ALL, TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF };

	inline char const * getLogLevelString( const LogLevel level );

	/**
	 * A utility class that does not print anywhere.
	 * This allows to not print stuff.
	 */
	template<LogLevel VERBOSITY> class OutputFormatter
	{
		private:
			std::ostream * const out;

		public:
			OutputFormatter( std::ostream * const out ) : out( out )
			{
				if( out != 0 )
				{
					// Figure out current time
					time_t rawtime;
					tm * timeinfo;
					time( &rawtime );
					timeinfo = localtime( &rawtime );

					// output it
					*out << '[';
					// FIXME does not properly use 00:00:00 format but will print stuff like 1:1:1
					*out << timeinfo->tm_hour << ':' << timeinfo->tm_min << ':' << timeinfo->tm_sec;
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
					*out << std::endl; // TODO this would probably better be only '\n' as to not flush the buffers
			}
	};

	template<LogLevel MAX = ALL> class Logger
	{
		private:
			LogLevel verbosity;

		public:
			Logger( const LogLevel verbosity = WARN ) : verbosity( verbosity ) { };

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
			return OutputFormatter<TRACE>( &std::cout );
		else
			return OutputFormatter<TRACE>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beTrace() const
	{
		return ( MAX <= TRACE && verbosity <= TRACE );
	}

	template<LogLevel MAX> const OutputFormatter<DEBUG> Logger<MAX>::debug() const
	{
		if( beDebug() )
			return OutputFormatter<DEBUG>( &std::cout );
		else
			return OutputFormatter<DEBUG>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beDebug() const
	{
		return ( MAX <= DEBUG && verbosity <= DEBUG );
	}

	template<LogLevel MAX> const OutputFormatter<INFO> Logger<MAX>::info() const
	{
		if( beInfo() )
			return OutputFormatter<INFO>( &std::cout );
		else
			return OutputFormatter<INFO>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beInfo() const
	{
		return ( MAX <= INFO && verbosity <= INFO );
	}

	template<LogLevel MAX> const OutputFormatter<WARN> Logger<MAX>::warn() const
	{
		if( beWarn() )
			return OutputFormatter<WARN>( &std::cout );
		else
			return OutputFormatter<WARN>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beWarn() const
	{
		return ( MAX <= WARN && verbosity <= WARN );
	}

	template<LogLevel MAX> const OutputFormatter<ERROR> Logger<MAX>::error() const
	{
		if( beError() )
			return OutputFormatter<ERROR>( &std::cout );
		else
			return OutputFormatter<ERROR>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beError() const
	{
		return ( MAX <= ERROR && verbosity <= ERROR );
	}

	template<LogLevel MAX> const OutputFormatter<FATAL> Logger<MAX>::fatal() const
	{
		if( beFatal() )
			return OutputFormatter<FATAL>( &std::cout );
		else
			return OutputFormatter<FATAL>( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beFatal() const
	{
		return ( MAX <= FATAL && verbosity <= FATAL );
	}

}

