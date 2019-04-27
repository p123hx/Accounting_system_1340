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

        /* Transfer money
         * input: from: the account where money comes from
         * input: to: the account where money will go to
         * input: value: the amount of money to be transfered
         * input: pin: PIN for verification if necessary
         * input: date: the date of the transaction
         * input: desc: the description of the transaction
         * return: boolean value indicating if the transaction succeeds
         */
        bool exec_transaction(const uint64_t &from, const uint64_t &to, const uint64_t &value, const std::string &pin, const uint64_t &date, const std::string &desc);

        uint64_t allocate_id();

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
        uint64_t open_account(const std::string &pin, const std::string &kyc);

        bool close_account(const uint64_t &account_id, const std::string &pin);

        bool deposit(const uint64_t &account_id, const uint64_t &value);

        bool withdraw(const uint64_t &account_id, const uint64_t &value, const std::string &pin);

        bool purchase(const uint64_t &account_id, const uint64_t &value, const std::string &pin);

        bool transfer(const uint64_t &from, const uint64_t &to, const uint64_t &value, const std::string &pin);

        bool time_deposit(const uint64_t &account_id, const uint64_t &value, const std::string &pin, const uint64_t &period);

        void settle();
};

#endif // CONTROLLER_H_
