/* 
 * Rutherford Le
 * Rle
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

/*
 * 
 */
int main(int argc, char** argv) {

    FILE *out;
    out = fopen("myGraphTestOut.txt", "w");
    if (out == NULL) {
        printf("Unable to write to file %s \n", argv[1]);
        exit(1);
    }

    GraphRef G = newGraph(8);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);


    
    GraphRef GT = transpose(G);

    ListRef L = newList();
    ListRef LC = newList();
    ListRef LO = newList();
    ListRef LT = newList();

    int i;
    for (i = 1; i <= getOrder(G); i++) {
        insertBack(L, i);
        insertBack(LC, i);
        insertBack(LO, i);
        insertBack(LT, i);
    }

    fprintf(out, "Printing Lists for DFS: ");
    fprintf(out, "\n");
    printList(out, L);
    fprintf(out, "\n");
    printList(out, LC);
    fprintf(out, "\n");
    printList(out, LO);
    fprintf(out, "\n");
    printList(out, LT);
    fprintf(out, "\n");

    DFS(G, L);
    GraphRef GC = copyGraph(G);
    DFS(G, LT);
    fprintf(out, "\nGraph of G: \n");
    printGraph(out, G);



    fprintf(out, "\n");
    fprintf(out, "\nGraph of GC (copy of G): \n");
    printGraph(out, GC);



    fprintf(out, "\n");
    fprintf(out, "\nGraph of GT (transpose of G): \n");
    printGraph(out, GT);
    DFS(GT, LT);


    fprintf(out, "\n");
    fprintf(out, "\nOrig L: ");
    printList(out, LO);

    fprintf(out, "\nDFS L: ");
    printList(out, L);

    fprintf(out, "\nDFS LC: ");
    printList(out, LC);

    fprintf(out, "\nDFS LT: ");
    printList(out, LT);
    fprintf(out, "\n");

    for (i = 1; i <= getOrder(G); i++) {
        fprintf(out, "\nItem: G | GC | GT");
        fprintf(out, "\nVert: %d | %d | %d |", i, i, i);
        fprintf(out, "\nPrnt: %d | %d | %d |", getParent(G, i), getParent(GC, i), getParent(GT, i));
        fprintf(out, "\nDisc: %d | %d | %d |", getDiscover(G, i), getDiscover(GC, i), getDiscover(GT, i));
        fprintf(out, "\nFnsh: %d | %d | %d |", getFinish(G, i), getFinish(GC, i), getFinish(GT, i));
        fprintf(out, "\n");
    }
    freeList(&LC);
    freeList(&LO);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&GT);
    freeGraph(&GC);

    fclose(out);
    return (EXIT_SUCCESS);
}

