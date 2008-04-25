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

#include "config.h"
#include "posixutils.h"

#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

posix_dirlist_t posix_listdir(const char *path, int type)
{
    errno = 0;
    DIR* dirp;
    struct dirent *ep;
    posix_dirlist_t fnames;

    if ((dirp = opendir(path)) == NULL) {
        printf("could not open dir.\n");
        return fnames;
    }
    
    for(;;) {
        ep = readdir(dirp);
        if (ep == NULL)
            break;
        if (ep->d_name[0] == '.' &&
            (NAMLEN(ep) == 1 ||
                (ep->d_name[1] == '.' && NAMLEN(ep) == 2)))
            // Skip the dot and double-dot names
            continue;
        if (!(ep->d_type & type))
            // Skip unrequested types
            continue;
        fnames.push_back(std::string(ep->d_name));
    }
    
    if (errno != 0) {
        // readdir() returned NULL and set errno
        closedir(dirp);
        printf("error %i while reading dir.\n", errno);
        return fnames;
    }
    closedir(dirp);
    return fnames;
}


bool posix_file_exists(const char *path)
{
    return access(path, R_OK) == 0;
}
