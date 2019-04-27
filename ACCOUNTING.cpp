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
      while(userAuthenticated)
      {
        std::cout<<"Accounting system is initiated, pls type in Accounting number and PIN\n";
        authenticate();
      }
      bool exitedUser=false;
      while(!exitedUser)
      {
        std::cout<<"\nMain menu:"<<"\n OPEN - Open an account"
        <<"\n DEPOSIT - Deposit money"<<"\n WITHDRAW - Withdraw money"<<"\n PURCHASE - Purchase at a POS\n TIME - Attempt to a time deposit"
        <<"\n TRANSFER - Transfer\n SETTLE - Settle interests \n CLOSE - delete account \n EXIT - Exit the system\n";
        std::string customerInput;
        std::cin>>customerInput;
        switch (customerInput)
        {
          case "OPEN":
            std::cout<<"\nOpen an account:\nPlease enter customer identity\n";
            std::string KYC, cin>>KYC;
            std::cout<<"\nPlease set up your 6-digit password PIN\n";
            std::string PIN, cin>>PIN;
            while (PIN.size()!=6)
            {
              std::cout<<"Your password must be 6-digit; please set up again.\n";
              std::cin>>PIN;
            }

            int ACCT=controller.open_account(PIN,KYC);
            if (ACCT==0) std::cout << "No more account number available." << '\n';
            else std::cout << "Your account is created, account number is:  "<< ACCT<< '\n';
             break;
          case "DEPOSIT":
            std::cout << "please enter the account number you want to deposit to" << '\n';
            int ACCT; cin>>ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; cin>>VALUE;
            if(controller.deposit(ACCT,VALUE))
            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;
          case "WITHDRAW":
            std::cout << "please enter the account number you want to withdraw from" << '\n';
            int ACCT; cin>>ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; cin>>VALUE;
            std::cout << "please enter your account PIN" << '\n';
            string PIN; cin>>PIN;
            if(controller.withdraw(ACCT,VALUE,PIN))
            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;

          case "PURCHASE":
            std::cout << "please enter the account number you want to purchase from" << '\n';
            int ACCT; cin>>ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; cin>>VALUE;
            std::cout << "please enter your account PIN" << '\n';
            string PIN; cin>>PIN;
            if(controller.purchase(ACCT,VALUE,PIN))

            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;

          case "TIME"

          case "EXIT";
            std::cout << "Exiting the system" << '\n';
            exitedUser=true;

          default:{
            std::cout << "you did not enter a valid command. Try again." << '\n';
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
