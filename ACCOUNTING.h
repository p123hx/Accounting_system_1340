//ACCOUNTING.h
//ACCOUNTING class definition
#ifndef ACCOUNTING_H
#define ACCOUNTING_H

// Controller class definition
// controller.h is the headed related to all system command's inplecation function
#include "controller.h"

class ACCOUNTING
{
public:
  // constructor initializes data
  ACCOUNTING();
  // start ACCOUNTING System
  void run();
private:
  // Accounting system command functions
  Controller controller;
  // to determine whether user is authenticated
  bool userAuthenticated;
  // function to authenticate user if all input information is valid
  void authenticate();
};

#endif
