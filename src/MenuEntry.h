#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

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
