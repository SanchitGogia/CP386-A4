#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){
    setbuf(stdout,NULL);
    if (argc != 5){
        printf("Invalid input, try again\n");
        return 1;
    }
    int available[4];
    int max[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};

   /* for (int i = 0; i<4;i++){
        available[i] = atoi(argv[i+1]);
        
    }*/
    char a[20];
    while (1){
        printf("Enter Command: ");
        scanf("%s",a);
        
        if(strcmp(a,"RQ")==0) printf("RQ\n");
        else if (strcmp(a,"RL")==0) printf("RL\n");
        else if(strcmp(a,"Run")==0) printf("Run \n");
        else if(strcmp(a,"Status")==0) printf("Status\n");
        else if(strcmp(a,"Exit")==0) break;
        else printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
    
    
}