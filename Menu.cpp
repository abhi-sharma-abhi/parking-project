
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

#include <iomanip>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds {
  void MenuItem::setItemName(const char str[]) {
    delete[] item;
    item = strcpy(str);
  }

  MenuItem::MenuItem() {
    size = 0;
    item = nullptr;
  }
  MenuItem::MenuItem(const char str[]) {
    this->size = strlen(str);
    if (!str) {
      item = nullptr;
    } else {
      item = strcpy(str);
    }
  }

  MenuItem::~MenuItem() {
    delete[] item;
  }

  // Menu
  ostream& Menu::indentLine(ostream& out) const {
    for (int i=0; i<indent*TAB_SIZE; i++) {
      out << " ";
    }
    return out;
  }

  void Menu::setEmpty() {

    delete[] title;
    delete[] items;
    title = nullptr;
    items = nullptr;
    indent = 0;
    item_cnt = 0;
    return;
  }

  Menu::Menu(const char str[], int indentation) {
    if (str == nullptr) {
      setEmpty();
      return;
    }
    title = strcpy(str);
    items = new MenuItem[MAX_NO_OF_ITEMS];
    indent = indentation;
    item_cnt = 0;
  }

  Menu::~Menu() {
    delete[] title;
    delete[] items;
  }

  Menu::operator bool() const {
    return title != nullptr;
  }

  bool Menu::isEmpty() const {
    return items == nullptr;
  }

  ostream& Menu::display(ostream& out) const {
    if (title == nullptr) {
      indentLine(out) << setw(TAB_SIZE*indent) << setfill(' ') << right << "Invalid Menu!\n";
      return out;
    } else {
      indentLine(out) << title << endl;
    }
    if (isEmpty()) {
      indentLine(out) << "No Items to display!" << endl;
      return out;
    }
    for (int i=1; i<=item_cnt; i++) {
      indentLine(out) << i << "- " << right << items[i-1].item << endl;
    }
    indentLine(out) << "> ";
    return out;
  }

  Menu& Menu::operator = (const char str[]) {
    if (title != nullptr) {
      delete[] title;
    }
    title = strcpy(str);
    return *this;
  }

  void Menu::add(const char itemName[]) {
    if (this->isEmpty()) return;
    if (!itemName) {
      this->setEmpty();
      return;
    }
    if (item_cnt == MAX_NO_OF_ITEMS) return;

    items[item_cnt].setItemName(itemName);
    item_cnt++;
  }

  Menu& Menu::operator << (const char str[]) {
    this->add(str);
    return *this;
  }

  int Menu::run() const {
    this->display();

    if (isEmpty()) return 0;

    int choice = 0;
    cin.clear();
    cin >> choice;
    while ( !(choice >= 1 && choice <= 9) || choice > item_cnt) {
      if ( !(choice >= 0 && choice <= 9) ) {
        cout << "Invalid Integer, try again: ";
      } else if (choice == 0 || choice > item_cnt) {
        cout << "Invalid selection, try again: ";
      }
      cin.clear();
      cin >> choice;
      cin.ignore(1000, '\n');
    }
    return choice;
  }

  Menu::operator int() const {
    return run();
  }

  void Menu::clear() {
    this->setEmpty();
  }
}
