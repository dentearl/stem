stem
4 May 2010
Dent Earl, dearl@soe.ucsc.edu
BME Dept, School of Engineering, UCSC

" stem() from the R project, now on the command line. "

stem is a C program for creating stem and leaf plots 
on the command line (see wikipedia:Stemplot). It is 
a complete port of the R stem() function from the R 
project and as such is offered here under GPL 2.

License
stem software is provided under the GNU GPL version 2.

Example
[dearl@machine demo]$ cat testData.txt  | stem

  The decimal point is at the |

  -3 | 0
  -2 | 6100
  -1 | 965443321000
  -0 | 9888777777666555555444333222211110000
   0 | 0011111122333444555556677788888899
   1 | 01123566678
   2 | 0

Details
[dearl@machine demo]$ stem --help
  stem an R-like stem and leaf plot.
  Version 0.1.3
  4 May 2011
    dent earl, dearl (a) soe ucsc edu

  R : A Computer Language for Statistical Data Analysis               
  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka           
  Copyright (C) 1997-2000   Robert Gentleman, Ross Ihaka and the      
                            R Development Core Team                   
**********************************************************************
  Copyright (c) May 2010    Dent A. Earl, UCSC                        
  Ported into a stand alone bin by Dent A. Earl dearl (a) soe ucsc edu
  ALL BUGS SHOULD BE REPORTED TO DENT A. EARL, not the R dev team.    
  http://users.soe.ucsc.edu/~dearl/                                   
**********************************************************************
                                                                      
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or   
  (at your option) any later version.                                 
                                                                      
  This program is distributed in the hope that it will be useful,     
  but WITHOUT ANY WARRANTY; without even the implied warranty of      
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       
  GNU General Public License for more details.                        
                                                                      
  You should have received a copy of the GNU General Public License   
  along with this program; if not, a copy is available at             
  http://www.r-project.org/Licenses/                                  
                                                                      
  'stem' produces a stem-and-leaf plot of the values in STDIN. The    
  parameter 'scale' can be used to expand the scale of the plot.  A   
  value of 'scale=2' will cause the plot to be roughly twice as long  
  as the default.                                                     

  stdin: one number on each line of input, no puntuation or text.     
  --scale: This controls the plot length.
  --width: The desired width of plot.
  --atom: a tolerance.
  --sorted: a flag that indicates the input data is already sorted in
            ascending order. Use this for a speedup on large inputs.  

  References:
     Becker, R. A., Chambers, J. M. and Wilks, A. R. (1988) _The New S
     Language_.  Wadsworth & Brooks/Cole.
