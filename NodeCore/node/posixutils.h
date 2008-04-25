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