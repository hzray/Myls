/*
reference list
1. Print file or directory information: 
    https://stackoverflow.com/a/10323127

2. Print date:
    http://www.cplusplus.com/reference/ctime/strftime/
    https://stackoverflow.com/a/26307720/12358813

3. Get absolute path of file or directory:
    https://stackoverflow.com/a/2153755

*/



#define _GNU_SOURCE
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
#include <sys/stat.h>
#include <time.h>
#include  "myls.h"

static int optioni, optionl, optionR = 0;


int main(int numArgs, char* args[]){
    // check options
    int valid_file_count = 0;
    int valid_direct_count = 0;
    int input_path_count = 0;
    parseCommand(numArgs, args, &valid_file_count, &valid_direct_count, &input_path_count);
    char* fileList[valid_file_count];
    char* directList[valid_direct_count];
    fill_file_direct_list(numArgs, args, fileList, directList);
    sort_nameList(fileList, valid_file_count);
    sort_nameList(directList, valid_direct_count);
    // default option
    if (optioni == 0 && optionl == 0 && optionR == 0){
        if (input_path_count == 0){
            defaultOption(".", 0);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                defaultOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                if (input_path_count == 1){
                    defaultOption(directList[i], 0);
                }
                else{
                    defaultOption(directList[i], 1);
                }
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }
            }
        }
    }
    
    // -i option
    else if(optioni == 1 && optionl == 0 && optionR == 0){
        if (input_path_count == 0){
            iOption(".", 0);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                iOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                if (input_path_count == 1){
                    iOption(directList[i], 0);
                }
                else{
                    iOption(directList[i], 1);
                }
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }

            }
        }
    }

    // -l option
    else if(optioni == 0 && optionl == 1 && optionR == 0){
        if (input_path_count == 0){
            lOption(".", 0);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                lOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                if (input_path_count == 1){
                    lOption(directList[i], 0);
                }
                else{
                    lOption(directList[i], 1);
                }
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }

            }
        }
    }

    // -R option
    else if(optioni == 0 && optionl == 0 && optionR == 1){
        if (input_path_count == 0){
            xROption(".", defaultOption);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                defaultOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                xROption(directList[i], defaultOption);
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }
            }
        }
    }

    // -li option
    else if(optioni == 1 && optionl == 1 && optionR == 0){
         if (input_path_count == 0){
            ilOption(".", 0);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                ilOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                if (input_path_count == 1){
                    ilOption(directList[i], 0);
                }
                else{
                    ilOption(directList[i], 1);
                }
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }

            }
        }
    }

    // -iR option
    else if(optioni == 1 && optionl == 0 && optionR == 1){
        if (input_path_count == 0){
            xROption(".", iOption);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                iOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                xROption(directList[i], iOption);
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }
            }
        }
    }

    // -lR option
    else if(optioni == 0 && optionl == 1 && optionR == 1){
        if (input_path_count == 0){
            xROption(".", lOption);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                lOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                xROption(directList[i], lOption);
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }
            }
        }
    }

    // -ilR option
    else if(optioni == 1 && optionl == 1 && optionR == 1){
        if (input_path_count == 0){
            xROption(".", ilOption);
        }
        else{
            for (int i=0; i<valid_file_count; i++){
                ilOption(fileList[i], 0);
                free(fileList[i]);
                if (i==valid_file_count-1 && valid_direct_count!=0){
                    printf("\n");
                }
            }
            for (int i=0; i<valid_direct_count;i++){
                xROption(directList[i], ilOption);
                free(directList[i]);
                if (i!=valid_direct_count-1){
                    printf("\n");
                }
            }
        }
    }
}

