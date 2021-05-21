#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<dirent.h>
#include<string.h>  
#include <fcntl.h>
#include <stdarg.h>

void catError(){
    printf("No file found\n"); 
}
void commandError(){
    printf("Command not found\n"); 
}
void doFunc(int fd, int flag1, int flag2){
    char buff; 
    int n = 1; 
    int k = 0; 
    int f= 1; 
    while(read(fd, &buff, 1) > 0){
        if(flag1 == 1 && f == 1){
            printf("%d    ", n); 
            n++; 
            f = 0; 
        }
        if(buff == '\n'){
            if(flag2 == 1){
                printf("$"); 
                if(flag1 == 1){
                    printf("\n%d    ", n); 
                    n++; 
                }
                else{
                    printf("\n"); 
                }
            }
            else{
                if(flag1== 1){
                    printf("\n%d    ", n); 
                    n++; 
                }
                else{
                    printf("\n"); 
                }
            }

        }
        else{
            printf("%c", buff); 
        }
    }
    if(flag2 ==1){
        printf("$"); 
    }
}
int checkSpace(char* input, int p){
    int i; 
    for(i=p; input[i]!= '\0'; i++){
        if(input[i] != ' '){
            break; 
        }
    }
    return i; 
}
int checkError(char* arg){
    if(arg[3] != ' '){
        return 0; 
    }
    return 1; 
}
int main(int argc, char* argv[]){
    if(checkError(argv[0]) == 0 ){
        return 0; 
    }
    char* input = argv[0]; 
    int i; 
    for( i=4; input[i] != '\0'; i++){
        if(input[i] != ' '){
            break; 
        }
    }

    int flag1 = 0; 
    int flag2 = 0; 
    if(input[i] == '-'){
        // printf("here\n"); 
        if(input[i+1] != '\0' && input[i+1] == 'n'){
            flag1 = 1; 
            i= i+2; 
            // printf("done\n"); 
        }
        else if(input[i+1] != '\0' && input[i+1] == 'e'){
            flag2 = 1; 
            i= i+2; 
        }
    }
    int flag3= 0; 
    int j; 
    for(j=i; input[j] != '\0'; j++){
        // printf("input[j] : %c\n", input[j]); 
        if(input[j] != ' ' && input[j]!= '-'){
            flag3 =1;
            break; 
        }
        else if(input[j] == '-'){
            // printf("reached here || \n"); 
            flag3 = 2; 
            break; 
        }
    }
    if(flag3 == 1){
        i = j; 
    }
    else if(flag3 == 2){
        // printf("reached here : %c\n", input[j+1]);
        if(input[j+1] != '\0' && input[j+1] == 'n'){
            if(input[j+2] == ' '){
                flag1 = 1;  
                j = j+3; 
            }
            else {
                commandError(); 
                return 0; 
            }
        }
        else if(input[j+1] != '\0' && input[j+1] == 'e'){
            // printf("reached here\n"); 
            if(input[j+2] == ' '){
                flag2 = 1;
                j = j+3;  
            }
            else{
                commandError(); 
                return 0; 
            }
        }
        i = j; 
    }
    
    int word = 0;
    int letter = 0; 
    char dir[1024][1024]; 
    while(input[i] != '\0'){
        if(input[i] != ' '){
            dir[word][letter] = input[i]; 
            letter++; 
            i++; 
        }
        else{
            dir[word][letter] = '\0'; 
            int pos = checkSpace(input, i); 
            word++; 
            letter = 0; 
            i = pos; 
        }
    } 
    dir[word][letter] == '\0';
    word++; 

    for(int i=0; i < word; i++){
            // printf("%s", dir[i] );  
        if(dir[i] == "\0"){
            continue; 
        }
        else{
            int fd = open(dir[i], O_RDONLY);
            if(fd == -1){
                catError(); 
            }
            else{
                doFunc(fd, flag1, flag2 ); 
            }
        }
    }
    printf("\n"); 
}