#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

struct Node {
  Node* next = NULL;
  char* firstName = new char[100];
  char* lastName = new char[100];
  int ID = 0;
  double GPA = 0;
};
#endif
