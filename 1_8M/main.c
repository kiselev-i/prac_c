//
//  main.c
//  Lab_1-8-M
//
//  Created by ILYA KISELEV on 12/09/16.
//  Copyright (c) 2016 ILYA KISELEV. All rights reserved.
//

#define BUFER_SIZE 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *readstr(int i);


int main(int argc, const char * argv[]) {

    char *str;
    str = readstr(0);
    printf("%s\n", str);
    return 0;
}

char *readstr(int f)
{
    char *simbol = malloc(1);
    char *str = malloc(BUFER_SIZE);
    char *result = malloc(1);
    long nread = 1;
    int iread = 0;
    int fwrite = 0;
    
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
            result = realloc(result, fwrite+BUFER_SIZE);
            for (iread = 0;iread < BUFER_SIZE; iread++)
            {
                result[fwrite] = str[iread];
                fwrite++;
            }
            iread = 0;
        }
    }
    str[iread] = '\0';
    for (nread = 0;nread <=iread;nread++)
    {
        result[fwrite] = str[nread];
        fwrite++;
    }
    return result;
}