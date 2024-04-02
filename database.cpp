#include "database.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void resizeDB(Database &database);
void deleteEntry(Entry *entry);
void deleteArray(Array &array);
int findEntry(Database &database, string &key);

void init(Database &database){
  database.SIZE = 1;
  database.len = 0;
  database.data = new Entry*[database.SIZE];
}

Entry *create(Type type, string key, void* value){
  Entry *e = new Entry;
  e->key = key;
  e->type = type;
  switch(type){
    case Type::INT:
      e->value = new int;
      memcpy(e->value, value, sizeof(int));
      break;
    case Type::DOUBLE:
      e->value = new double;
      memcpy(e->value, value, sizeof(double));
      break;
    case Type::STRING:
      e->value = new char[static_cast<string*>(value)->size() + 1];
      memcpy(e->value, static_cast<string*>(value)->c_str(), static_cast<string*>(value)->size() + 1);
      break;
    case Type::ARRAY:
      e->value = new Array;
      memcpy(e->value, value, sizeof(Array));
      break;
    default:
      cout << "invalid type\n";
      return nullptr;
      break;
  }
  return e;
}
void add(Database &database, Entry *entry){
  if(database.len == database.SIZE) resizeDB(database);
  int idx = findEntry(database, entry->key);
  if(idx == -1) { database.data[database.len++] = entry; return; }
  Entry *tmp = database.data[idx];
  database.data[idx] = entry;
  deleteEntry(tmp);
}
Entry *get(Database &database, string &key){
  int idx = findEntry(database, key);
  if(idx == -1) return nullptr;
  return database.data[idx];
}
void remove(Database &database, string &key){
  int idx = findEntry(database, key);
  if(idx == -1){
    cout << "not found\n";
    return;
  }
  swap(database.data[idx], database.data[database.len-1]);
  deleteEntry(database.data[database.len-1]);
  database.data[database.len-1] = nullptr;
  database.len--;
}

void destroy(Database &database){
  for(int i = 0; i < database.len; i++){
    deleteEntry((database.data)[i]);
  }
  delete [] database.data;
}

void resizeDB(Database &database){
  database.SIZE *= 2;
  Entry **tmp = new Entry*[database.SIZE];
  for(int i = 0; i < database.len; i++){
    tmp[i] = database.data[i];
  }
  delete [] database.data;
  database.data = tmp;
}
void deleteEntry(Entry *entry){
  switch(entry->type){
    case Type::INT:
      delete static_cast<int*>(entry->value);
      break;
    case Type::DOUBLE:
      delete static_cast<double*>(entry->value);
      break;
    case Type::STRING:
      delete [] static_cast<char*>(entry->value);
      break;
    case Type::ARRAY:
      deleteArray(*(static_cast<Array*>(entry->value)));
      delete static_cast<Array*>(entry->value);
      break;
  }
  delete entry;
}
// Array 구조체 변수, items의 메모리 해제
void deleteArray(Array &array){
  switch(array.type){
    case Type::INT:
      delete [] static_cast<int*>(array.items);
      break;
    case Type::DOUBLE:
      delete [] static_cast<double*>(array.items);
      break;
    case Type::STRING:
      delete [] static_cast<string*>(array.items);
      break;
    case Type::ARRAY:
      for(int i = 0; i < array.size; i++){
        deleteArray((static_cast<Array*>(array.items)[i]));
      }
      delete [] static_cast<Array*>(array.items);
      break;
  }
}
int findEntry(Database &database, string &key){
  for(int i = 0; i < database.len; i++){
    if(database.data[i]->key != key) continue;
    return i;
  }
  return -1;
}