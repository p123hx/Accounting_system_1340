//ACCOUNTING.cpp
//Member-function definitions for class ACCOUNTING
#include "ACCOUNTING.h"
#include iostream

enum MenuOpetion{};

ACCOUNTING::ACCOUNTING()
  : userAuthenticated(flase),
  currentAccountNum(0)
  {

  }

  void ACCOUNTING::run()
  {
    while(true)
    {
      while(userAuthenticated)
      {
        cout<<"Accounting system is initiated, pls type in\n";
        authenticate();
      }
      userAuthenticated=false;
      currentAccountNum=0;
      cout<<("Accounting system is closed.\n")
    }

  }

  void ACCOUNTING::authenticate()
  {

  }
