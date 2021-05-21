#include<stdio.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h>
#include<sys/wait.h>  
#include<unistd.h> 
#include<dirent.h>
#include<string.h>  
#include<fcntl.h>
#include<stdarg.h>
#include<time.h> 
#include<errno.h> 

void commandError(){
    printf("Command not found");  
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
    printf("File cannot be removed"); 
}
int checkCommand(char* input){
    if(input[4] == ' ' || input[4] == '\0'){
        return 1; 
    }
    return 0; 
} 
void findTime(char* ch, int flag1, int flag2){
    if(flag1 == 1){
    
        time_t now; 
        time(&now);
        struct tm* n_time = gmtime(&now);  
        int year = 1900 + n_time->tm_year ; 
        printf("%d - %d - %d    %d : %d : %d UTC \n",n_time->tm_mday, n_time->tm_mon+1,year, n_time->tm_hour, n_time->tm_min, n_time->tm_sec);
    }
    else if(flag2 == 1){
        pid_t pid = fork(); 
        if(pid < 0){
            printf("command could not be found\n"); 
        }
        else if(pid == 0){
            
            int pd = open("date_help.txt", O_RDONLY); 
            char buff; 
            while(read(pd, &buff, 1)>0){
                printf("%c", buff); 
            }
            exit(0); 
        }
        else{
            wait(NULL); 
            return; 
        }

    }
    else{
        
        time_t now; 
        time(&now); 
        printf("%s", ctime(&now)); 
    }
}
int main(int argc, char* argv[]){ 
    char* input = argv[0]; 
    if(checkCommand(input) == 0){
        commandError(); 
        return 0; 
    }
    int i; 
    i = checkSpace(input, 5);

    int flag1=0; 
    int flag2=0; 

    if(input[i] == '-'){
        // printf("here\n"); 
        if(input[i+1] != '\0' && input[i+1] == 'u'){
            flag1 = 1; 
            i= i+2; 
            // printf("done\n"); 
        }
        else if(input[i+1] != '\0' && input[i+1] == 'h'){
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
        if(input[j+1] != '\0' && input[j+1] == 'u'){
            if(input[j+2] == ' '){
                flag1 = 1;  
                j = j+3; 
            }
            else {
                commandError(); 
                return 0; 
            }
        }
        else if(input[j+1] != '\0' && input[j+1] == 'h'){
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

    findTime(input, flag1, flag2); 
}