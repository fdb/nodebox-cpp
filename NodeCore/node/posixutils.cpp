#include "NodeCore.h"

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
