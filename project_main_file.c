#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
void get_file_names(char *path[]);


int main(int argc, char *argv[]){

	get_file_names(argv[1]);
	return 0;
}

void get_file_names(char *path[]){
	
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if(d){
	
		while ((dir = readdir(d)) != NULL){
			printf("%s\n", dir->d_name);
		}
		closedir(d); 
	}	
}
