#pragma once

#include "unnamedEngine/event/event.hpp"
class KeyEvent : public Event {
public:
  KeyEvent(int key, int action, int mods)
      : m_key(key), m_action(action), m_mods(mods) {}

private:
  int m_key, m_action, m_mods;
};
