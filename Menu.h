
/* Citation and Sources...
Final Project Milestone ? 
Module: Whatever
Filename: Whatever.cpp
Version 1.0
Author  John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and 
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/

#define MAX_ITEM_LENGTH 50
#define MAX_NO_OF_ITEMS 10
#define TAB_SIZE 4

#include <iostream>

using namespace std;

namespace sdds {
  class Menu;
  class MenuItem {
    char* item;
    int size;
    void setItemName(const char str[]);
    
    public:
      MenuItem();
      MenuItem(const char str[]);
      MenuItem(const MenuItem& mi2) = delete;
      MenuItem& operator=(const MenuItem& mi2) = delete;
      ~MenuItem();
      friend class Menu;
  };

  class Menu {
    char* title;
    MenuItem* items;
    int item_cnt;
    int indent;

    ostream& indentLine(ostream& out=cout) const;
    void setEmpty();

    public:
      Menu(const char str[], int indentation=0);
      Menu(const Menu& m2) = delete;
      Menu& operator = (const Menu& m2) = delete;
      ~Menu();

      operator bool() const;
      bool isEmpty() const;

      ostream& display(ostream& out=cout) const;

      Menu& operator = (const char str[]);

      void add(const char itemName[]);
      Menu& operator << (const char str[]);

      int run() const;
      operator int() const;
      void clear();
  };
}
