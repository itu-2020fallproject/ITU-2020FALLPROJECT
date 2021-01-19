/**
 * C program to list file and sub-directories of a directory 
 * recursively in tree structure.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "aes.c"
#include <dir.h>
#include <sys/stat.h>


#define SIZE 150      //Maximum Length of name of folder

void createfile(char *dirname);

char* encryptIt(uint8_t* data);
void tree(char *basePath);
void createFile(char* filename);
int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);
	createfile("output");
    tree(path);
	
    return 0;
}


void tree(char *basePath)
{
    int i;
    char path[5000];
    char output[500]="output/";
    struct dirent *dp;
    DIR *dir = opendir(basePath);
	
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
    	memset(output,0,strlen(output));
    	strcat(output, "output/");
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, "output") != 0)
        {
        	struct stat sb;
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            strcat(output, strchr(path , '.')==NULL? strchr(path , '/')+1 : path+2 );//output stringi ./output/path seklinde yani klasordeki ayni agacin output klasoru uzerinden yaziyor dosya olustururken falan bu stringi kullanabilirsin.
            //printf("%s\n",output);
        	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))//eger path dosyasi bir klasorse burasi calisiyor
				{
					printf("%s\n", output);
				    createfile(output);
				}
			else{
				//buraya filelar için çalisacak kodlar yazilacak.
			}	
            tree(path);
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

void createfile(char *dirname) {
    
	mkdir(dirname);

    }
