/**
 * C program to list file and sub-directories of a directory 
 * recursively in tree structure.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "aes.c"
char* encryptIt(uint8_t* data);
void tree(char *basePath, const int root);
void createFile(char* filename);
int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);

    tree(path, 0);

    return 0;
}


/**
 * Tree, prints all files and sub-directories of a given 
 * directory in tree structure.
 * 
 * @param basePath Base path to traverse directory
 * @param root     Integer representing indention for current directory
 */
void tree(char *basePath, const int root)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++) 
            {
                if (i%2 == 0 || i == 0)
                    printf("%c", 179);
                else
                    printf(" ");

            }

            printf("%c%c%s\n", 195, 196, dp->d_name);
            char* filename = encryptIt(dp->d_name);
            //encryptIt(dp->d_name);
            createFile(filename);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2);
        }
    }

    closedir(dir);
}
char* encryptIt(uint8_t* data){
    uint8_t key[] = "secret key 123";
    
    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, data, strlen((char*)data));
    printf("\nENC: %s\n",(char*) data); // don't use this string as an input
    return ((char*)data);    
}

void createFile(char* filename){
    FILE *fp;
    fp = fopen(filename, "w+");
    fclose(fp);
}