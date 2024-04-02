#include "database.h"
#include <iostream>
#include <string>
using namespace std;
const char nl = '\n';
void Query(Database &db, string cmd);
Entry* create(Type type, string key, void* value);
void deleteEntry(Entry *entry);
int main(){
  Database db;
  init(db);
  string command;
  while(1){
    cout << "command (list, add, get, del, exit): ";
    cin >> command;
    if(command == "exit") break;
    Query(db, command);
  }
  destroy(db);
} 