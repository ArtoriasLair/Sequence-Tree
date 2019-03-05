## Project: Sequence-Tree
Author: Arthur Lai  
Date: October 2018

Description: An academic project on AVL and BST trees using enzyme sequences.


To Compile:<br>
make all

To Execute:<br>
./query_tree <database file name> <flag> < <test file>
./query_tree rebase210.txt AVL < filename.txt
./query_tree rebase210.txt BST < filename.txt
  
./test_tree <database file name> <queries file name> <flag>
./test_tree rebase210.txt sequences.txt AVL
./test_tree rebase210.txt sequences.txt BST
