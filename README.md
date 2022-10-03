# golphGraph

This is a submission for the JGraph Lab for COSC494. The purpose of this project is to
write a program that creates a jgraph file that produces a graph with interesting visuals.
My program is an implementation of the example on the lab writeup, "Will this help me next week on DraftKings?"

Files:

- golfgraph.cpp
  This is the main program that generates the jgraph file "jtest.jgr" and runs the
  Jgraph program to create the graph as a .png file called "golf_stats.jpg".
  
- golfer.eps
  This file is used to create a golfer graphic that is used to denote the
  total value for each golfer.
  
- golftest.txt
  This is an example input file for the golfgraph program
  
- makefile
  A makefile for the program. type "make" to make. type "make run" to make
  and run the program with the "golftest.txt" file as input.
  
Compilation and input:

  make with the makefile, type "make run" to compile and run the program with
  example input in "golftest.txt".
  
  Otherwise, the program takes a single text file as input. This text file should be
  list the golfer's name first, followed by the stats in this order:
    - (Golfer's first and last name)  (off-the-tee stat)
    - (Golfer's first and last name)  (approach-the-green stat)
    - (Golfer's first and last name)  (arround-the-green stat)
    - (Golfer's first and last name)  (putting stat)
  *see golftest.txt as an example.
  
Output:
  
  The program creates a .jgr file and runs the command to create a .jpg of the graph.
  Each graph created will contain at most five golfers. If more than five golfers are
  listed in the input file, it will create a new graph.
  
  Here is an example with five golfers:
  
![Screen Shot 2022-10-03 at 7 09 14 PM](https://user-images.githubusercontent.com/77810642/193701672-94629e35-b488-4978-adfa-8b6fb651eb6d.png)
  
  Here is an example with more than five golfers:
  
![Screen Shot 2022-10-03 at 7 10 11 PM](https://user-images.githubusercontent.com/77810642/193701785-cd177e0d-da6c-4ae8-82f3-d0dca79a639a.png)
