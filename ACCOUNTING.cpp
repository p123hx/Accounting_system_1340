//ACCOUNTING.cpp
//Member-function definitions for class ACCOUNTING
#include "ACCOUNTING.h"//ACCOUNTING class definition
#include <iostream>
#include <fstream>
#include <string>

//ACCOUNTING default constructor initializes data member
ACCOUNTING::ACCOUNTING()
  : userAuthenticated(false) //user is not authenticated to start
  {
    //empty body
  }// end ACCOUNTING default constructor

  // start runnning ACCOUTNING
  void ACCOUNTING::run()
  {
      // loop while user is not yet authenticated
      while(userAuthenticated)
      {
        std::cout << "Accounting system is initiated, pls type in Accounting number and PIN\n";
        authenticate();// user will be authenticated if pin matches the database
      }
      bool exitedUser = false;// user does not comfirm the exitting.
      while(!exitedUser)
      {
        // displaying the main menu
        std::cout<<"\nMain menu:\n" << " OPEN - Open an account\n"
        << " DEPOSIT - Deposit money\n" << " WITHDRAW - Withdraw money\n" << " PURCHASE - Purchase at a POS\n TIME - Attempt to a time deposit\n"
        << " TRANSFER - Transfer\n SETTLE - Settle interests \n CLOSE - delete account \n EXIT - Exit the system\n";
        std::string customerInput;
        std::cin >> customerInput;
        switch (customerInput)
        {
          case "OPEN":
            std::cout << "Open an account:\nPlease enter customer identity\n";
            std::string KYC; std::cin >> KYC;
            std::cout<<"Please set up your 6-digit password PIN\n";
            std::string PIN; std::cin >> PIN;
            while (PIN.size()!= 6)
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
            int ACCT; std::cin >> ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; std::cin >> VALUE;
            if(controller.deposit(ACCT,VALUE))
            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;
          case "WITHDRAW":
            std::cout << "please enter the account number you want to withdraw from" << '\n';
            int ACCT; std::cin>>ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; std::cin>>VALUE;
            std::cout << "please enter your account PIN" << '\n';
            string PIN; std::cin>>PIN;
            if(controller.withdraw(ACCT,VALUE,PIN))
            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;

          case "PURCHASE":
            std::cout << "please enter the account number you want to purchase from" << '\n';
            int ACCT; std::cin >> ACCT;
            std::cout << "please enter the amount of money" << '\n';
            int VALUE; std::cin >> VALUE;
            std::cout << "please enter your account PIN" << '\n';
            string PIN; std::cin >> PIN;
            if(controller.purchase(ACCT,VALUE,PIN))
            std::cout << "Success!" << '\n';
            else std::cout << "System busy, try later" << '\n';
            break;

          case "TIME":
          std::cout << "please enter the account number you want to attempt a time depost from" << '\n';
          int ACCT; std::cin >> ACCT;
          std::cout << "please enter the amount of money" << '\n';
          int VALUE; std::cin >> VALUE;
          std::cout << "please enter your account PIN" << '\n';
          string PIN; std::cin >> PIN;
          std::cout << "please enter the period in days" << '\n';
          int PERIOD; std::cin >> PERIOD;
          if(controller.time_deposit(ACCT,VALUE,PIN,PERIOD))
          std::cout << "Success!" << '\n';
          else std::cout << "System busy, try later" << '\n';
          break;

          case "TRANSFER":
          std::cout << "please enter the account number you want to transfer from" << '\n';
          int ACCTO_FROM; std::cin >> ACCT_FROM;
          std::cout << "please enter the account number you want to transfer to" << '\n';
          int ACCT_TO; std::cin >> ACCT_TO;
          std::cout << "please enter the amount of money" << '\n';
          int VALUE; std::cin >> VALUE;
          std::cout << "please enter your account PIN" << '\n';
          string PIN; std::cin >> PIN;
          if(controller.transfer(ACCT_FROM,ACCT
            ,VALUE,PIN,PERIOD))
          std::cout << "Success!" << '\n';
          else std::cout << "System busy, try later" << '\n';
          break;

          case "SETTLE":
          controller.settle();
          break;

          case "CLOSE":
          std::cout << "please enter the account number you want to close" << '\n';
          int ACCT; std::cin>>ACCT;
          std::cout << "please enter your account PIN" << '\n';
          string PIN; std::cin>>PIN;
          if(controller.close_account(ACCT,PIN))
          std::cout << "Success!" << '\n';
          else std::cout << "System busy, try later" << '\n';
          break;

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

// to authenticate user if user's input matches
  void ACCOUNTING::authenticate()
  {
    std::cout<<("Entre your user name\n");
    std::string username;
    // database is stored with the username as the filename;
    // failing in finding the file is equivalent to failing in finding the username
    std::ifsteam fin;
    fin.open(username);
    if (fin.fail())
    {
      std::cout<<"user not found\n;"
      exit(1);
    }
    else
    {
      std::cout << ("Entre your PIN\n");// prompt for PIN
      std::string pinInput, pin;
      std::cin >> pinInput;
      fin >> pin;
      if (pin == pinInput) userAuthenticated = true;
      else
      {
        cout<<"Invalid PIN.\n";
      }
    }

  }//end function authenticate
