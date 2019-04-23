//ACCOUNTING.cpp
//Member-function definitions for class ACCOUNTING
#include "ACCOUNTING.h"
#include iostream
#include fstream
#include string

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
        std::cout<<"Accounting system is initiated, pls type in Accounting number and PIN\n";
        authenticate();
      }
      std::cout<<"\nmain menu\n";
      std::cout << "0-Exit\n";
      std::string type;
      std::cin>>type;
      switch (type)
      {
        default:{
          userAuthenticated=false;
          currentAccountNum=0;
          std::cout<<("Accounting system is closed.\n")
          break;
        }
          
      }

    }

  }

  void ACCOUNTING::authenticate()
  {
    std::cout<<("Entre your account number\n");
    std::int accountNumInt;
    std::string accountNumStr;
    std::cin >> accountNumInt;
    std::stringstream ss;
    ss << accountNumInt;
    accountNumStr=ss.str();
    std::ifsteam fin;
    fin.open(accountNumStr);
    if (fin.fail())
    {
      std::cout <<"account not found\n;"
      exit(1);
    }
    else
    {
      std::cout<<("Entre your PIN\n");
      std::string pinInput, pin;
      std::cin>>pinInput;
      fin >> pin;
      if (pin==pinInput) {
        userAuthenticated=true;
        currentAccountNum=accountNumInt;}
      else {
        cout<<"Invalid PIN.\n";
      }
    }


  }
