#pragma once

class Event {
public:
  void handle() { handled = true; }
  bool isHandled() { return handled; }

private:
  bool handled;
}