// parse the command argument, find which options are requested
void parseCommand(int numArgs, char* args[], int* file_count, int* direct_count, int* path_count){
    struct stat fileStat;
    int hasFile = 0;
    if (numArgs == 1){
        return;
    }
    for (int i=1; i<numArgs; i++){
        int arglen = strlen(args[i]);
        if (strncmp("-", args[i],1)!=0 || hasFile==1){
            hasFile = 1;
            if (lstat(args[i],&fileStat) == 0){
                if (S_ISDIR(fileStat.st_mode)){
        	        (*direct_count) ++;
                }
                else{
                    (*file_count) ++;
                }
            }
            else{
                printf("myls: cannot access '%s': No such file or directory\n", args[i]);
            }
            (*path_count) ++;
            
            continue;
        }

        for (int j=1; j<arglen; j++){
            switch (args[i][j]){
                case 'i':
                    optioni = 1;
                    break;
                case 'l':
                    optionl = 1;
                    break;
                case 'R':
                    optionR = 1;
                    break;
                default:
                    printf("myls: invalid option -- '%c' \n", args[i][j]);
                    exit(1);
            }
        }
    }
}

// myls
void defaultOption(char *path, int showpath){
    DIR *directory;
    struct stat fileStat;
    int n = 0; // number of files/directories
    directory = opendir(path);
    if (directory == NULL){
        // not directory, but may be a valid file
        if (lstat(path, &fileStat) == 0){
            printf("%s\n", path);
            closedir(directory);
            return;
        }
        closedir(directory);
        printf("myls: cannot access '%s': No such file or directory\n", path);
        return;
    }
    
    // get number of non-hidden files and directories
    n = count_direct(directory);

    rewinddir(directory);
    // get name of files and directories in sorted order
    char* nameList[n];
    fill_nameList(directory, nameList);
    sort_nameList(nameList, n);
    // if there are multiple paths, we will print path first
    if (showpath==1){
        printf("%s: \n", path);
    }
    for(int i=0; i<n ;i++){
        printf("%s\n", nameList[i]);
        free(nameList[i]);
    }
    closedir(directory);
    return;
}



// myls -i
void iOption(char *path, int showpath){
    DIR *directory;
    struct stat fileStat;
    int n = 0;
    directory = opendir(path);
    if (directory == NULL){
        if (lstat(path, &fileStat) == 0){
            printf("%ld %s\n", fileStat.st_ino, path);
            closedir(directory);
            return;
        }
        closedir(directory);
        printf("myls: cannot access '%s': No such file or directory\n", path);
        return;
    }

    n = count_direct(directory);
    rewinddir(directory);
    char* nameList[n];
    fill_nameList(directory, nameList);
    sort_nameList(nameList, n);

    // first, find the maximum length of digits among inodes with function max_digits_length
    int inodeDigit = find_inode_length(nameList, n, path);

    // then, print information
    if (showpath == 1){
        printf("%s: \n", path);
    }
    for (int i=0; i<n; i++){
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        strcat(abs_path, "/");
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);
        printf("%*ld %s\n", inodeDigit, fileStat.st_ino, nameList[i]);
        free(nameList[i]);
    }
    closedir(directory);
    return;
}


