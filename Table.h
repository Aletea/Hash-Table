#ifndef TABLE_H
#define TABLE_H
#include "Node.h"
#include <iostream>

using namespace std;

class Table {
 public:
  Table();
  ~Table();
  void insert(Node* student);
  void print();
  void remove(int ID);
  int getID();
  int checkForID(Node* check);
  
 private:
  int modulus;
  Node** array;
  int newID;
};
#endif
