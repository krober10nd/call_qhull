#include "libqhull_r/qhull_ra.h"

/*-------------------------------------------------
-internal function prototypes
*/
void print_facets(qhT *qh);
int read_points(coordT *points, int numpoints, int DIM);

/*-------------------------------------------------
-print_facets
*/
void print_facets(qhT *qh) {

    facetT *facet; 
    vertexT *vertex, **vertexp; 

    FORALLfacets { 
        if( !facet->upperdelaunay) {
           // prints number of vertices per facet
          //printf ("%d", qh_setsize (qh, facet->vertices) );
          FOREACHvertex_(facet->vertices)
              printf(" %d", qh_pointid (qh, vertex->point) );
          printf("\n");
        }
    }
}


/*--------------------------------------------------
 -read_points
*/
int read_points(coordT *points, int numpoints, int dim) {

  int i;
  FILE *fptr;

  fptr = fopen("points.txt","r");
  if(fptr == NULL)
    {
    printf("Error!! Cannot open file containing points \n" );
    return 1;
    }
  else
    {
      printf("File opened successfully :) \n");
      
      // read them in
      if (dim == 2) {
        // 2d
        for ( i=0; i<numpoints; i++)
           {
            fscanf(fptr,"%lf %lf",&points[i*2 ],&points[i*2 + 1]);
           }
      } else {
        // 3d
        for ( i=0; i<numpoints; i++)
           {
            fscanf(fptr,"%lf %lf %lf",&points[i*3 ],&points[i*3 + 1],&points[i*3+2]);
           }
      }
    }
  return 0;
}



int main(int argc, char *argv[]) {

  // lets assume we get this information from another program
  int DIM=3;                /* dimension of points */
  int numpoints=100;    /* number of points */

  boolT ismalloc= False;    /* True if qhull should free points in qh_freeqhull() or reallocation */
  char flags[250];          /* option flags for qhull, see qh-quick.htm */
  FILE *outfile= NULL;      /* output from qh_produce_output()
                               use NULL to skip qh_produce_output() */
  FILE *errfile= stderr;    /* error messages from qhull code */
  int exitcode0,exitcode;   /* 0 if no error from qhull */
  facetT *facet;            /* set by FORALLfacets */
  int curlong, totlong;     /* memory remaining after qh_memfreeshort, used if !qh_NOmem  */
  int i;

  QHULL_LIB_CHECK

  {
    coordT points[DIM*numpoints]; /* array of coordinates for each point */

    qhT qh_qh;                     /* Create an instance of Qhull */
    qhT *qh= &qh_qh;
    qh_zero(qh, errfile);

    sprintf(flags, "qhull d Tcv i");

    exitcode0=read_points(points, numpoints, DIM);

    if (exitcode0)
      return exitcode0;

    fflush(NULL);
    exitcode= qh_new_qhull(qh, DIM, numpoints, points, ismalloc,
                    flags, outfile, errfile);
    fflush(NULL);

    if (!exitcode)
      // this could go to an array instead of file IO 
      print_facets(qh);

    qh_freeqhull(qh, !qh_ALL);                 /* free long memory */
    qh_memfreeshort(qh, &curlong, &totlong);  /* free short memory and memory allocator */
    if (curlong || totlong)
        fprintf(errfile, "qhull internal warnin: did not free %d bytes of long memory (%d pieces)\n", totlong, curlong);
    /* Exiting the block frees qh_qh */
  }

    
return exitcode;
} /* main */

