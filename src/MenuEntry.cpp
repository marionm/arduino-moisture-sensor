#include "MenuEntry.h"

MenuEntry::MenuEntry(String _name, MenuEntry *_parent) {
  name        = _name;
  parent      = _parent;
  nextSibling = NULL;
  prevSibling = NULL;
  child       = NULL;
}

void MenuEntry::setSibling(MenuEntry *sibling) {
  nextSibling = sibling;
  sibling->prevSibling = this;
}
