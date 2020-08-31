# Interpolition
  This programm counts interpolations. 
  Input parameters are two files
  1) the first file contains points for which interpolation is performed in the following
  format:
    n
    t1 f(t1)
    t2 f(t2)
    ...
    tn f(tn)
    
  2) the second file contains a set of arguments for which you need to find
  interpolated values:
    k
    t1
    t2
    ...
    tk
    
  Output parameters:
  One file with coordinates of interpolated points:
    k
    t1 f (t1)
    t2 f (t2)
    ...
    tk f (tk)
   
  There are three types of interpolation: linear, quadratic, and cubic.
  Interpolation can be switched dynamically while the program is running.
  
  
