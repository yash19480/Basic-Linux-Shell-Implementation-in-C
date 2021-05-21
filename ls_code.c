#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<dirent.h>
#include<string.h>  

void commandError(){
    printf("This command is not recognised\n"); 
}

void directError() {
    printf("This directory cannot be opened\n"); 
}
int main(int argc, char* argv[]){
    int i; 
    char* input = argv[0]; 
    char* command ; 
    int k =0; 
    struct dirent* dir; 
    DIR *current_dir = opendir("."); 
    if(current_dir == NULL){
        directError(); 
        return 0; 
    }
    if(strlen(input) > 2 && input[2] != ' '){
        commandError(); 
        return 0; 
    }
    for(int i=0; input[i] != '\0'; i ++){
        if(input[i] != ' '){
            command[k] = input[i]; 
            k++; 
        }
    }
    if(strstr(command, "-a")){
        if(strstr(command, "-i")){
            while((dir = readdir(current_dir))!=NULL){
                printf("%lud     %s\n", dir->d_ino, dir->d_name); 
            }
            printf("\n"); 
        }
        else{
            while((dir = readdir(current_dir)) != NULL){
                printf("%s        ", dir->d_name);
            }
            printf("\n");
        }
    }
    else if(strlen(command) == 2){ 
        while(((dir = readdir(current_dir)) != NULL)){
            if(dir->d_name[0] != '.'){
                printf("%s        ", dir->d_name);
            }
        }
        printf("\n");
    }
    else if(strstr(command, "-i")){
        if (strstr(command, "-a")){
            while((dir = readdir(current_dir))!=NULL){
                printf("%lud     %s \n", dir->d_ino, dir->d_name); 
            }
            printf("\n"); 
        }
        else{
            while(((dir = readdir(current_dir)) != NULL) ){
                if(dir->d_name[0] != '.'){
                    printf("%lud     %s\n", dir->d_ino, dir->d_name); 
                }
            }
            printf("\n"); 
        }
    }
    else{
        commandError(); 
    }

    
    // closedir(dr);     
    return 0; 
}