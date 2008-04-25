/*
 * This file is part of NodeBox.
 *
 * Copyright (C) 2008 Frederik De Bleser (frederik@pandora.be)
 *
 * NodeBox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NodeBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NodeBox.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef posixutils_h
#define posixutils_h

#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

#define NAMLEN(dirent) strlen((dirent)->d_name)

typedef std::vector<std::string> posix_dirlist_t;
typedef posix_dirlist_t::iterator posix_diriter_t;

const int POSIX_FILE = DT_REG;
const int POSIX_DIR = DT_DIR;

posix_dirlist_t posix_listdir(const char *path, int type=64);

bool posix_file_exists(const char *path);

#endif // posixutils_h