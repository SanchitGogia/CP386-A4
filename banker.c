#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void display(int maximum[][4],int allocated[][4], int need[][4], int available[]){
    int i =0;
    
    printf("\nResources available: ");
    for (int x = 0; x<4; x++) printf("%d ",available[x] );
    printf("\nMaximum resources available per customer: ");
    while (i < 5){
        printf("\n%d: ",i);
        for (int x=0;x<4;x++ ) printf("%d ",maximum[i][x]);
        
        i++;
    }
    i = 0;
    printf("\nResources allocated to each customer: ");
    while (i < 5){
        printf("\n%d: ",i);
        for (int x=0;x<4;x++ ) printf("%d ",allocated[i][x]);
        i++;
    }
    printf("\nResources available per customer: ");
    i =0;
    while (i < 5){
        printf("\n%d: ",i);
        for (int x=0;x<4;x++ ) printf("%d ",need[i][x]);
        i++;
    }
    printf("\n");


    
}
int safeSequence(int allocated[][4], int need[][4], int available[]){
    //int need1[5][4] = need;
    int available1[4]; 
    memcpy(available1,available,4*sizeof(int));
    int completion[5] = {0,0,0,0,0};
    //int safeSequence[5] = {-1,-1,-1,-1,-1};
    //int failState[1] = {-1};
    int c_count = 0; //count of completed customers for the sake of safe sequence
    int i = 0;
    while (c_count<5){
        printf("%d: \n",i);
        if (i == 5 && c_count<5) return 0;
        if (completion[i] == 0){
            int flag = 1;
            for(int x = 0; x<4;x++){
                if(need[i][x]>available1[x]){
                    printf("%d, %d, (%d , %d)\n",i,x, need[i][x],available1[x]);
                    flag = 0;
                    break;
                }
            }
            if(flag == 1){
                for (int x=0; x<4;x++){
                    available1[x] = available1[x] + allocated[i][x];
                    //printf("BITCH");

                }

                completion[i] = 1;
                printf("--------------");
                c_count++;
                i = 0;
                
            }
            else i++;
            
        }
        else i++;
        
        
    }
    return 1;
}


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
    for (int i = 0; i<4;i++){
        available[i] = atoi(argv[i+1]);
        
    }
    printf("Number of Customers: 5\n");
    printf("Currently Available resources: ");
    for (int x = 0; x<4; x++) printf("%d ",available[x] );
    printf("\nMaximum resources from file: ");
    int n = 0;
    while (n < 5){
        printf("\n");
        for (int x=0;x<4;x++ ) printf("%d ",maximum[n][x]);
        
        n++;
    }
    printf("\n");
    char a[50];
    char *command;
    while (1){
        printf("Enter Command: ");
        fgets(a,50,stdin);
        a[strcspn(a, "\n")] = 0;
        //a[strlen(a) - 1] = "\0";
        //printf("%s\n",a);
        char *p = strtok(a," ");
        if(strcmp(p,"RQ")==0) {
            printf("%s\n",p);
            int i = 0;
            
             p = strtok(NULL, " ");
            while(p!= NULL){
                
                temp[i] = atoi(p);
                //printf("%d ,",temp[i]);
                i++;
                p = strtok(NULL, " ");  
            }
            i = 0;
            //for (int a = 0; a<4; a++) printf("%d, ",temp[a]);
            //printf("hey");
            if(temp[4] == -1) printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
            else{
                if((need[temp[0]][0] - temp[1]>=0 && available[0] - temp[1] >=0 )&&(need[temp[0]][1] - temp[2]>=0 && available[1] - temp[2] >=0 )&&(need[temp[0]][2] - temp[3]>=0 && available[2] - temp[3] >=0 )&&
                (need[temp[0]][3] - temp[4]>=0 && available[3] - temp[4] >=0 )){
                    while (i < 4){
                        available[i] = available[i] - temp[i+1];
                        need[temp[0]][i] = need[temp[0]][i] - temp[i+1];
                        allocated[temp[0]][i] = allocated[temp[0]][i] + temp[i+1];
                        //temp[i+1] = -1;  
                        i++;
                    }
                    //temp[0] = -1;
                    int v = safeSequence(allocated,need,available);
                    printf("SS = %d",v);
                    if( v== 1){
                        for (int x = 0; x< 5;x++) temp[x] = -1;
                        printf("State is safe, and request is satisfied\n");}
                    else {
                        i = 0;
                        while (i < 4){
                            available[i] = available[i] + temp[i+1];
                            need[temp[0]][i] = need[temp[0]][i] + temp[i+1];
                            allocated[temp[0]][i] = allocated[temp[0]][i] - temp[i+1];
                            temp[i+1] = -1;  
                            i++;
                    }
                        temp[0] = -1;
                        printf("State unsafe, request denied\n");
                    }
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
                temp[i] = atoi(p);
                i++;
                p = strtok(NULL," ");
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
                    i++; 
                }
                printf("The resources have been released successfully");
            }
        }
        else if(strcmp(p,"Run")==0) printf("Run \n");
        else if(strcmp(p,"Status")==0) display(maximum,allocated,need,available);
        else if(strcmp(p,"Exit")==0) break;
        else printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
    
    
}