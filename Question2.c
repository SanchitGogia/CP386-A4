/*
nicholassam6425 190148430
SanchitGogia
q2
Best Fit Algorithm
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct process
{
    int start;
    int memory;
    char *name;
};
struct block
{
    int start;
    int size;
};
struct process *plist;
struct block *freelist;
int freelist_size = 0;
int plist_size = 0;
int freelist_max = 1;
int plist_max = 1;
int memory_size;
int comparesize(const void *a, const void *b)
{
    struct block aa = *((struct block *)a);
    struct block bb = *((struct block *)b);

    if (aa.size < bb.size)
    {
        return -1;
    }
    if (aa.size == bb.size)
    {
        return 0;
    }
    if (aa.size > bb.size)
    {
        return 1;
    }
}
int comparestart(const void *a, const void *b)
{
    struct block aa = *((struct block *)a);
    struct block bb = *((struct block *)b);

    if (aa.start < bb.start)
    {
        return -1;
    }
    if (aa.start == bb.start)
    {
        return 0;
    }
    if (aa.start > bb.start)
    {
        return 1;
    }
}
void allocate(char *name, int size)
{
    // make new process struct and populate it
    struct process new_p;
    new_p.name = malloc(sizeof(char) * strlen(name));
    strcpy(new_p.name, name);
    new_p.memory = size;
    // default value for if a hole was found
    int inserted = -1;
    // best fit hole size
    int best_fit_size = memory_size;
    // iterate through free list
    for (int i = 0; i < freelist_size && inserted == -1; i++)
    {
        // if process can fit in hole AND hole is smaller than best fit size
        if (freelist[i].size >= new_p.memory && freelist[i].size <= best_fit_size)
        {
            // update best fit size and inserted
            best_fit_size = freelist[i].size;
            inserted = i;
        }
    }
    if (inserted == -1)
    {
        printf("No hole of sufficient size.\n");
    }
    else if (inserted != -1)
    {
        // if size of plist is about to go to big, realloc
        if (plist_size + 1 == plist_max)
        {
            plist_max *= 2;
            plist = realloc(plist, plist_max * sizeof(struct process));
        }
        // set new process start to hole start
        new_p.start = freelist[inserted].start;
        // move free list start to new start
        freelist[inserted].start += new_p.memory;
        // set size to new size
        freelist[inserted].size -= new_p.memory;
        // if allocating consumes an entire hole
        if (freelist[inserted].size == 0)
        {
            // and if the hole was at the end of the list
            if (inserted == freelist_size)
            {
                // just -1 the size
                freelist_size--;
            }
            else
            {
                // if hole isnt at end of the list
                for (int i = inserted + 1; i < freelist_size; i++)
                {
                    freelist[i - 1].start = freelist[i].start;
                    freelist[i - 1].size = freelist[i].size;
                }
                freelist_size--;
            }
        }
        plist[plist_size] = new_p;
        plist_size++;
        printf("Successfully allocated %d to Process %s\n", plist[plist_size - 1].memory, plist[plist_size - 1].name);
    }
}
void release(char *name)
{
    if (plist_size > 0)
    {
        int found = -1;
        for (int i = 0; i < plist_size && found == -1; i++)
        {
            //found
            if (strcmp(name, plist[i].name) == 0)
            {
                int relp_end = plist[i].memory + plist[i].start;
                // far left
                if (plist[i].start == 0)
                {
                    int ffound = -1;
                    for (int k = 0; k < freelist_size && ffound == -1; k++)
                    {
                        if (relp_end == freelist[k].start)
                        {
                            ffound = k;
                        }
                    }
                    // if right is allocated
                    if (ffound == -1)
                    {
                        if (freelist_max == freelist_size)
                        {
                            freelist_max *= 2;
                            freelist = realloc(freelist, freelist_max * sizeof(struct block));
                        }
                        freelist[freelist_size].size = plist[i].memory;
                        freelist[freelist_size].start = plist[i].start;
                        freelist_size++;
                    }
                    // if right is not allocated
                    else
                    {
                        freelist[ffound].start = plist[i].start;
                        freelist[ffound].size += plist[i].memory;
                    }
                }
                // far right
                else if (relp_end == memory_size)
                {
                    int ffound = -1;
                    for (int k = 0; k < freelist_size && found == -1; k++)
                    {
                        if (freelist[k].start + freelist[k].size == plist[i].start)
                        {
                            ffound = k;
                        }
                    }
                    // if left is allocated
                    if (ffound == -1)
                    {
                        if (freelist_max == freelist_size)
                        {
                            freelist_max *= 2;
                            freelist = realloc(freelist, freelist_max * sizeof(struct block));
                        }
                        freelist[freelist_size].size = plist[i].memory;
                        freelist[freelist_size].start = plist[i].start;
                        freelist_size++;
                    }
                    // left is hole
                    else
                    {
                        freelist[ffound].size += plist[i].memory;
                    }
                }
                //not far right or far left
                else
                {
                    int rfound = -1;
                    int lfound = -1;
                    for(int k = 0; k < freelist_size && (rfound == -1 || lfound == -1); k++)
                    {
                        //hole on right
                        if(freelist[k].start == relp_end)
                        {
                            rfound = k;
                        }
                        //hole on left
                        else if (freelist[k].start + freelist[k].size == plist[i].start)
                        {
                            lfound = k;
                        }
                    }
                    //left and right allocated
                    if (rfound == -1 && lfound == -1)
                    {
                        if (freelist_max == freelist_size)
                        {
                            freelist_max *= 2;
                            freelist = realloc(freelist, freelist_max * sizeof(struct block));
                        }
                        freelist[freelist_size].size = plist[i].memory;
                        freelist[freelist_size].start = plist[i].start;
                        freelist_size++;
                    }
                    //left and right holes
                    else if (rfound != -1 && lfound != -1)
                    {
                        freelist[lfound].size += plist[i].memory + freelist[rfound].size;
                        //if right hole is end of hole list
                        if (rfound == freelist_size-1)
                        {
                            freelist_size--;
                        }
                        //right hole is not at the end of hole list
                        else
                        {
                            for(int k = rfound + 1; k < freelist_size; k++)
                            {
                                freelist[k - 1].size = freelist[k].size;
                                freelist[k - 1].start = freelist[k].start;
                            }
                            freelist_size--;
                        }
                    }
                    //left allocated right hole
                    else if (rfound != -1 && lfound == -1)
                    {
                        freelist[rfound].start = plist[i].start;
                        freelist[rfound].size += plist[i].memory;
                    }
                    //left hole right allocated
                    else 
                    {
                        freelist[lfound].size += plist[i].memory;
                    }
                }
                found = i;
            }
        }
        if (found == -1)
        {
            printf("There is no process running by that name.\n");
        }
        else
        {
            if(found == plist_size-1)
            {
                plist_size--;
            }
            else
            {
                for(int k = found+1; k < plist_size; k++)
                {
                    plist[k-1].memory = plist[k].memory;
                    plist[k-1].start = plist[k].start;
                    strcpy(plist[k-1].name, plist[k].name);
                }
                plist_size--;
            }
            printf("Process %s successfully released\n", name);
        }
    }
    else
    {
        printf("There are no processes running.");
    }
}

void status()
{
    int totalallocated = 0;
    int totalfree = 0;
    qsort(freelist, freelist_size, sizeof(struct block), comparestart);
    for (int i = 0; i < plist_size; i++)
    {
        totalallocated += plist[i].memory;
    }
    for (int i = 0; i < freelist_size; i++)
    {
        totalfree += freelist[i].size;
    }
    printf("Partitions [Allocated Memory = %d]:\n", totalallocated);
    for (int i = 0; i < plist_size; i++)
    {
        printf("Address [%d:%d] Process %s\n", plist[i].start, plist[i].start + plist[i].memory - 1, plist[i].name);
    }
    printf("\nHoles [Free Memory = %d]:\n", totalfree);
    for (int i = 0; i < freelist_size; i++)
    {
        printf("Address [%d:%d] len = %d\n", freelist[i].start, freelist[i].start + freelist[i].size - 1, freelist[i].size);
    }
}
void main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    char input[41];
    char command[6];
    char p_name[10];
    int p_size;
    memory_size = strtol(argv[1], NULL, 10);
    freelist = malloc(freelist_max * sizeof(struct block));
    plist = malloc(plist_max * sizeof(struct process));
    freelist[0].start = 0;
    freelist[0].size = memory_size;
    freelist_size++;
    do
    {
        qsort(freelist, freelist_size, sizeof(struct block), comparesize);
        printf("command>");
        fgets(&input, 40, stdin);
        strcpy(command, strtok(input, " \n"));
        if (strcmp("RQ", command) == 0)
        {
            strcpy(p_name, strtok(NULL, " \n"));
            p_size = strtol(strtok(NULL, " \n"), NULL, 10);
            allocate(p_name, p_size);
        }
        else if (strcmp("RL", command) == 0)
        {
            strcpy(p_name, strtok(NULL, " \n"));
            release(p_name);
        }
        else if (strcmp("Status", command) == 0)
        {
            status();
        }
    } while (strcmp("Exit", command) != 0);
    printf("Exiting\n");
}
