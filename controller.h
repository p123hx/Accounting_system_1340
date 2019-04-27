#pragma once
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "account.h"
#include <map>

class Controller
{
    private:
        std::map<uint64_t, Account*> accounts;
        uint64_t calendar;

    public:
        // Read information from database on start up
        void read();

        // Write information back to database on exit
        void write();

        /* Open an account
         * input: pin: the PIN set by the customer when opening this account
         * input: kyc: customer's legal identification
         * return: the account number in 64-bit unsigned integer format, 0 if failed to open an account
         */
        uint64_t open_account(const unsigned int &pin, const std::string &kyc);

        /* Transfer money
         * input: from: the account where money comes from
         * input: to: the account where money will go to
         * input: value: the amount of money to be transfered
         * input: pin: PIN for verification if necessary
         * input: date: the date of the transaction
         * input: desc: the description of the transaction
         * return: boolean value indicating if the transaction succeeds
         */
        bool transfer(const uint64_t &from, const uint64_t &to, const uin64_t &value, const unsigned int &pin, const uint64_t &date, const std::string &desc);
};

#endif // CONTROLLER_H_
