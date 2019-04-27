//ACCOUNTING.h
//ACCOUNTING class definition
#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "controller.h"

class ACCOUNTING
{
public:
  ACCOUNTING();
  void run();
private:
  Controller controller;
  bool userAuthenticated;

  void authenticate();
};

#endif
