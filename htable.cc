#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

//Header
//***************************************************************************
//
// Name: Victoria Torres
// ZId:  Z2043396 
// CSCI 340 PE1
// Assignment: Separate Chaining Hashtable
// Desc: This program uses hash tables with separate chaining to store and search
// inventory items, while using pointers to display in alphabetical order.
// Due Date: 11/17/2026
// I certify that this is my own work and, where appropriate, an extension
// Of the starter code provided for the assignment.
//
//***************************************************************************


// Hash function, you may NOT modify this function
int HT::hash(const string &s) 
{
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...

// Constructor
HT::HT(const unsigned &hs) {
  hsize = hs;
  hTable.resize(hsize);
}

//Destructor
HT::~HT() {
  // vector and list containers automatically free their memory
  // the pointers in pTable do not own the entries
}

// Inserts an item into the hash table
void HT::insert(const Entry &e)
{
  int i = hash(e.key);

  // Get the list at the calculated hash index
  list<Entry> &l = hTable[i];

  // Check whether the key already exists
  auto it = find_if(l.begin(), l.end(),
                    [&e](const Entry &item) {
                      return item.key == e.key;
                    });

  if (it != l.end())
  {
    cout << " not inserted - duplicate key!!!" << endl;
  }
  else
  {
    // Insert the new item at the beginning of the list.
    l.push_front(e);

    // store the address of the new item in the pointer table
    pTable.push_back(&l.front());

    cout << " entry = " << setw(2) << i << endl;
  }
}

// Searches for an item using its key
void HT::search(const string &s) {
  int i = hash(s);

  // Get the list at the calculated hash index.
  list<Entry> &l = hTable[i];

  // Search for the matching key.
  auto it = find_if(l.begin(), l.end(),
                    [&s](const Entry &item) {
                      return item.key == s;
                    });

  if (it != l.end())
  {
    cout << " ==> number:" << setw(5) << it->num
         << " - item:" << left << setw(ITEM_SZ) << it->desc
         << right << endl;
  }
  else
  {
    cout << " not in table!!" << endl;
  }
}

// prints all active entries in the hash table
void HT::hTable_print()
{
  for (unsigned i = 0; i < hsize; i++)
  {
    // visit each item in the current list
    for (const Entry &e : hTable[i])
    {
      cout << setw(3) << i << ": "
           << setw(4) << e.key << " - "
           << setw(5) << e.num << " - "
           << left << setw(ITEM_SZ) << e.desc
           << right << endl;
    }
  }
}

// print the entries in sorted order
void HT::pTable_print()
{
  // Sort the pointers by their entries' keys.
  sort(pTable.begin(), pTable.end(),
       [](Entry *p, Entry *q) {
         return p->key < q->key;
       });

  // Print the entries in sorted order
  for (Entry *p : pTable)
  {
    cout << "  " << setw(3) << p->key << " - "
         << setw(5) << p->num << " - "
         << left << setw(ITEM_SZ) << p->desc
         << right << endl;
  }
}