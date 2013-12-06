#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

//TODO: Extract basic elements to struct, and compose different types?
//TODO: Need three types, each with one action:
//        go to child
//        do something and output results
//        accept input and save results

class MenuEntry {
  public:
    String name;
    MenuEntry *parent;
    MenuEntry *nextSibling;
    MenuEntry *prevSibling;
    MenuEntry *child;

    MenuEntry(String name = NULL, MenuEntry *parent = NULL);

    void setSibling(MenuEntry *sibling);
};

#endif
