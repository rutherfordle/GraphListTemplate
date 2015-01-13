/* 
 * Rutherford Le
 * Rle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 250

int main(int argc, char** argv) {
    FILE *in, *out;
    char line[MAX_LEN];

    char* token;

    /* check command line for correct number of arguments */
    if (argc != 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        exit(1);
    }

    /* open files for reading and writing */
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to write file %s for writing\n", argv[2]);
        exit(1);
    }

    /* initializing */
    int count = 0;
    int n = 0;
    int tmp = 0;
    int u;
    int v;
    
    GraphRef G;
    count++;

    int vert = 0;
    if (count == 1) {
        fgets(line, MAX_LEN, in);
        /*Creates stores graph vertex count*/
        token = strtok(line, " ");
        vert = atoi(token);
    }

    G = newGraph(vert);

    while ((vert != 0) && (fgets(line, MAX_LEN, in) != NULL)) {
        count++;
        n = 0;
        token = strtok(line, " ");

        /*Figures out the values of (u,v)*/
        while ((token != NULL)) {
            tmp = atoi(token);
            if (n == 0) {
                u = tmp;
            } else if (n == 1) {
                v = tmp;
            }
            n++;
            token = strtok(NULL, " \n");
        }

        /*If (0,0), exit protocol*/
        if ((v == 0) && (u == 0)) {
            /*sets phase 1 over*/
            break;
        }
        addArc(G, u, v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);


    /*Creates List for Stack use in DFS(G); */
    ListRef L = newList();
    GraphRef GT = transpose(G);

    int i;
    for (i = 1; i <= getOrder(G); i++) {
        insertBack(L, i);
    }

    DFS(G, L);
    ListRef Lcpy = copyList(L);

    DFS(GT, Lcpy);
    ListRef Lgcc = copyList(Lcpy);
    
  
    /* Number of Strong Connected Components computed.*/
    i = 0;
    int ssc = 0;
    int p, q, len;
    int Ltmp, Lcpytmp;
    while (!isEmpty(Lgcc)) {
        moveTo(L, i);
        Ltmp = getCurrent(L);
        for (p = 0; p < getLength(Lgcc); p++) {
            moveTo(Lgcc, p);
            Lcpytmp = getCurrent(Lgcc);
            if (Ltmp == Lcpytmp) {
                ssc++;
                len = getLength(Lgcc);
                for (q = p; q < len; q++) {
                    deleteBack(Lgcc);
                }
            }
        }
        i++;
    }

    /* Strong Connected Components List printed*/
    fprintf(out, "\n\nG contains %d strongly connected components:", ssc);
    i = 0;
    ssc = 0;
    while (!isEmpty(Lcpy)) {
        moveTo(L, i);
        Ltmp = getCurrent(L);
        for (p = 0; p < getLength(Lcpy); p++) {
            moveTo(Lcpy, p);
            Lcpytmp = getCurrent(Lcpy);
            /*printf("test2(%d): L: %d, Lgcc: %d\n", p, Ltmp, Lcpytmp);*/
            if (Ltmp == Lcpytmp) {
                len = getLength(Lcpy);
                ssc++;
                fprintf(out, "\nComponent %d: ", ssc);
                for (q = p; q < len; q++) {
                    moveTo(Lcpy, p);
                    Lcpytmp = getCurrent(Lcpy);
                    if (q == len - 1) {
                        fprintf(out, "%d", Lcpytmp);
                    } else {
                        fprintf(out, "%d ", Lcpytmp);
                    }
                    deleteCurrent(Lcpy);
                }
            }
        }
        i++;
    }

    fprintf(out, "\n");

    freeList(&Lcpy);
    freeList(&Lgcc);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&GT);

    /* close files */
    fclose(in);
    fclose(out);

    return (0);
}

