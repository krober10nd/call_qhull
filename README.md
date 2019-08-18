# call_qhull
Minimal example to call qhull to output facet table of Delaunay triangulation (lower hull of convex hull of point set lifted into an extra dimension). NOTE: you can change the code to output the Vornoi facets by changing the "lowerhull" to "upperhull" when printing the facets. 

# Usage
1. Build and install qhull (use cmake).
2. In call_qhull.c, change "numpoints" and "DIM" to fit your the number of points and the dimension in your text file "points.txt". 
3. Compile gcc call_qhull.c -L lib/ -lqhullstatic_r -I include/ -o call_qhull.x
