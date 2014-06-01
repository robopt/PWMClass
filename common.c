/*
Copyright (c) 2013 Adafruit
Author: Justin Cooper

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "common.h"

int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len)
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir (partial_path);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            // Enforce that the prefix must be the first part of the file
            char* found_string = strstr(ep->d_name, prefix);

            if (found_string != NULL && (ep->d_name - found_string) == 0) {
                snprintf(full_path, full_path_len, "%s/%s", partial_path, ep->d_name);
                (void) closedir (dp);
                return 1;
            }
        }
        (void) closedir (dp);
    } else {
        return 0;
    }

    return 0;
}

int load_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[40];
    char line[256];

    build_path("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        //PyErr_SetFromErrnoWithFilename(PyExc_IOError, slots);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            fclose(file);
            return 1;
        }
    }

    //if the device isn't already loaded, load it, and return
    fprintf(file, name);
    fclose(file);

    //0.2 second delay
    nanosleep((struct timespec[]){{0, 200000000}}, NULL);

    return 1;
}


int unload_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[40];
    char line[256];
    char *slot_line;

    build_path("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        //PyErr_SetFromErrnint build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);oWithFilename(PyExc_IOError, slots);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is loaded, let's unload it
        if (strstr(line, name)) {
            slot_line = strtok(line, ":");
            //remove leading spaces
            while(*slot_line == ' ')
                slot_line++;

            fprintf(file, "-%s", slot_line);
            fclose(file);
            return 1;
        }
    }

    //not loaded, close file
    fclose(file);

    return 1;
}