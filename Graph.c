#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
FILE *out;

typedef struct Graph {
    int order;
    int size;
    int source;
    ListRef *adj; /*List of neghboring verticies*/
    char *color;
    int *par; /*Parent*/
    int *d; /*Discovery*/
    int *f; /*Finish Time*/

} Graph;

/*** Constructors-Destructors ***/

GraphRef newGraph(int n) {


    GraphRef G = malloc(sizeof (Graph));
    G->adj = calloc(n + 1, sizeof (ListRef));
    G->color = calloc(n + 1, sizeof (char));
    G->par = calloc(n + 1, sizeof (int));
    G->d = calloc(n + 1, sizeof (int));
    G->f = calloc(n + 1, sizeof (int));

    int i;
    for (i = 1; i <= n; i++) { /*for each vertex, do this: */
        G->adj[i] = newList();
        G->color[i] = white;
        G->d[i] = UNDEF;
        G->f[i] = UNDEF;
        G->par[i] = NIL;
    }
    G->size = 0;
    G->order = n;
    G->source = NIL;

    return G;
}

/*
 *  freeGraph
 *  Frees all heap memory associated with the GraphRef *pG.  Sets *pG to NULL. 
 */
void freeGraph(GraphRef *pG) {

    int i;
    if (pG != NULL && *pG != NULL) {
        for (i = 1; i <= (*pG)->order; i++)
            freeList(&(*pG)->adj[i]);
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->par);
    free((*pG)->d);
    free((*pG)->f);
    free(*pG);
    *pG = NULL;

}

/*** Access functions ***/

/*returns int value of # of vertices*/
int getOrder(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getOrder() on NULL GraphRef\n");
        exit(1);
    }

    return (G->order);
}

/*returns int value of # of edges   */
int getSize(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getSize() on NULL GraphRef\n");
        exit(1);
    }
    return (G->size);
}

/*returns int source vertex value*/
int getSource(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getSource() on NULL GraphRef\n");
        exit(1);
    }
    return (G->source);
}

/*returns parent of u'th element in the parent array*/
int getParent(GraphRef G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getParent() on NULL GraphRef\n");
        exit(1);
    }
    if (!(((1 <= u) && (u <= G->order)) && (G->order == getOrder(G)))) {
        printf("Graph Error: calling getParent() on incorrect vertices\n");
        exit(1);
    }
    return (G->par[u]);
}

/*returns int discover vertex value*/
int getDiscover(GraphRef G, int u) {
    /* Pre: 1<=u<=n=getOrder(G) */
    if (!(1 <= u) && (u <= G->order)) {
        printf("Graph Error: calling getParent() on incorrect vertices\n");
        exit(1);
    }
    return (G->d[u]);
}

/*returns int finish vertex value*/
int getFinish(GraphRef G, int u) {
    /* Pre: 1<=u<=n=getOrder(G) */

    return (G->f[u]);
}

/* Manipulation procedures */
void visit(GraphRef G, int u, int *time_ptr, ListRef Adj, ListRef S) {
    int i, v;
    G->color[u] = grey;
    *time_ptr = *time_ptr + 1;
    G->d[u] = *time_ptr;
    for (i = 0; i < getLength(Adj); i++) {
        moveTo(Adj, i);
        v = getCurrent(Adj);
        /*printf("outLoop(visit) v: %d \n", v);*/
        if (G->color[v] == white) {
            /* printf("InnerLoop(visit) v: %d \n", v);*/
            G->par[v] = u;
            visit(G, v, time_ptr, G->adj[v], S);
        }
    }
    G->color[u] = black;
    insertFront(S, u);
    *time_ptr = *time_ptr + 1;
    G->f[u] = *time_ptr;
    /*printf(">>> u: %d, Discovery: %d, Finish: %d, Time: %d<<< \n", u, G->d[u], G->f[u], *time_ptr);*/
}

void DFS(GraphRef G, ListRef S) {
    if (!(getLength(S) == getOrder(G))) {
        printf("Graph Error: passing list with length not equal to number of vertices\n");
        exit(1);
    }
    int i, u;
    for (i = 0; i < getLength(S); i++) {
        moveTo(S, i);
        u = getCurrent(S);
        G->color[u] = white;
        G->par[u] = NIL;
        G->d[u] = UNDEF;
        G->f[u] = UNDEF;
    }
    int time = 0;
    int *time_ptr;
    time_ptr = &time;

    for (i = 0; i < getLength(S); i++) {
        moveTo(S, i);
        u = getCurrent(S);
        /*   printf("InnerLoopDFS u: %d, i: %d \n", u, i);*/
        if (G->color[u] == white) {
            visit(G, u, time_ptr, G->adj[u], S);
        }
    }
    for (i = 0; i < G->order; i++) {
        deleteBack(S);
    }
}

/*makes restores graph to original state*/
void makeNull(GraphRef G) {
    int i;
    for (i = 1; i <= G->order; i++) {
        makeEmpty(G->adj[i]);
        G->color[i] = white;
        G->d[i] = UNDEF;
        G->f[i] = UNDEF;
        G->par[i] = NIL;
    }
    G->size = 0;
    G->source = NIL;


}

/*int u is added to the adjacency List of v and v to the adj List of U*/

/*Range 1 to getOrder()*/
void addArc(GraphRef G, int u, int v) {

    if (u > (getOrder(G)) || v > (getOrder(G))) {
        printf("Graph Error: adding an illegal edge. %d > %d || %d > %d\n", u, getOrder(G), v, getOrder(G));
        exit(1);
    }
    if (u > 0 && u <= G->order) {
        insertBack(G->adj[u], v);
        G->size++;
    }
}

/*** Other operations ***/

GraphRef transpose(GraphRef G) {
    GraphRef T = newGraph(G->order);
    int i, s, tmp;
    for (i = 1; i <= G->order; i++) {
        /*printf("Vertex: %d \n", i);*/
        for (s = 0; s < getLength(G->adj[i]); s++) {
            moveTo(G->adj[i], s);
            tmp = getCurrent(G->adj[i]);
            insertBack(T->adj[tmp], i);
            /*printf("Inner Loop: Position: %d. Insert %d into T->Adj[%d] \n", s, i, tmp);*/
        }
    }

    return T;
}

GraphRef copyGraph(GraphRef G) {
    GraphRef C = newGraph(G->order);
    int i, s, tmp;
    for (i = 1; i <= G->order; i++) {
        /*printf("\nVertex: %d \n", i);*/
        for (s = 0; s < getLength(G->adj[i]); s++) {
            moveTo(G->adj[i], s);
            tmp = getCurrent(G->adj[i]);

            insertBack(C->adj[i], tmp);


        }
        C->color[i] = G->color[i];
        C->d[i] = G->d[i];
        C->f[i] = G->f[i];
        C->par[i] = G->par[i];
        /*printf("Inner Loop(%d): C: %d-%d, D: %d-%d, F: %d-%d, P: %d-%d \n", i, C->color[s], G->color[s], C->d[s], G->d[s], C->f[s], G->f[s], C->par[s], G->par[s]);*/

    }
    return C;
}

void printGraph(FILE* out, GraphRef G) {
    int i;
    for (i = 1; i <= G->order; i++) {

        if (i == 1) {
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);

        } else {
            fprintf(out, "\n");
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);
        }
    }
}


