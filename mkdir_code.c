#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<sys/wait.h> 
#include<fcntl.h> 
#include<string.h> 
#include<unistd.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include<dirent.h> 
#include<errno.h> 

void commandError(){
    printf("Command not working\n"); 
}

void dirError(){
    printf("Directory couldn't be created"); 
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
int main(int argc, char* argv[]){
    char* input = argv[0];
    char* command; 
    if(input[5] != ' '){
        commandError(); 
        return 0; 
    }
    int k = 0; 
    int i = checkSpace(input, 6); 
    // printf("%d", i); 
    int flag1= 0; 
    int flag2 = 0;  
    if(input[i] == '-'){
        if(input[i+1] == 'm' && input[i+2] == ' '){

            flag1 = 1; 
            i = i+2; 
        }
        else if(input[i+1] == 'v' && input[i+2] == ' '){
            flag2 = 1; 
            i = i+2; 
        }
        else{
            printf("This flag is not supported\n"); 
            return 0; 
        }
    }

    int flag3= 0 ; 
    int j ; 
    for(j = i; input[j] != '\0'; j++){
        if(input[j] != ' ' && input[j] != '-'){
            flag3 = 2; 
            break; 
        }
        else if(input[j] == '-'){
            flag3 = 1; 
            break; 
        }
    }
    if(flag3 == 1){
        if(input[j+1] == 'm' && input[j+2] == ' '){
            flag1 = 1; 
            j = j+2; 
        }
        else if(input[j+1] == 'v' && input[j+2] == ' '){
            flag2 = 1;
            j = j + 2;  
        }
        else{
            printf("This flag is not supported\n"); 
            return 0; 
        }
        i = j; 
    }
    else if(flag3 == 2){
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
        word++; 

        for(int i=0; i < word; i++){
            // printf("%s", dir[i] ); 
            
            int val; 
            if(flag1 == 1){
                val = mkdir(dir[i], 0777);
            }
            else{
                val = mkdir(dir[i], 0766); 
            }
            if(val == 1) {
                dirError();  
            }
            else{

                if(flag2== 1){
                    printf("mkdir : directory created %s\n", dir[i]); 
                }

            }
        }
    return 0; 
}