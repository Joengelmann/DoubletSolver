This program solves a doublet puzzle. Given two five letter words, it will find the shortest path from one word to the other by changing one letter at a time, using words that exist in the dictionary knuth.txt. To do this, the program creates a graph object of words whose neighbors are words that differ by exactly one letter. It then runs breadth first search to find the shortest path between the two selected words. I found the graph2.h file online.

To try the code yourself, compile main2.cpp with g++11. I already find the paths between seven different doublets, but try any words you like!