// myls -l
void lOption(char *path, int showpath){
    DIR *directory;
    struct stat fileStat;
    struct passwd *pw;
    struct group *grp;
    int n = 0;
    directory = opendir(path);
    if (directory == NULL){
        if (lstat(path, &fileStat) == 0){
            printf("-");
            // Reference : https://stackoverflow.com/a/10323127
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%ld ", fileStat.st_nlink);
            pw = getpwuid(fileStat.st_uid);
            printf("%s ", pw->pw_name);
            grp = getgrgid(fileStat.st_gid);
            printf("%s ", grp->gr_name);
            // size in byte
            printf("%ld ", fileStat.st_size);
            char timebuffer[80];
            strftime(timebuffer, 80, "%b %2d %Y %2H:%2M", localtime(&(fileStat.st_mtime)));
            printf("%s ", timebuffer);
            // file name
            printf("%s", path);
            // soft link
            char linkname[MAX_NAME_LENGTH];
            ssize_t r = readlink(path, linkname, MAX_NAME_LENGTH);
            if (r!= -1){
                linkname[r] = '\0';
                printf(" -> %s\n", linkname);  
            }
            else{
                printf("\n");
            }
        
            closedir(directory);
            return;
        }
        closedir(directory);
        printf("myls: cannot access '%s': No such file or directory\n", path);
        return;
    }
    n = count_direct(directory);
    rewinddir(directory);
    char* nameList[n];
    fill_nameList(directory, nameList);
    sort_nameList(nameList, n);

    // determine max width of to-be-printed variables
    int hardlinkDigit, sizeDigit, ownerLength, groupLength;
    int space = 0;
    find_length(nameList, n, path, &hardlinkDigit, &sizeDigit, &ownerLength, &groupLength, &space);

    if (showpath == 1){
        printf("%s: \n", path);
    }  
    for (int i=0; i<n; i++){
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        strcat(abs_path, "/");
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);
        // type 
        if (S_ISDIR(fileStat.st_mode)){
        	printf("d");
        }
        else if (S_ISLNK(fileStat.st_mode)){
        	printf("l");
        }
        else{
        	printf("-");
        }
        // permissions
        // Reference : https://stackoverflow.com/a/10323127
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x " : "- ");
        // hardlink
        printf("%*ld ", hardlinkDigit, fileStat.st_nlink);
        // owner name
        pw = getpwuid(fileStat.st_uid);
        printf("%*s ", ownerLength, pw->pw_name);
        // group name
        grp = getgrgid(fileStat.st_gid);
        printf("%*s ", groupLength, grp->gr_name);
        // size in byte
        printf("%*ld ", sizeDigit, fileStat.st_size);
        // time 
        // reference: http://www.cplusplus.com/reference/ctime/strftime/
        // reference: https://stackoverflow.com/a/26307720/12358813
        char timebuffer[80];
        strftime(timebuffer, 80, "%b %2d %Y %2H:%2M", localtime(&(fileStat.st_mtime)));
        printf("%s ", timebuffer);
        // file name
        if(space == 0){
            printf("%s", nameList[i]);
        }
        else{
            // no space in this name
            if (need_quote(nameList[i])==0){
                printf(" %s", nameList[i]);
            }
            else{
                printf("'%s'", nameList[i]);
            }
        }
        // print softlink filename, if any
        // reference: https://stackoverflow.com/a/55521879/12358813
        char linkname[MAX_NAME_LENGTH];
        ssize_t r = readlink(abs_path, linkname, MAX_NAME_LENGTH);
        if (r!= -1){
            linkname[r] = '\0';
            printf(" -> %s\n", linkname);  
        }
        else{
            printf("\n");
        }
        free(nameList[i]);
    }
    closedir(directory);
    return;
}


