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
    int maximum[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
    int allocated[5][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int need[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
    int temp[5] = {-1,-1,-1,-1,-1};
   /* for (int i = 0; i<4;i++){
        available[i] = atoi(argv[i+1]);
        
    }*/
    char a[50];
    char *command;
    while (1){
        printf("Enter Command: ");
        scanf("%s",a);
        char *p = strtok(a," ");
        if(strcmp(p,"RQ")==0) {
            int i = 0;
            p = strtok(NULL," ");
            while(p!= NULL){
                temp[i] = (int) p;
                i++;
            }
            i = 0;
            
            if(temp[4] == -1) printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
            else{
                if((need[temp[0]][0] - temp[1]>=0 && available[0] - temp[1] >=0 )&&(need[temp[0]][1] - temp[2]>=0 && available[1] - temp[2] >=0 )&&(need[temp[0]][2] - temp[3]>=0 && available[2] - temp[3] >=0 )&&
                (need[temp[0]][0] - temp[1]>=0 && available[0] - temp[1] >=0 )){
                    while (i < 4){
                        available[i] = available[i] - temp[i+1];
                        need[temp[0]][i] = need[temp[0]][i] - temp[i+1];
                        allocated[temp[0]][i] = allocated[temp[0]][i] + temp[i+1];
                        temp[i+1] = -1;  
                    }
                    temp[0] = -1;
                    printf("State is safe, and request is satisfied\n");
                    /*available[0] = available[0] - temp[1];
                    available[1] = available[0] - temp[2];
                    available[2] = available[0] - temp[3];
                    available[3] = available[0] - temp[4];
                    need[temp[0]][0] = need[temp[0]][0] - temp[1];
                    need[temp[0]][1] = need[temp[0]][1] - temp[2];
                    need[temp[0]][2] = need[temp[0]][2] - temp[3];
                    need[temp[0]][3] = need[temp[0]][3] - temp[4];
                    allocated[temp[0]][0] = allocated[temp[0]][0] - temp[1];
                    allocated[temp[0]][1] = allocated[temp[0]][1] - temp[2];
                    allocated[temp[0]][2] = allocated[temp[0]][2] - temp[3];
                    allocated[temp[0]][3] = allocated[temp[0]][3] - temp[4];
                    temp[0] = -1;
                    temp[1] = -1;
                    temp[2] = -1;   */
                }
                else printf("State unsafe, request denied\n");
            }
        }
        else if (strcmp(p,"RL")==0) {
            int i = 0;
            p = strtok(NULL," ");
            while(p!= NULL){
                temp[i] = (int) p;
                i++;
            }
            i = 0;
            
            if(temp[4] == -1) printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
            else{
                int release_counter;
                while (i < 4){
                    release_counter = allocated[temp[0]][i] - temp[i+1];
                    if(release_counter<0){
                        available[i] = available[i] + allocated[temp[0]][i];
                        need[temp[0]][i] = need[temp[0]][i] + allocated[temp[0]][i];
                        allocated[temp[0]][i] = 0;
                    }
                    else{
                        available[i] = available[i] + temp[i+1];
                        need[temp[0]][i] = need[temp[0]][i] + temp[i+1];
                        allocated[temp[0]][i] = release_counter;
                    }
                    temp[i+1] = -1;   
                }
                printf("The resources have been released successfully");
            }
        }
        else if(strcmp(p,"Run")==0) printf("Run \n");
        else if(strcmp(p,"Status")==0) printf("Status\n");
        else if(strcmp(p,"Exit")==0) break;
        else printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
    
    
}