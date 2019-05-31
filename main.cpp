#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Table.h"

using namespace std;

//FIRST NAMES DOES NOT WORK

int main() {
  Table* hash = new Table();
  bool stillGoing = true;
  //make array of student first and last names
  //get student names file 'first.txt'
  ifstream textFile;
  textFile.open("first.txt");
  if (!textFile) {
    cout << "File Destination Not Found" << endl;
  }
  textFile.seekg(0,textFile.end);
  int length = textFile.tellg();
  textFile.seekg(0,textFile.beg);
  //convert to char array
  char charArray[1000];
  for(int i = 0; i < length;i++) {
    charArray[i] = textFile.get();
  }
  charArray[length] = '\0';
  //convert char array to array of character arrays for each name
  char** firstNames = new char*[100];
  int nameNum = 0;
  //ERROR IN FOR LOOP SOMEWHERE
  for (int i = 0; i < length; i++) {
    char* name = new char[100];
    int count = 0;
    while (isalpha(charArray[i]) && i < length) {
      name[count] = charArray[i];
      i++;
      count++;
    }
    name[count] = '\0';
    firstNames[nameNum] = name;
    nameNum++;
    while (!isalpha(charArray[i+1])) {
      i++;
    }
  }
  //do the same thing for the list of last names
  ifstream textFile2;
  textFile2.open("last.txt");
  textFile2.seekg(0,textFile2.end);
  int length2 = textFile2.tellg();
  textFile2.seekg(0,textFile2.beg);
  //convert to char array
  char charArray2[1000];
  for(int i = 0; i < length2;i++) {
    charArray2[i] = textFile2.get();
  }
  charArray2[length2] = '\0';
  //convert char array to array of character arrays for each name
  char** lastNames = new char*[100];
  nameNum = 0;
  for (int i = 0; i < length2; i++) {
    char* name = new char[100];
    int count = 0;
    while (isalpha(charArray2[i]) && i < length2) {
      name[count] = charArray2[i];
      i++;
      count++;
    }
    name[count] = '\0';
    lastNames[nameNum] = name;
    nameNum++;
    while (!isalpha(charArray2[i+1])) {
      i++;
    }
  }
  while (stillGoing == true) {
    cout << "Would you like to add, delete, print, or quit?" << endl;
    char input[20];
    cin.get(input,20);
    cin.get();
    while (strcmp(input, "add") != 0 && strcmp(input, "delete") != 0 && strcmp(input, "quit") != 0 && strcmp(input, "print") != 0) {
      cout << "Please enter 'add', 'delete', 'print', or 'quit'" << endl;
      cin.get(input,20);
      cin.get();
    }
    if (strcmp(input,"add") == 0) {
      //ask for adding a single student or a file
      cout << "Would you like to add:\n1. random students\n2. specific student" << endl;
      int num;
      cin >> num;
      cin.ignore();
      while (num != 1 && num != 2) {
	cout << "Please enter 1 or 2" << endl;
	cin >> num;
	cin.ignore();
      }
      if (num == 1) {
	//get number of students
	int studentNum = 0;
	cout << "How many students would you like to be entered?" << endl;
	cin >> studentNum;
	cin.ignore();
       
	//use a file of first names and last names to generate random students with random IDs and GPAs
	for (int i = 0; i < studentNum; i++) {
	  Node* newStudent = new Node();
	  newStudent->next = NULL;
	  //generate a random student
	  int ID = hash->getID();
	  newStudent->ID = ID;
	  //get random first and last name
	  int first = rand()%49;
	  char* firstName = firstNames[first];
	  newStudent->firstName = firstName;
	  int last = rand()%49;
	  char* lastName = lastNames[last];
	  newStudent->lastName = lastName;
	  //get random GPA
	  double GPA = (rand()%400)/100.0;
	  if (GPA == 0) {
	    GPA = 1.0;
	  }
	  newStudent->GPA = GPA;
	  //	  cout << "New Student: " << newStudent->firstName << " " << newStudent->lastName << ", " << newStudent->ID << ", " << newStudent->GPA << endl;
	  //add to hash
	  hash->insert(newStudent);
	}
      }
      else if (num == 2) {
	//make student node and insert
	Node* newStudent = new Node();
	newStudent->next = NULL;
	cout << "First Name: ";
	char* name = new char[100];
	cin.get(name,100);
	cin.get();
	newStudent->firstName = name;
	cout << "Last Name: ";
	char* name2 = new char[100];
	cin.get(name2,100);
	cin.get();
	newStudent->lastName = name2;
	cout << "ID: ";
	int ID;
	cin >> ID;
	cin.ignore();
	newStudent->ID = ID;
	cout << "GPA: ";
	double GPA;
	cin >> GPA;
	cin.ignore();
	newStudent->GPA = GPA;
	while (hash->checkForID(newStudent) == 1) {
	  cout << "This Student ID already exists. Enter a new ID" << endl;
	  cout << "ID: ";
	  cin >> ID;
	  cin.ignore();
	  newStudent->ID = ID;
	}
	hash->insert(newStudent);
      }
    }
    else if (strcmp(input, "delete") == 0) {
      //get ID and then run remove
      cout << "Student ID: ";
      int ID;
      cin >> ID;
      cin.ignore();
      hash->remove(ID);
    }
    else if (strcmp(input, "print") == 0) {
      hash->print();
    }
    else {
      return 0;
    }
  }

  
  return 0;
}