// myls -il
void ilOption(char *path, int showpath){
    DIR *directory;
    struct stat fileStat;
    struct passwd *pw;
    struct group *grp;
    int n = 0;
    directory = opendir(path);
    if (directory == NULL){
        if(lstat(path, &fileStat) == 0){
            printf("%ld ", fileStat.st_ino);
            printf("-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%ld ", fileStat.st_nlink);
            pw = getpwuid(fileStat.st_uid);
            printf("%s ", pw->pw_name);
            grp = getgrgid(fileStat.st_gid);
            printf("%s ", grp->gr_name);
            // size in byte
            printf("%ld ", fileStat.st_size);
            char timebuffer[80];
            strftime(timebuffer, 80, "%b %2d %Y %2H:%2M", localtime(&(fileStat.st_mtime)));
            printf("%s ", timebuffer);
            // file name
            printf("%s", path);
            char linkname[MAX_NAME_LENGTH];
            ssize_t r = readlink(path, linkname, MAX_NAME_LENGTH);
            if (r!= -1){
                linkname[r] = '\0';
                printf(" -> %s\n", linkname);  
            }
            else{
                printf("\n");
            }
            closedir(directory);
            return;
        }
        closedir(directory);
        printf("myls: cannot access '%s': No such file or directory\n", path);
        return;
    }
    n = count_direct(directory);
    rewinddir(directory);
    char* nameList[n];
    fill_nameList(directory, nameList);
    sort_nameList(nameList, n);

    // determine max width of to-be-printed variables
    int hardlinkDigit, sizeDigit, ownerLength, groupLength;
    int space = 0;
    find_length(nameList, n, path, &hardlinkDigit, &sizeDigit, &ownerLength, &groupLength, &space);
    int inodeDigit = find_inode_length(nameList, n, path);
    if (showpath == 1){
        printf("%s: \n", path);
    }  
    for (int i=0; i<n; i++){
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        strcat(abs_path, "/");
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);

        // inode
        printf("%*ld ", inodeDigit, fileStat.st_ino);
        // type and permission
        if (S_ISDIR(fileStat.st_mode)){
        	printf("d");
        }
        else if (S_ISLNK(fileStat.st_mode)){
        	printf("l");
        }
        else{
        	printf("-");
        }
        // Reference : https://stackoverflow.com/a/10323127
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x " : "- ");
        // hardlink
        printf("%*ld ", hardlinkDigit, fileStat.st_nlink);
        // owner name
        pw = getpwuid(fileStat.st_uid);
        printf("%*s ", ownerLength, pw->pw_name);
        // group name
        grp = getgrgid(fileStat.st_gid);
        printf("%*s ", groupLength, grp->gr_name);
        // size in byte
        printf("%*ld ", sizeDigit, fileStat.st_size);
        // time 
        // reference: http://www.cplusplus.com/reference/ctime/strftime/
        // reference: https://stackoverflow.com/a/26307720/12358813
        char timebuffer[80];
        strftime(timebuffer, 80, "%b %2d %Y %2H:%2M", localtime(&(fileStat.st_mtime)));
        printf("%s ", timebuffer);
        // file name
        if(space == 0){
            printf("%s", nameList[i]);
        }
        else{
            // no space in this name
            if (need_quote(nameList[i])==0){
                printf(" %s", nameList[i]);
            }
            else{
                printf("'%s'", nameList[i]);
            }
        }
        char linkname[MAX_NAME_LENGTH];
        ssize_t r = readlink(abs_path, linkname, MAX_NAME_LENGTH);
        if (r!= -1){
            linkname[r] = '\0';
            printf(" -> %s\n", linkname);  
        }
        else{
            printf("\n");
        }
        free(nameList[i]);
    }
    closedir(directory);
    return;
}

// myls -R(i)(l)
void xROption(char* path, void(*Option)(char*, int)){
    
    DIR *directory;
    struct stat fileStat;
    int n = 0;
    directory = opendir(path);
    Option(path, 1);
    // get ready for recursive step
    // as usual, first get name of files/directories under current path
    n = count_direct(directory);
    rewinddir(directory);
    char* nameList[n];
    fill_nameList(directory, nameList);
    sort_nameList(nameList, n);
    
    // recursive step
    for (int i=0; i<n; i++){
        // use absolute path get get information of file/directory
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        if (path[strlen(path)-1] !='/'){
            strcat(abs_path, "/");
        }
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);
        // it is a directory
        if (S_ISDIR(fileStat.st_mode)){
            printf("\n");
            xROption(abs_path, Option);
        }
        free(nameList[i]);
    }
    closedir(directory);
    return;
}


// sort the list containing files and directories lexicographically
void sort_nameList(char *nameList[], int n){
    for(int i=0; i<n; i++){
        int min = i;
        for(int j=i+1; j<n; j++){
            if(strcmp(nameList[min],nameList[j])>0){
                min = j;
            }
        }
        char* temp = nameList[i];
        nameList[i] = nameList[min];
        nameList[min] = temp;
    }
}

// count the number of files and directory under current path
int count_direct(DIR* directory){
    int count = 0;
    struct dirent *dp;
    while((dp = readdir(directory)) != NULL){
        char *name = dp->d_name;
        // skip hidden file
        if (strncmp(name, "." ,1) == 0){
            continue;
        }
        count ++;
    }
    return count;
}



