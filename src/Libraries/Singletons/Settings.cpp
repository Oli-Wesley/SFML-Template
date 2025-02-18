#include "settings.h"

// Define the static member variable
Settings* Settings::instance_ = nullptr;

// Implement the getInstance method
Settings* Settings::getInstance()
{
  if (instance_ == nullptr)
  {
    instance_ = new Settings();
  }
  return instance_;
}