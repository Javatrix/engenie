#pragma once

class Event {
public:
  void markHandled() { m_handled = true; }
  bool isHandled() { return m_handled; }

private:
  bool m_handled;
};