// fill a list containing names of files and directories under current folder
void fill_nameList(DIR*directory, char* nameList[]){
    struct dirent *dp;
    int i = 0;
    while((dp = readdir(directory)) != NULL){
        char *name = dp->d_name;
        // skip hidden file
        if (strncmp(name, "." ,1) == 0){
            continue;
        }
        nameList[i] = malloc((strlen(name)+1)*sizeof(char));
        strcpy(nameList[i], name);
        i ++;
    }
    return;

}

// find the max length of inode of files or directories within current path
int find_inode_length (char* nameList[], int n, char* path){
    struct stat fileStat;
    int digit = 0;
    long maxinode = 0;
    for (int i=0; i<n; i++){
        // use absolute path get inode of file or directory
        // https://stackoverflow.com/a/2153755
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        strcat(abs_path, "/");
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);
        long inode = fileStat.st_ino;
        if (inode  > maxinode){
            maxinode = inode;
        }
    }
    while(maxinode / 10 > 0){
        digit ++;
        maxinode /= 10;
    }
    return digit + 1;
}


// find max length of multiple variables that need to be print
void find_length(char* nameList[], int n, char* path, int *hardlink, int *size, int *onwer, int *group, int* space){
    struct stat fileStat;
    struct group *grp;
    struct passwd *pw;
    int hardlink_length = 0;
    int size_length = 0;
    int owner_length = 0;
    int group_length = 0;

    long maxhardlink = 0;
    long maxsize = 0;

    int alreadyspace = 0;
    for (int i=0; i<n ;i++){
        // first check if space in name
        if (alreadyspace == 0){
            if (need_quote(nameList[i]) == 1){
                alreadyspace = 1;
                *space = 1;
            }
        }
        
        char abs_path[MAX_NAME_LENGTH];
        strcpy(abs_path, path);
        strcat(abs_path, "/");
        strcat(abs_path, nameList[i]);
        lstat(abs_path, &fileStat);
        if (fileStat.st_nlink > maxhardlink){
            maxhardlink = fileStat.st_nlink;
        }
        if (fileStat.st_size > maxsize){
            maxsize = fileStat.st_size;
        }
        pw = getpwuid(fileStat.st_uid);
        if (strlen(pw->pw_name) > owner_length){
            owner_length = strlen(pw->pw_name);
        }
        grp = getgrgid(fileStat.st_gid);
        if (strlen(grp->gr_name) > group_length){
            group_length = strlen(grp->gr_name);
        }
    }
    while (maxhardlink / 10 > 0){
        hardlink_length ++;
        maxhardlink /= 10;
    }
    while(maxsize / 10 > 0){
        size_length ++;
        maxsize /= 10;
    }
    *hardlink = hardlink_length+1;
    *size = size_length+1;
    *onwer = owner_length;
    *group = group_length;
    return;
}

void fill_file_direct_list(int numArgs, char* args[], char* fileList[], char* directList[]){
    struct stat fileStat;
    int hasFile = 0;
    if (numArgs == 1){
        return;
    }
    int file_index = 0;
    int direct_index = 0;
    for (int i=1; i<numArgs; i++){
        if (strncmp("-", args[i],1)!=0 || hasFile==1){
            hasFile = 1;
            if (lstat(args[i],&fileStat) == 0){
                if (S_ISDIR(fileStat.st_mode)){
        	        directList[direct_index] = malloc((strlen(args[i])+1)*sizeof(char));
                    strcpy(directList[direct_index], args[i]);
                    direct_index++;
                }
                else{
                    fileList[file_index] = malloc((strlen(args[i])+1)*sizeof(char));
                    strcpy(fileList[file_index], args[i]);
                    file_index++;
                }
            }
            continue;
        }
    }
}

int need_quote(char name[]){
    for(int i=0; name[i]!='\0'; i++){
        if (name[i] == ' ' || name[i] == '!' || name[i] == '$' || name[i] == '^' || name[i] == '&' || name[i] == '(' || name[i] == ')'){
            return 1;
        }
    }
    return 0;
}



