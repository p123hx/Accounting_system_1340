//ACCOUNTING.h
//ACCOUNTING class definition
#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "BankData.h"
#include "controller.h"

class ACCOUNTING
{
public:
  ACCOUNTING();
  void run();
private:
  Controller controller;
  bool userAuthenticated;
  int currentAccountNum;

  void authenticate();
};

#endif
