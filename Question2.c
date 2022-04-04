/*
nicholassam6425 190148430
SanchitGogia
q2

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
int comparef(const void *a, const void *b)
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
    printf("In allocate function\n");
    struct process new_p;
    new_p.name = name;
    new_p.memory = size;
    int inserted = -1;
    int best_fit_size = memory_size;
    for (int i = 0; i < freelist_size && inserted == -1; i++)
    {   
        printf("Block Size: %d\n", freelist[i].size);
        printf("Process Memory: %d\n", new_p.memory);
        printf("BFS: %d\n", best_fit_size);
        if (freelist[i].size >= new_p.memory && freelist[i].size <= best_fit_size)
        {
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
        if (plist_size == plist_max)
        {
            plist_max *= 2;
            plist = realloc(plist, plist_max * sizeof(struct process));
        }
        new_p.start = freelist[inserted].start;
        freelist[inserted].start += new_p.memory + 1;
        freelist[inserted].size -= new_p.memory;
        plist[plist_size] = new_p;
        plist_size++;
        printf("Successfully allocated %d to Process %s\n", new_p.memory, new_p.name);
    }
}
void release(char *name)
{
    if (plist_size > 0)
    {
        int found = 0;
        for (int i = 0; i < plist_size || found == 0; i++)
        {
            if (strcmp(name, plist[i].name) == 0)
            {
                found = 1;
                int rel_p_end = plist[i].start + plist[i].memory;
                for (int k = 0; k < freelist_size; k++)
                {
                    // short circuit k > 0 so this doesnt happen during first loop
                    // if release process has free block on left and right
                    //
                    if (k > 0 && freelist[k].start == rel_p_end && freelist[k - 1].start+freelist[k - 1].size == plist[i].start)
                    {
                        struct block temp;
                        temp.start = freelist[k-1].start;
                        temp.size = freelist[k-1].size + plist[i].memory + freelist[k].size;
                    }
                    if (freelist[k].start == rel_p_end)
                    {
                        freelist[k].start -= plist[i].memory;
                        freelist[k].size += plist[i].memory;
                    }
                }
                for (int k = i + 1; k < plist_size; k++)
                {
                    plist[k - 1] = plist[k];
                }
                plist_size--;
            }
        }
        if (found == 0)
        {
            printf("There is no process running by that name.\n");
        }
        else
        {
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
    for (int i = 0; i < plist_size; i++)
    {
    }
}
void main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    char input[41];
    char *command;
    char *p_name;
    int p_size;
    memory_size = strtol(argv[1], NULL, 10);
    freelist = malloc(freelist_max * sizeof(struct block));
    plist = malloc(plist_max * sizeof(struct process));
    freelist[0].start = 0;
    freelist[0].size = memory_size;
    freelist_size++;
    do
    {
        qsort(freelist, freelist_size, sizeof(struct block), comparef);
        printf("command>");
        fgets(&input, 40, stdin);
        command = strtok(input, " \n");
        if (strcmp("RQ", command) == 0)
        {
            printf("Doing: RQ\n");
            p_name = strtok(NULL, " \n");
            printf("Process Name: %s\n", p_name);
            p_size = strtol(strtok(NULL, " \n"), NULL, 10);
            printf("Process Size: %d\n", p_size);
            allocate(p_name, p_size);
        }
        else if (strcmp("RL", command) == 0)
        {
            printf("Doing: RL\n");
            p_name = strtok(NULL, " \n");
            printf("Process Name: %s\n", p_name);
            release(p_name);
        }
        else if (strcmp("Status", command) == 0)
        {
        }
    } while (strcmp("Exit", command) != 0);
    printf("Exiting\n");
}
