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

#define MAX_HISTORY_SIZE 1024
void commandError(){
    printf("This command does not exist\n"); 
}

void directoryError(){
    printf("This directory does not exist\n");  
}

void echoError(){
    printf("This is not a proper commmand.\n"); 
}
void appendHistory(char history[][MAX_HISTORY_SIZE], int top, char* location) {
    FILE* file = fopen(location, "a"); 
    
    for(int i=0; i<top; i++){
        fputs(history[i], file); 
        fputs("\n", file); 
    }
    fclose(file) ; 
}

int main(){    int top= 0;
    system("clear"); 
    char FolderDirectory[1024]; 
    char HistoryFolder[1024]; 
    getcwd(FolderDirectory, sizeof(FolderDirectory)); 
    getcwd(HistoryFolder, sizeof(HistoryFolder)); 
    char history[MAX_HISTORY_SIZE][1024]; 
    char* location = strcat(HistoryFolder, "/history.txt"); 
    FILE* file = fopen(location, "rt"); 
    if(file == NULL){
        printf("History file could not be loaded, terminating ... \n"); 
        exit(1);
    }
    char buffer[1024] ; 
    while(fgets(buffer, sizeof(buffer), file)!=NULL){  
        for(int j=0; buffer[j] != '\0' && buffer[j] != '\n'; j++){
            history[top][j] = buffer[j]; 
        }
        // printf("%s\n", history[top]);
        top++; 
    }
    fclose(file); 
    char currentDirectory[1024];
    printf("terminal >>> : \n"); 
    while(1){
        getcwd(currentDirectory, sizeof(currentDirectory));   
        printf("%s >>>  ", currentDirectory);  
        char input[1024]; 
        char command[1024]; 
        char history_check[1024]; 
        int h =0;
        // this is working fine for input
        scanf(" %1023[^\n]s", input);
        for(int i=0; input[i] != '\0'; i++){
            history_check[h] = input[i] ;
            h++; 
        }
        if(strcmp (history_check, "")){
            int i; 
            for(i=0; input[i] != '\0'; i++){
                history[top][i] = input[i]; 
            }
            history[top][i] = '\0'; 
            FILE* file = fopen(location, "a"); 
            fputs(history[top], file); 
            fputs("\n", file ); 
            fclose(file); 
            top++;
        }
        if(input[0] =='c' && input[1] == 'd'){
            if(input[2] != ' ' && input[2] == '\0'){
                commandError(); 
            }
            else{
                int i; 
                for( i= 3; input[i] != '\0'; i++){
                    if(input[i] != ' '){
                        break; 
                    }
                }
                // printf("%d\n", i); 
                int flag1 = 0; 
                int flag2 = 0; 
                if(input[i] == '-'){
                    if(input[i+1] == 'P'){
                        if(input[i+2] != ' '){
                            commandError(); 
                            continue; 
                        }
                        else{
                            flag1= 1; 
                        }
                    }
                    else{
                        printf("this flag is not supported\n"); 
                        continue ; 
                    }
                    i = i+3; 
                }
                // printf("%d\n", i); 
                int j; 
                int k= 0;  
                for(j = i; input[j] != '\0'; j++ ){
                    // printf("%c\n", input[j]); 
                    if(input[j] != ' '){
                        command[k] = input[j];
                    } 
                    k++; 
                }
                command[k] = '\0'; 
                if(strcmp(command, "~") == 0){
                    chdir("/home/yash"); 
                }

                else{
                    // printf("%s\n", command);
                    int val; 
                    val = chdir(command); 
                    // printf("%s\n", command); 
                    if(val != 0){
                        printf("%s\n", strerror(errno));  
                    }
                    else{
                        continue; 
                    }
                }
            }   
        }
        else if(strstr(input, "echo")){
            if(input[4] != ' '){
                commandError(); 
            }
            else{
                int i; 
                for( i=5; input[i] != '\0'; i++){
                    if(input[i] != ' '){
                        break; 
                    }
                }
                int flag1 = 0; 
                int flag2 = 0; 
                if(input[i] == '\0'){
                    printf("\n"); 
                }
                else if(input[i] == '-'){
                    if(input[i+1] != '\0' && input[i+2] != '\0' && input[i+1] == 'E' && input[i+2] == ' '){ 
                        flag1 = 1; 
                        i = i+3; 
                    }
                    else if(input[i+1] != '\0' && input[i+2] != '\0' &&  input[i+1] == 'n' && input[i+2] == ' '){
                        flag2 = 1; 
                        i = i+3; 
                    }
                    else if(input[i+1] != '\0' && input[i+2] != '\0' && (input[i+1] != 'E' || input[i+1] != 'n')){
                        printf("This flag is not supported"); 
                        continue; 
                    }
                        int j; 
                        for(j = i; input[j] != '\0'; j++){
                            if(input[j] != ' '){
                                // printf("input[j] : %c\n", input[j]); 
                                break; 
                            }
                        }
                        if(input[j] == '-'){
                            // printf("Here\n");  
                            if(input[j+1] != '\0' && input[j+2] != '\0' && input[j+1] == 'E' && input[j+2] == ' '){ 
                                flag1 = 1; 
                                j = j+3;                    
                            }
                            else if(input[j+1] != '\0' && input[j+2] != '\0' &&  input[j+1] == 'n' && input[j+2] == ' '){
                                flag2 = 1; 
                                j = j+3; 
                            }
                        }
                        i=j; 
                }
                int j; 
                char message[1024];  
                for( j= i; input[j] != '\0'; j++){
                    message[j-i] = input[j]; 
                }
                message[j-i] = '\0'; 
                printf("%s      ", message); 
                if(flag2!= 1){
                    printf("\n"); 
                }
            }
        }
        else if(input[0] == 'p' && input[1] =='w' && input[2] == 'd'){
            int flag1 = 0; 
            int flag2 = 0; 
            int i; 
            for( i=4; input[i] != '\0'; i++){
                if(input[i] != ' '){
                    break; 
                }
            }
            if(input[i] == '-'){
                if(input[i+1] == 'P'){
                    flag1 = 1; 
                    i = i+2; 
                }
                else if(input[i+1] == '-'){
                    if(input[i+2] != 'h'){
                        commandError(); 
                        continue; 
                    }
                    else{
                        i = i+2; 
                        int j; 
                        for(j=i; input[j] != '\0' && j < i+4; j++){
                            command[j-i] = input[j];  
                        }
                        command[j-i] = '\0'; 
                        if(strcmp(command, "help") == 0){
                            flag2 =1; 
                        }
                        i = i+3 ; 
                    }
                }
                else{
                    printf("This flag is not supported\n"); 
                    continue; 
                }
            }
            if(flag2 == 1){
                int fd = open("pwd_help.txt", O_RDONLY); 
                char buff; 
                while(read(fd, &buff, 1) > 0){
                    printf("%c", buff); 
                }
                printf("\n\n"); 
            }
            else{
                getcwd(currentDirectory, sizeof(currentDirectory)); 
                printf("%s\n", currentDirectory) ; 
            }
        }
        else if(strcmp("exit", input) == 0){
            break; 
        }
        else if(strstr(input, "ln")){
            if(input[2] != ' '){
                commandError(); 
                continue; 
            }
            else{
                char currentDirectory[1024]; 
                char link[1024]; 
                int j=0; 
                int i; 
                for( i=3; input[i] != '\0'; i++){
                    if(input[i] == ' '){
                        break; 
                    }
                    else{
                        currentDirectory[j] = input[i] ; 
                        j++; 
                    }
                }
                if(input[i] == '\0'){
                    printf("symbolic link not provided"); 
                }
                else{
                    int l = 0; 
                    for(int k = i+1; input[k] != '\0'; k++){
                        link[l] = input[i];
                        l++;  
                    }
                    int link_no = symlink(currentDirectory, link); 
                    if(link_no!=0){
                        printf("%s\n" , strerror(errno)); 
                    }
                    else{
                        printf("Linking completed\n");  
                    }
                }
            }
        }
        else if(strstr(input, "history")){
            if(strcmp(input, "history")==0){
                int i =0; 
                for( i=0; i < top; i++){
                    for(int j=0; history[i][j] != '\0'; j++){
                        printf("%c", history[i][j]); 
                    }
                    printf("\n"); 
                }
            }
            else{
                int k = 0; 
                for(int i=7; input[i] != '\0'; i++){
                    if(input[i] != ' '){
                        command[k] = input[i]; 
                        k++; 
                    }
                }
                command[k] = '\0'; 
                int flag4 = 0 ; 
                for(int i=0; command[i] != '\0'; i++){
                    if(!isdigit(command[i])){
                        flag4 =1; 
                        break; 
                    }
                }
                if(flag4 == 0){
                    int i =0; 
                    for( i=top-atoi(command); i < top; i++){
                        for(int j=0; history[i][j] != '\0'; j++){
                            printf("%c", history[i][j]); 
                        }
                        printf("\n"); 
                    }
                }
                else{
                    if(strstr(command, "-a")){
                        int i; 
                        for(i=0; input[i] != '\0'; i++){
                            history[top][i] = input[i]; 
                        }
                        history[top][i] = '\0'; 
                        top++;
                        appendHistory(history, top, location); 
                    }
                    else if(strstr(command, "-c")){
                        top = 0; 
                    }
                    else if(strstr(command, "-a-c")){
                        appendHistory(history, top, location); 
                        top= 0; 
                    }
                    else if(strstr(command, "-c-a")){
                        top = 0 ; 
                        appendHistory(history, top, location); 
                    }
                    else{
                        commandError(); 
                    }
                }
            }
        }
        else if(strstr(input, "ls")){
            pid_t pid = fork();
            if(pid < 0){
                printf("Not possible\n"); 
            }
            else if(pid == 0){
                char* loc = strcat(FolderDirectory, "/ls"); 
                // printf("%s\n", loc); 
                int val = execl(loc, input, (char*)NULL);
                if(val == -1){
                    // printf("Here\n"); 
                    commandError(); 
                }
                exit(0); 
            }  
            else{
                waitpid(-1, NULL, 0); 
            }
        }
        else if(strstr(input, "mkdir")){
            pid_t pid = fork(); 
            if(pid<0){
                printf("Not possible\n"); 
            }
            else if(pid == 0){
                char* loc = strcat(FolderDirectory, "/mkdir"); 
                int val = execl(loc, input, (char*)NULL);

                if(val == -1){
                    commandError(); 
                }
                exit(0); 
            }
            else{
                wait(NULL); 
            }
        }
        else if(input[0] == 'c' && input[1]== 'a' && input[2] == 't'){
            pid_t pid = fork(); 
            if(pid < 0){
                printf("Not possible\n"); 
            }
            else if(pid == 0){ 
                // printf("Here \n");  
                char* loc = strcat(FolderDirectory, "/cat"); 
                // printf("%s\n", loc); 
                int val = execl(loc, input, (char *)NULL); 
                if(val == -1){
                    commandError(); 
                }
                exit(0); 
            } 
            else{
                wait(NULL); 
            }
        }
        else if(strstr(input, "rm")){
            pid_t pid = fork(); 

            if(pid < 0){
                printf("Not possible\n"); 
            }
            else if(pid == 0){
                char* loc = strcat(FolderDirectory, "/rm"); 
                int val = execl(loc, input, (char *)NULL);
                if(val == -1){
                    commandError(); 
                }
                exit(0); 
            }
            else{
                wait(NULL); 
            }
        }
        else if(strstr(input, "date")){
            pid_t pid = fork(); 

            if(pid < 0){
                printf("Not possible\n"); 
            }
            else if(pid == 0){
                char* loc = strcat(FolderDirectory, "/date"); 
                int val = execl(loc, input, (char *)NULL);

                if(val != 0){
                    printf("%s\n ", strerror(errno)); 
                }
                exit(0); 
            }
            else{
                wait(NULL); 
            } 
        }
        else{
            commandError(); 
        }
    }
    return 0; 
}
