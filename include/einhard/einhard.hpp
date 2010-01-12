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

	/**
	 * A utility class that does not print anywhere.
	 * This allows to not print stuff.
	 */
	class OutputFormatter
	{
		private:
			std::ostream * const out;

		public:
			OutputFormatter( std::ostream * const out ) : out( out ) { };

			template<typename T> inline const OutputFormatter& operator<<( T arg ) const
			{
				if( out != 0 )
					*out << arg;

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

			inline const OutputFormatter trace() const;
			inline const OutputFormatter debug() const;
			inline const OutputFormatter info() const;
			inline const OutputFormatter warn() const;
			inline const OutputFormatter error() const;
			inline const OutputFormatter fatal() const;

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
				switch( this->verbosity )
				{
					case ALL:
						return "all";
					case TRACE:
						return "trace";
					case DEBUG:
						return "debug";
					case INFO:
						return "info";
					case WARN:
						return "warn";
					case ERROR:
						return "error";
					case FATAL:
						return "fatal";
					case OFF:
						return "off";
					default:
						return "--- Something is horribly broken - A value outside the enumation has been given ---";
				}
			}
	};

	/*
	 * IMPLEMENTATIONS
	 */

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::trace() const
	{
		if( beTrace() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beTrace() const
	{
		return ( MAX <= TRACE && verbosity <= TRACE );
	}

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::debug() const
	{
		if( beDebug() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beDebug() const
	{
		return ( MAX <= DEBUG && verbosity <= DEBUG );
	}

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::info() const
	{
		if( beInfo() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beInfo() const
	{
		return ( MAX <= INFO && verbosity <= INFO );
	}

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::warn() const
	{
		if( beWarn() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beWarn() const
	{
		return ( MAX <= WARN && verbosity <= WARN );
	}

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::error() const
	{
		if( beError() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beError() const
	{
		return ( MAX <= ERROR && verbosity <= ERROR );
	}

	template<LogLevel MAX> const OutputFormatter Logger<MAX>::fatal() const
	{
		if( beFatal() )
			return OutputFormatter( &std::cout );
		else
			return OutputFormatter( 0 );
	}

	template<LogLevel MAX> bool Logger<MAX>::beFatal() const
	{
		return ( MAX <= FATAL && verbosity <= FATAL );
	}

}

