/****************************************************************************************** 
File:         test_tree.cc
Author:       Arthur Lai
Date Created: October 2018

Description:
This program parses a database 'rebase210.txt' to construct a AVL or BST search tree
of a enzyme recognition sequences and their corresponding acronyms. Then, it returns 
information of said tree regarding its average depth, average depth ratio. It then
parses 'sequences.txt' containing sequences to be removed and then returns information
of the edited tree after removals.

******************************************************************************************/

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
// You will have to add #include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

string getAcronym(string &line);

bool getNextSequence(string &line, string &seq);

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)

  //DB parser
  ifstream readDB;
  readDB.open(db_filename);
  string line;
  const string blank;

  //skip 10 lines (title of rebase.txt)
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

  readDB.close(); //DB parser


  //2) print number of nodes in tree
  int nodeTotal = a_tree.numOfNodes();
  cout << endl;
  cout << "2:\t" << nodeTotal << endl;

  //3a) print average depth
  int avgDepth = a_tree.findAvgDepth();
  cout << "3a:\t" << avgDepth << endl;

  //3b) print ratio of average depth to log n
  cout << "3b:\t" << avgDepth/log(nodeTotal) << endl;

  //4a) print total number of strings found
  int count = 0;
  ifstream readSeq;
  readSeq.open(seq_filename);
  while(getline(readSeq,line)){
    count++;
  }
  readSeq.close();
  cout << "4a:\t" << count << endl;

  //4b) Print average number of recursion calls
  cout << "4b:\t" << endl;

  //5a) remove every sequence in sequences.txt from the tree
  readSeq.open(seq_filename);
  while(getline(readSeq,line)){
    SequenceMap rmSeq(line,blank);
    a_tree.remove(rmSeq);
  }
  readSeq.close();
  cout << "5a:\t" << a_tree.findRemoveCount() << endl;

  //5b) print average number of calls
  cout << "5b:\t" << endl;

  //6a) print UPDATED number of nodes in tree
  nodeTotal = a_tree.numOfNodes();
  cout << "6a:\t" << nodeTotal << endl;

  //6b) print UPDATED average depth
  avgDepth = a_tree.findAvgDepth();
  cout << "6b:\t" << avgDepth << endl; 

  //6c) print UPDATED ratio of average depth to log n
  cout << "6c:\t" << avgDepth/log(nodeTotal) << endl;

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
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
//    BinarySearchTree<int> a_tree;
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
//    AvlTree<int> a_tree;
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
