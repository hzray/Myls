#ifndef _MYLS_H_
#define _MYLS_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 4096

// parse the command, determine which options are gonna to use
void parseCommand(int numArgs, char* args[], int* file_count, int* direct_count, int* path_count);

// myls
void defaultOption(char *path, int showpath);

// myls -i
void iOption(char *path, int showpath);

// myls -l
void lOption(char *path, int showpath);

// myls -li
void ilOption(char *path, int showpath);

// myls -R(li)
void xROption(char* path, void(*Option)(char*, int));

// count number of files or directories under current path (exclude those hidden ones)
int count_direct(DIR* directory);

// add name of non-hidden files or directories to nameList
void fill_nameList(DIR*directory, char* nameList[]);

// sort nameList lexicographically
void sort_nameList(char *nameList[], int n);

// find max length of inode of files or directories under current path
// use for print space 
int find_inode_length (char* nameList[], int n, char* path);

// find max length of those to-be-printed variables
// use for print space
void find_length(char *nameList[], int n, char* path, int *hardlink, int *size, int *onwer, int *group, int *space);

// assign input arguments to either fileList or directList
void fill_file_direct_list(int numArgs, char* args[], char* fileList[], char* directList[]);

int need_quote(char name[]);
#endif 