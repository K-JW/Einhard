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

# Einhard is currently header only -> We only have to look for headers
# However set EINHARD_LIBRARIES anyhow in case somebody expects it
SET(EINHARD_LIBRARIES "")

FIND_PATH(EINHARD_INCLUDE_DIRS einhard/einhard.hpp DOC "Include for Einhard")

FIND_PACKAGE_HANDLE_STANDARD_ARGS( Einhard DEFAULT_MSG EINHARD_INCLUDE_DIRS )

MARK_AS_ADVANCED(
  EINHARD_INCLUDE_DIRS
  EINHARD_LIBRARIES
)
