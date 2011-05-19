/**
 * Testing Einhard from multiple source files.
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

#ifndef _COMMON_SOURCE_H_
#define _COMMON_SOURCE_H_

#include "einhard.hpp"

#include <stdio.h>

/**
 * Global logging instance
 */

extern einhard::Logger<> baseLogger;

void file1();
void file2();

#endif /* _COMMON_SOURCE_H_ */

