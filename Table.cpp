#include <iostream>
#include <cstring>
#include <array>
#include "Node.h"
#include "Table.h"

Table::Table() {
  modulus = 100;
  array = new Node*[100];
  for (int i = 0; i < 100; i++) {
    array[i] = NULL;
  }
  newID = 1123;
}

Table::~Table() {
  modulus = 0;
  newID = 0;
  for (int i = 0; i < sizeof(array); i++) {
    array[i] = NULL;
  }
}

void Table::insert(Node* student) {
  student->next = NULL;
  //get the index number
  int index = student->ID%modulus;
  //check for existing ID and increment ID if exists
  if (array[index] != NULL) {
    Node* currentNode = array[index];
    while (currentNode != NULL) {
      if (currentNode->ID == student->ID) {
	student->ID = student->ID + 1;
	insert(student);
	return;
      }
      currentNode = currentNode->next;
    }
  }
  //try to insert index
  if (array[index] == NULL) {
    array[index] = student;
    return;
  }
  else {
    int count = 1;
    Node* currentNode = array[index];
    while (currentNode->next != NULL && count != 3) {
      currentNode = currentNode->next;
      count++;
    }
    if (count >= 3) {
      //get all students into a node array
      Node** studentArray = new Node*[3*modulus];
      int count = 0;
      
      for (int i = 0; i < modulus; i++) {
	if (array[i] != NULL) {
	  
	  studentArray[count] = array[i];
	  count++;
	  Node* currentNode = array[i];
	  while (currentNode->next != NULL) {
	    studentArray[count] = currentNode->next;
	    count++;
	    currentNode = currentNode->next;
	  }
	}
      }
      studentArray[count] = student;
      //change modulus and array size
      
      array = new Node*[2*modulus];
      int arraySize = modulus*3;
      modulus = modulus*2;
      //re-insert all students


      for (int i = 0; i < count+1; i++) {
	if (studentArray[i] != NULL) {
	  if (studentArray[i]->firstName != NULL) {
	    insert(studentArray[i]);
	  }
	}

      }

      return;
    }
    else {
      currentNode->next = student;
      return;
    }
  }
}

void Table::remove(int ID) {
  //get the index of the ID
  int index = ID%modulus;
  //search for ID in that index
  Node* currentNode = array[index];
  if (currentNode != NULL) {
    if (currentNode->ID == ID) {
      array[index] = currentNode->next;
      currentNode = NULL;
      return;
    }
    while (currentNode->next != NULL) {
      if (currentNode->next->ID == ID) {
	currentNode->next = currentNode->next->next;
	return;
      }
      currentNode = currentNode->next;
    }
  }
  cout << "this ID could not be found." << endl;
}

void Table::print() {
  for (int i = 0; i < modulus; i++) {
    if (array[i] != NULL) {
      if (array[i]->firstName != NULL) {
      cout << i << " ";
      Node* currentNode = array[i];
      while (currentNode != NULL) {
	cout << "-> " << currentNode->firstName;
	cout << " " << currentNode->lastName;
	cout << ", " << currentNode->ID;
	cout << ", " << currentNode->GPA << " ";
	currentNode = currentNode->next;
      }
      

      cout << endl;
      }
      } 
  }
}

int Table::getID() {
  newID = newID+20;
  return newID;
}

int Table::checkForID(Node* check) {
  int placement = check->ID%modulus;
  if (array[placement] != NULL) {
    Node* currentNode = array[placement];
    while (currentNode != NULL) {
      if (currentNode->ID == check->ID) {
	return 1;
      }
      currentNode = currentNode->next;
    }
  }
  return 0;
}
