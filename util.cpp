#include "database.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void addQ(Database &database);
void delQ(Database &database);
void listQ(Database &database);
void getQ(Database &database);
void printEntry(Entry &e);
void printArray(Array &a);
Array createArray();
void Query(Database &db, string cmd){
  if(cmd == "add") addQ(db);
  else if(cmd == "list") listQ(db);
  else if(cmd == "get") getQ(db);
  else if(cmd == "del") delQ(db);
  else cout << "invalid command\n";
  cout << '\n';
}

void addQ(Database &database){
  string key, type;
  Entry *entry;
  cout << "key: "; cin >> key;
  cout << "type (int, double, string, array): "; cin >> type;
  cout << "value: ";
  if(type == "int")
  {
    int val;
    cin >> val;
    entry = create(Type::INT, key, &val);
  }
  else if(type == "double")
  {
    double val;
    cin >> val;
    entry = create(Type::DOUBLE, key, &val);
  }
  else if(type == "string")
  {
    string val;
    getline(cin, val);
    getline(cin, val);
    entry = create(Type::STRING, key, &val);
  }
  else if(type == "array")
  {
    Array val = createArray();
    entry = create(Type::ARRAY, key, &val);
  }
  else
  {
    cout << "invalid type\n";
    return;
  }
  add(database, entry);
}
void listQ(Database &database){
  for(int i = 0; i < database.len; i++){
    printEntry(*(database.data[i]));
  }
}
void getQ(Database &database){
  string key;
  cout << "key: "; cin >> key;
  Entry *entry = get(database, key);
  if(entry == nullptr){
    cout << "not found\n";
    return;
  }
  printEntry(*entry);
}
void delQ(Database &database){
  string key;
  cout << "key: "; cin >> key;
  remove(database, key);
}

Array createArray(){
  Array arr;
  string type;

  cout << "type (int, double, string, array): ";
  cin >> type;
  cout << "size: ";
  cin >> arr.size;

  if(type == "int" )
  {
    arr.type = Type::INT;
    arr.items = new int[arr.size];
  }
  else if(type == "double")
  {
    arr.type = Type::DOUBLE;
    arr.items = new double[arr.size];
  }
  else if(type == "string")
  {
    arr.type = Type::STRING;
    arr.items = new string[arr.size];
  }
  else if(type == "array")
  {
    arr.type = Type::ARRAY;
    arr.items = new Array[arr.size];
  }
  string tmp;
  getline(cin, tmp);
  for(int i = 0; i < arr.size; i++){
    cout << "item[" << i <<"]: ";
    switch(arr.type){
      case Type::INT:
        cin >> static_cast<int*>(arr.items)[i];
        break;
      case Type::DOUBLE:
        cin >> static_cast<double*>(arr.items)[i];
        break;
      case Type::STRING:
        getline(cin, static_cast<string*>(arr.items)[i]);
        break;
      case Type::ARRAY:
        static_cast<Array*>(arr.items)[i] = createArray();
        break;
      default:
        break;
    }
  }
  return arr;
}
void printArray(Array &a){
  cout << "[";
  int sep_cnt = a.size - 1;
  for(int i = 0; i < a.size; i++){
    switch(a.type){
      case Type::INT:
        cout << static_cast<int*>(a.items)[i];
        break;
      case Type::DOUBLE:
        cout << static_cast<double*>(a.items)[i];
        break;
      case Type::STRING:
        cout << "\"" << static_cast<string*>(a.items)[i] <<"\"";
        break;
      case Type::ARRAY:
        printArray(static_cast<Array*>(a.items)[i]);
        break;
    }
    if(sep_cnt--) cout << ", ";
  }
  cout << "]";
}
void printEntry(Entry &e){
  cout << e.key << ": ";
  switch(e.type){
    case Type::INT:
      cout << *(static_cast<int*>(e.value));
      break;
    case Type::DOUBLE:
      cout << *(static_cast<double*>(e.value));
      break;
    case Type::STRING:
      cout << "\"" << static_cast<char*>(e.value) << "\"";
      break;
    case Type::ARRAY:
      printArray(*(static_cast<Array*>(e.value)));
      break;
  }
  cout << '\n';
}