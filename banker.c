/*
Sanchit Gogia 193272580 SanchitGogia
Nicholas Sam 190148430 nicholassam6425
https://github.com/SanchitGogia/CP386-A4
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
int maximum[5][4] = {{6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 5, 7, 5}};
int allocated[5][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int need[5][4] = {{6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 5, 7, 5}};

int available[4];

void display(int maximum[][4], int allocated[][4], int need[][4], int available[])
{
    int i = 0;

    printf("\nResources available: ");
    for (int x = 0; x < 4; x++)
        printf("%d ", available[x]);
    printf("\nMaximum resources available per customer: ");
    while (i < 5)
    {
        printf("\n%d: ", i);
        for (int x = 0; x < 4; x++)
            printf("%d ", maximum[i][x]);

        i++;
    }
    i = 0;
    printf("\nResources allocated to each customer: ");
    while (i < 5)
    {
        printf("\n%d: ", i);
        for (int x = 0; x < 4; x++)
            printf("%d ", allocated[i][x]);
        i++;
    }
    printf("\nResources available per customer: ");
    i = 0;
    while (i < 5)
    {
        printf("\n%d: ", i);
        for (int x = 0; x < 4; x++)
            printf("%d ", need[i][x]);
        i++;
    }
    printf("\n");
}
int safeCheck(int allocated[][4], int need[][4], int available[])
{
    // int need1[5][4] = need;
    int available1[4];
    memcpy(available1, available, 4 * sizeof(int));
    int completion[5] = {0, 0, 0, 0, 0};
    // int safeSequence[5] = {-1,-1,-1,-1,-1};
    // int failState[1] = {-1};
    int c_count = 0; // count of completed customers for the sake of safe sequence
    int i = 0;
    while (c_count < 5)
    {
        if (i == 5 && c_count < 5)
            return 0;
        if (completion[i] == 0)
        {
            int flag = 1;
            for (int x = 0; x < 4; x++)
            {
                if (need[i][x] > available1[x])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                for (int x = 0; x < 4; x++)
                {
                    available1[x] = available1[x] + allocated[i][x];
                    // printf("BITCH");
                }

                completion[i] = 1;
                c_count++;
                i = 0;
            }
            else
                i++;
        }
        else
            i++;
    }
    return 1;
}
int *safeSequence(int allocated[][4], int need[][4], int available[])
{
    // int need1[5][4] = need;
    int available1[4];
    memcpy(available1, available, 4 * sizeof(int));
    int completion[5] = {0, 0, 0, 0, 0};
    static int safeSequence[5] = {-1, -1, -1, -1, -1};
    // int failState[1] = {-1};
    int c_count = 0; // count of completed customers for the sake of safe sequence
    int i = 0;
    while (c_count < 5)
    {

        if (completion[i] == 0)
        {
            int flag = 1;
            for (int x = 0; x < 4; x++)
            {
                if (need[i][x] > available1[x])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                for (int x = 0; x < 4; x++)
                {
                    available1[x] = available1[x] + allocated[i][x];
                    // printf("BITCH");
                }

                completion[i] = 1;
                safeSequence[c_count] = i;
                c_count++;
                i = 0;
            }
            else
                i++;
        }
        else
            i++;
    }
    return safeSequence;
}

void runthread(int num_t)
{
    printf("--->    Customer/Thread %d\n", num_t);
    printf("\tAllocated Resources:   %d %d %d %d\n", allocated[num_t][0], allocated[num_t][1], allocated[num_t][2], allocated[num_t][3]);
    printf("\tNeeded Resources:      %d %d %d %d\n", need[num_t][0], need[num_t][1], need[num_t][2], need[num_t][3]);
    printf("\tAvailable Resources:   %d %d %d %d\n", available[0], available[1], available[2], available[3]);
    printf("\tThread has started\n");
    printf("\tThread has finished\n");
    printf("\tThread is releasing resources\n");
    for(int i = 0; i < 4; i++)
    {
        available[i] += allocated[num_t][i];
        allocated[num_t][i] = 0;
    }
    printf("\tNew Available:         %d %d %d %d\n", available[0], available[1], available[2], available[3]);
}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    if (argc != 5)
    {
        printf("Invalid input, try again\n");
        return 1;
    }

    int temp[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 4; i++)
    {
        available[i] = atoi(argv[i + 1]);
    }
    printf("Number of Customers: 5\n");
    printf("Currently Available resources: ");
    for (int x = 0; x < 4; x++)
        printf("%d ", available[x]);
    printf("\nMaximum resources from file: ");
    int n = 0;
    while (n < 5)
    {
        printf("\n");
        for (int x = 0; x < 4; x++)
            printf("%d ", maximum[n][x]);

        n++;
    }
    printf("\n");
    char a[50];
    char *command;
    while (1)
    {
        printf("Enter Command: ");
        fgets(a, 50, stdin);
        a[strcspn(a, "\n")] = 0;
        char *p = strtok(a, " ");
        if (strcmp(p, "RQ") == 0)
        {
            int i = 0;

            p = strtok(NULL, " ");
            while (p != NULL)
            {
                temp[i] = atoi(p);
                i++;
                p = strtok(NULL, " ");
            }
            i = 0;
            if (temp[4] == -1)
                printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
            else
            {
                if ((need[temp[0]][0] - temp[1] >= 0 && available[0] - temp[1] >= 0) 
                 && (need[temp[0]][1] - temp[2] >= 0 && available[1] - temp[2] >= 0)
                 && (need[temp[0]][2] - temp[3] >= 0 && available[2] - temp[3] >= 0) 
                 && (need[temp[0]][3] - temp[4] >= 0 && available[3] - temp[4] >= 0))
                {
                    while (i < 4)
                    {
                        available[i] -= temp[i + 1];
                        need[temp[0]][i] -= temp[i + 1];
                        allocated[temp[0]][i] += temp[i + 1];
                        i++;
                    }
                    int v = safeCheck(allocated, need, available);
                    if (v == 1)
                    {
                        for (int x = 0; x < 5; x++)
                            temp[x] = -1;
                        printf("State is safe, and request is satisfied\n");
                    }
                    else
                    {
                        i = 0;
                        while (i < 4)
                        {
                            available[i] = available[i] + temp[i + 1];
                            need[temp[0]][i] = need[temp[0]][i] + temp[i + 1];
                            allocated[temp[0]][i] = allocated[temp[0]][i] - temp[i + 1];
                            temp[i + 1] = -1;
                            i++;
                        }
                        temp[0] = -1;
                        printf("State unsafe, request denied\n");
                    }
                }
                else
                    printf("State unsafe, request denied\n");
            }
        }
        else if (strcmp(p, "RL") == 0)
        {
            int i = 0;
            p = strtok(NULL, " ");
            while (p != NULL)
            {
                temp[i] = atoi(p);
                i++;
                p = strtok(NULL, " ");
            }
            i = 0;

            if (temp[4] == -1)
                printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
            else
            {
                int release_counter;
                while (i < 4)
                {
                    release_counter = allocated[temp[0]][i] - temp[i + 1];
                    if (release_counter < 0)
                    {
                        available[i] = available[i] + allocated[temp[0]][i];
                        need[temp[0]][i] = need[temp[0]][i] + allocated[temp[0]][i];
                        allocated[temp[0]][i] = 0;
                    }
                    else
                    {
                        available[i] = available[i] + temp[i + 1];
                        need[temp[0]][i] = need[temp[0]][i] + temp[i + 1];
                        allocated[temp[0]][i] = release_counter;
                    }
                    temp[i + 1] = -1;
                    i++;
                }
                printf("The resources have been released successfully");
            }
        }
        else if (strcmp(p, "Run") == 0)
        {

            int *seq = safeSequence(allocated, need, available);
            for (int i = 0; i < 5; i++)
            {
                printf("%d\n", seq[i]);
                pthread_t thread_id;
                pthread_create(&thread_id, NULL, runthread, seq[i]);
                pthread_join(thread_id, NULL);
            }
        }
        else if (strcmp(p, "Status") == 0)
            display(maximum, allocated, need, available);
        else if (strcmp(p, "Exit") == 0)
            break;
        else
            printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
}