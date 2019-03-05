You will use this exact Makefile for your Homework 2. If you need to change it, please consult with me first.

You can compile everything by typing 

make all

You can compile one program individually by just typing make <Program Name>, for example

make query_tree

By typing 

make clean

You delete all .o files and executables.

*Additions by 
Arthur Lai
CSCI 335
Prof. Stammos
Fall 2018
Assignment 2
=========================
Parts complete:
Part 1
Part 2a
Part 2b: (missing 4b & 5b)

Bugs/Issues:
expected output for 5a is 161 but shows 261 instead
expected output for 6a is 404 but shows 304 instead

How to run program:
for part 2a:
make all
./query_tree <database file name> <flag> < <test file>
./query_tree rebase210.txt AVL < filename.txt
./query_tree rebase210.txt BST < filename.txt

for part 2b:
make all
./test_tree <database file name> <queries file name> <flag>
./test_tree rebase210.txt sequences.txt AVL
./test_tree rebase210.txt sequences.txt BST