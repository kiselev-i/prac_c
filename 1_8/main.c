//
//  main.c
//  Lab_1-8
//
//  Created by ILYA KISELEV on 12/09/16.
//  Copyright (c) 2016 ILYA KISELEV. All rights reserved.
//

#define BUFER_SIZE 4
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"


typedef struct Tnode Tnode;
typedef struct Tlist Tlist;


struct Tnode{
    char data[BUFER_SIZE];
    Tnode *next;
};

struct Tlist{
    Tnode *first;
    Tnode *last;
    int count;
};


Tlist *create_list(Tnode *fi);
Tnode *create_node(char *d);
void pushnode(Tlist *list, Tnode *node);
char *list_tochar(Tlist* list);
Tlist *readstr(int f);
void free_list(Tlist *list);


int main(int argc, const char * argv[]) {
    Tlist *list = readstr(0);
    char *ch = list_tochar(list);
    printf("String = %s\n", ch);
    
    free(ch);
    free_list(list);
    free(list);
    return 0;
}

Tnode *create_node(char *d)
{
    if (d == NULL)
        return NULL;
    Tnode *bu = malloc(sizeof(Tnode));
    for (int i = 0; i < BUFER_SIZE; i++)
    {
        bu->data[i] = d[i];
        if (d[i] == '\0')
            return bu;
    }
    return bu;
}

Tlist *create_list(Tnode *fi)
{
    Tlist *bu = malloc(sizeof(Tlist));
    bu->first = fi;
    bu->last = fi;
    (bu->first == NULL) ? (bu->count = 0) : (bu->count = 1);
    return bu;
}

void pushnode(Tlist *list, Tnode *node)
{
    if (list == NULL)
    {
        printf("list is NULL!\n");
        return;
    }
    if (node == NULL)
    {
        printf("node is NULL!\n");
        return;
    }
    if (list->count == 0)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        list->last = node;
        
    }
    list->count += 1;
}


Tlist *readstr(int f)
{
    char *simbol = malloc(1);
    char *str = malloc(BUFER_SIZE);
    Tlist *list = create_list(NULL);
    int nread = 1;
    int iread = 0;
    while (nread == 1)
    {
        nread = read(f, simbol, 1);
        if (nread != 1)
        {
            printf("EoF!\n");
            break;
            
        }
        if (simbol[0] == '\n')
            break;
        str[iread] = simbol[0];
        iread++;
        if (iread == BUFER_SIZE)
        {
            pushnode(list, create_node(str));
            iread = 0;
        }
    }
    str[iread] = '\0';
    pushnode(list, create_node(str));
    
    return list;
}

char *list_tochar(Tlist* list)
{
    char *buc;
    Tnode *bun = list->first;
    long n = 0;
    int i;
    int index_0;
    
    for (index_0 = 0;index_0 < BUFER_SIZE; index_0++)
    {
        if (list->last->data[index_0] == '\0')
            break;
    }
    index_0 +=1;
    buc = malloc((list->count*BUFER_SIZE) - (BUFER_SIZE - index_0));
    
    while (bun->next != NULL)
    {
        for(i = 0; i < BUFER_SIZE; i++)
        {
            buc[n] = bun->data[i];
            n++;
        }
        bun = bun->next;
    }
    for (i = 0; i < index_0; i++)
    {
        buc[n] = bun->data[i];
        n++;
    }
    return buc;
}

void free_list(Tlist *list)
{
    Tnode *noww = list->first;
    Tnode *next = noww->next;
    while (next != NULL)
    {
        free(noww->data);
        noww = NULL;
        noww = next;
        next = noww->next;
    }
    free(noww->data);
    noww = NULL;
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
}
