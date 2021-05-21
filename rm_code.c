#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<dirent.h>
#include<string.h>  
#include <fcntl.h>
#include <stdarg.h>

void commandError(){
    printf("Command not found\n");  
}
int checkCommand(char* input){
    if(input[2] != '\0' && input[2] == ' '){
        return 1; 
    }
    return 0; 
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
void removeError(){
    printf("File cannot be removed\n"); 
}
void removeFile(char* input, int flag1, int flag2){
    if(flag1 == 1){
        if(flag2 == 1){
            char choice; 
            printf("rm : remove regular file %s ? (y/n)   ", input); 
            scanf("%c", &choice); 
            if(choice == 'y' || choice == 'Y'){
                if(remove(input) == 0){
                    printf("removed '%s' \n", input); 
                }
                else{
                    removeError(); 
                }
            }
            else{
                return; 
            }
        }
        else{
             if(remove(input) == 0){
                printf("removed '%s' \n", input); 
            }
            else{
                removeError(); 
            }
        }
    }
    else{
        if(flag2== 1){
            char choice; 
            printf("rm : remove regular file %s ? (y/n)    ", input); 
            scanf("%c", &choice); 
            if(choice == 'y' || choice == 'Y'){
                if(remove(input) != 0){
                    removeError(); 
                }
                else{
                    return; 
                }
            }
            else{
                return; 
            }   
        }
        else{
            if(remove(input) == 0){
                return; 
            }
            else{
                removeError(); 
            }
        }
    }
}
int main(int argc, char* argv[]){
    char* input = argv[0]; 
    if(checkCommand(input) == 0){
        commandError(); 
        return 0; 
    } 
    int i; 
    i = checkSpace(input, 3); 
    int flag1 = 0; 
    int flag2 = 0; 
    if(input[i] == '-'){
        // printf("here\n"); 
        if(input[i+1] != '\0' && input[i+1] == 'v'){
            flag1 = 1; 
            i= i+2; 
            // printf("done\n"); 
        }
        else if(input[i+1] != '\0' && input[i+1] == 'i'){
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
        if(input[j+1] != '\0' && input[j+1] == 'v'){
            if(input[j+2] == ' '){
                flag1 = 1;  
                j = j+3; 
            }
            else {
                commandError(); 
                return 0; 
            }
        }
        else if(input[j+1] != '\0' && input[j+1] == 'i'){
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
        // printf("%c\n", input[i]); 
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
    word++;

    for(int i=0; i<word; i++){
        removeFile(dir[i], flag1, flag2); 
    }

}