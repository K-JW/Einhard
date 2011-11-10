# This is a cmake utility file you can add to your own projects
# to find a version of Einhard for your build.
#
# This file is part of Einhard.
#
# Einhard is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Einhard is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Einhard.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2011 Matthias Bach <bach@compeng.uni-frankfurt.de>

FIND_PACKAGE( PackageHandleStandardArgs )

IF (APPLE)

	FIND_LIBRARY(EINHARD_LIBRARIES einhard DOC "Einhard lib for OSX"
		ENV DYLD_LIBRARY_PATH )

ELSE (APPLE)

	IF (WIN32)

		FIND_LIBRARY(EINHARD_LIBRARIES einhard
			ENV PATH
		)

	ELSE (WIN32)

		# Unix style platforms
		FIND_LIBRARY(EINHARD_LIBRARIES einhard
			ENV LD_LIBRARY_PATH
		)

	ENDIF (WIN32)

ENDIF (APPLE)

FIND_PATH(EINHARD_INCLUDE_DIRS einhard/einhard.hpp DOC "Include for Einhard")

# Also search relative to lib ( git build )
IF ( NOT EINHARD_INCLUDE_DIRS )
	GET_FILENAME_COMPONENT(_EINHARD_LIB_DIR ${EINHARD_LIBRARIES} PATH)
	GET_FILENAME_COMPONENT(_EINHARD_INC_CAND ${_EINHARD_LIB_DIR}/include ABSOLUTE)
	GET_FILENAME_COMPONENT(_EINHARD_INC_CAND2 ${_EINHARD_LIB_DIR}/../include ABSOLUTE)
	FIND_PATH(EINHARD_INCLUDE_DIRS einhard/einhard.hpp PATHS ${_EINHARD_INC_CAND} ${_EINHARD_INC_CAND2} )
ENDIF ( NOT EINHARD_INCLUDE_DIRS )


FIND_PACKAGE_HANDLE_STANDARD_ARGS( Einhard DEFAULT_MSG EINHARD_LIBRARIES EINHARD_INCLUDE_DIRS )

MARK_AS_ADVANCED(
  EINHARD_INCLUDE_DIRS
)
