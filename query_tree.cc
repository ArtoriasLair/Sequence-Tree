/****************************************************************************************** 
File:         query_tree.cc
Author:       Arthur Lai
Date Created: October 2018

Description:
This program parses a database file 'rebase.txt' containing a list of enzymes 
and their corresponding recognition sequences, and distributes them into Binary Search 
Trees or AVL Trees for effective queries. An input file containing requested sequences 
is also parsed, returning the corresponding acronyms for each sequence. 

******************************************************************************************/

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
// You will have to add #include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string getAcronym(string &line);

bool getNextSequence(string &line, string &seq);

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();

  //DB parser
  ifstream readDB;
  readDB.open(db_filename);
  string line;

  //skip 10 lines (title of rebase210.txt)
  for (int i = 0; i < 10; i++){
    getline(readDB,line);
  }

  //parse and insert into tree
  while(getline(readDB,line)){
    if (line == "") //for blank lines near EOF
      break;

    //capture acro
    string acro = getAcronym(line);

    string sequence;
    while(getNextSequence(line,sequence)){
      SequenceMap newSM(sequence,acro);
      a_tree.insert(newSM);
    }
  }

  readDB.close();

  cout << endl;

  //./query_tree rebase210.txt AVL < filename.txt
  //                                  ^reads non-hardcoded file
  while(getline(cin,line)){
    if (line == "")
      break;

    string blank;

    SequenceMap newSeq(line,blank);
    a_tree.find(newSeq);

  }


}

}  // namespace


string getAcronym(string &line){ //extract acronym from line

  string acro;

  //capture enzyme acronym
  int i = 0;
  while(line[i] != '/'){
     acro += line[i];
     i++;
  }

  //trunkate line
  string tempLine = line.substr(i+1,line.size()-1);
  line = tempLine;

  return acro;
}

bool getNextSequence(string &line, string &seq){ //extract all sequences from line

  int i = 0;
  string tempSeq;

  if(line[i] == '/'){ //no other sequence to capture
    return false;
  }
  else {
    while(line[i] != '/'){ //parse sequence
      tempSeq += line[i];
      i++;
    }
    seq = tempSeq;

    //trunkate line
    string tempLine = line.substr(i+1,line.size()-1);
    line = tempLine;

    return true;
  }


}

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    //BinarySearchTree<int> a_tree;
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    //AvlTree<int> a_tree;
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
