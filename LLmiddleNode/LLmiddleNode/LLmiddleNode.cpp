// LLmiddleNode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Joseph Bdaro 323-34


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//listNode Class
class listNode {

public:

	//members
	int data;
	listNode* next;

	//default constructor
	listNode() {
		this->data = -9999;
		this->next = NULL;
	}

	//constructor to create new nodes
	listNode(int data, listNode* next) {
		this->data = data;
		this->next = next;
	}

	//print node method that prints a node to a file
	void printNode(listNode* node, ofstream& outFile2) {
		outFile2 << "(" << node->data << ", " << node << ", " << node->next << ", " << node->next->data << ")" <<endl;
	}
	
};




class LinkedList {
	
public:
	//default linkedlist constructor
	LinkedList(listNode* listHead, ifstream& inFile, ofstream& outFile2) {
		if (inFile.is_open())
		{
			int dataParsed;
			//iterates through the file to insert data to LL
			while (inFile >> dataParsed)
			{
				listNode* newNode = new listNode(dataParsed, NULL);
				listInsert(listHead, newNode);
				printList(listHead, outFile2);
			}
		}
	}

	//this method inserts nodes
	void listInsert(listNode* listHead, listNode* newNode) {
		listNode* spot = findSpot(listHead, newNode);
		newNode->next = spot->next;
		spot->next = newNode;

	}
	//finds the spot in the LL to insert the node
	listNode* findSpot(listNode* listHead, listNode* newNode) {
		listNode* spot = listHead;
		while (spot->next != NULL && spot->next->data < newNode->data) {
			spot = spot->next;	
		}
		return spot;
	}
	//prints the entire LL
	void printList(listNode* listHead, ofstream& outFile2) {
		listNode* iterate = listHead;
		outFile2 << "listHead ->(" << iterate->data << ", " << &iterate << ", " << iterate->next << ", " << iterate->next->data << ")";
		iterate = iterate->next;
		while (iterate->next != NULL) {
			outFile2 << "->(" << iterate->data << ", " << &iterate << ", " << iterate->next << ", " << iterate->next->data <<")";
			iterate = iterate->next;
		}
		outFile2 << endl;
	}
	//finds the middlemost node in the LL
	listNode* findMiddleNode(listNode* listHead, ofstream& outFile2) {
		listNode* walk1 = listHead;
		listNode* walk2 = listHead;
		while (walk2 != NULL && walk2->next != NULL) {
			listHead->printNode(walk1, outFile2);
			walk1 = walk1->next;
			walk2 = walk2->next->next;
		}
		return walk1;
	}


};

int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1, outFile2;
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);

	listNode* headNode = new listNode();
	LinkedList constructLL(headNode, inFile, outFile2);
	listNode* middleNode = constructLL.findMiddleNode(headNode, outFile2);
	headNode->printNode(middleNode, outFile1);
	constructLL.printList(headNode, outFile1);
	inFile.close();
	outFile1.close();
	outFile2.close();
	
}
