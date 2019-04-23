//ACCOUNTING.h
//ACCOUNTING class definition
#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "BankData.h"

class ACCOUNTING
{
public:
  ACCOUNTING();
  void run();
private:
  bool userAuthenticated;
  int currentAccountNum;

  void authenticate();
};

#endif
