/******************************************************************************************
File: 			SequenceMap.h
Author: 		Arthur Lai
Date Created:		October 2018

Description:
This file contains the implementation for a custom structure called "SequenceMap" which
stores an enzyme recogniition sequence and their corresponding acronyms for said sequence.
This structure is also made to handle merges, sorts, and comparisons. 

******************************************************************************************/

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include "dsexceptions.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std; 

class SequenceMap {
private:
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;
public:
	SequenceMap(){

	}

	~SequenceMap() = default;									//DESTRUCTOR
	SequenceMap(const SequenceMap &rhs) = default;				//Copy Constructor
	SequenceMap(SequenceMap &&rhs) = default;					//Move Constructor
	SequenceMap &operator=(const SequenceMap &rhs) = default;	//Copy Assignment
	SequenceMap &operator=(SequenceMap &&rhs) = default;		//Move Assignment

	//A
	SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
		//construct a SequenceMap from 2 strings
		//vector enzyme_acronyms_ <- an_enz_acro
		
		enzyme_acronyms_.push_back(an_enz_acro);	//add element to acronym vector
		recognition_sequence_ = a_rec_seq;			//add sequence name to database

	}

	//B
	bool operator<(const SequenceMap &rhs) const {
		//string comparison
		return recognition_sequence_ < rhs.recognition_sequence_;
	}

	//C; for printTree()
	friend ostream &operator<<(ostream &out, const SequenceMap &seq){

		//print Sequence
//		out << "Sequence: " << seq.recognition_sequence_;

		//print Acronyms
		for (int i = 0; i < seq.enzyme_acronyms_.size(); i++)
			out << seq.enzyme_acronyms_[i] << " ";

		return out;
	}

	//D
	void Merge(const SequenceMap &other_sequence){
		//assumes current recognition_sequence == other_sequence.recognition_sequence;
		//merge other_sequence.acronym with current object's enzyme_acronym
		//merge is automatically called 
		for(int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
			enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
		}
	}

	//for comparing sequences
	bool operator==(const SequenceMap &rhs) const {
		return rhs.recognition_sequence_ == recognition_sequence_;
	}

};


#endif
