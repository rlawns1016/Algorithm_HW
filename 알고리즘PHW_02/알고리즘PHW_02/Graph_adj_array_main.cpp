
#include "Graph_adj_array.h"
#include "Graph_adj_array_global.h"
#include "Graph_adj_array_function.h"
#include <queue>

void main ( void ) {
	int    src;
	int    Tnum; // # of test cases
	int    Memsize_for_array;
	clock_t start, finish;
	double cmpt;

	scanf_s("%d", &Tnum);

	for (int t = 0; t < Tnum; t++ ) {
		scanf_s("%d %d %d", &Vnum, &Enum, &src);
		V = new vertex [Vnum];
		E = new edge [Enum];
		if ( V == NULL || E == NULL ) {
			Error_Exit("Memory Allocation Error");
		}
		Memsize_for_array = Vnum * sizeof(vertex) + Enum * sizeof(edge);
		if ( Used_Memory_for_array < Memsize_for_array ) {
			Used_Memory_for_array = Memsize_for_array;
		}
		Read_Graph_adj_array( );
		// Do DFS
		start = clock();

	    for ( int i = 0; i < Vnum; i++ ) {
		  V[i].flag = false;  // clear flag
	    }
 	    for ( int i = 0; i < Enum; i++ ) {
		  E[i].flag = false;  // clear flag
	    }
		Tree_cost = 0;
		DFS_Tree_adj_array (src);

		finish = clock();
		cmpt = ((double)(finish - start)) / (double)CLK_TCK;

        if (Tree_Check_adj_array( ) == 0) { // check if spanning tree
			if ( t != 0 ) printf("\n");
			printf("**T%d (DFS) (V = %d, E = %d, time = %.3f sec) ERROR: NOT A TREE!!", 
				t+1, Vnum, Enum, cmpt);
		}
		else {
			if ( t != 0 ) printf("\n");
			printf("**T%d (DFS) (V = %d, E = %d, time = %.3f sec) Tree Cost = %d", 
				t+1, Vnum, Enum, cmpt, Tree_cost);
		}
		delete V; delete E;
	}
	//printf("Tree COst = %d\n", Tree_cost);
	printf("\nTotal memory used = %d", Used_Memory_for_array);
	getchar();
	getchar();
}

void Error_Exit ( char *s ) {
  printf("%s\n", s);
  exit(-1);
}