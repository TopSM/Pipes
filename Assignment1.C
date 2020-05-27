//Name: Ostavo Palaios 
//Class: operating Systems Assignement 1
//Date: 9/26/19

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    printf("\n");
   // printf("Looking through Operating System Resource Folder:\n");
    int* nullptr= NULL;

    int fd[2];
    int p= pipe(fd); //Create pipe

    int pid1=NULL; 
    int pid=fork();    //First Fork

    if (p==-1){
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if(pid<0){
        printf("%d failed forks \n",pid );
        exit(1); 
    }
    else if(pid==0){  //  child1 is writing 
        close(fd[0]); //closing read
        dup2(fd[1],1); //writing
        printf("ls\n");
        execlp("ls","-F",NULL); //execute ls -F
        printf("should not execute past here 1\n");         
    }        
    else{ //parent
        pid1=fork();        //Second Fork
        if (pid1==0){   //  child2  is reading  
            close(fd[1]); //closing write
            dup2(fd[0],0); //using read   
            execlp("nl","nl",NULL);     //execute nl
            printf("should not execute past here 2\n");
        }
    }
    waitpid(pid,nullptr,0); //waits for first children to end
    close(fd[1]); //closes write 
    waitpid(pid1,nullptr,0) ; //wait for second children to end 
    printf("\n");
    return 0;
}