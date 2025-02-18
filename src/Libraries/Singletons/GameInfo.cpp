#include "GameInfo.h"

// Define the static member variable
GameInfo* GameInfo::instance_ = nullptr;

// Implement the getInstance method
GameInfo* GameInfo::getInstance()
{
  if (instance_ == nullptr)
  {
    instance_ = new GameInfo();
  }
  return instance_;
}