#pragma once
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>
#include <string>
#include <cstdint>

struct Transaction
{
    uint64_t from_account_id, to_account_id, value, date;
    std::string description;
    /* Constructor function of struct transaction
     * input: from: the account number which money comes from
     * input: to: the account number which money will go to
     * input: v: the amount of money being transferred, in cents
     * input: d: the date when the transaction takes place
     * input: desc: the description of the transaction
     */
    Transaction(uint64_t from, uint64_t to, uint64_t v, uint64_t d, std::string desc) :
        from_account_id(from), to_account_id(to), value(v), date(d), description(desc) {}
};

class Account
{
    private:
        uint64_t account_id, balance, date_of_interest;
        unsigned int pin;
        std::string kyc;
        std::vector<Transaction> transactions;
    public:
        // Forbids default constructor
        Account() = delete;

        /* Constructor function of class account
         * input: id: the account number
         */
        Account(uint64_t id);

        // Read from database
        void read();

        // Write to database
        void write();

        /* Initialization when opening this new account
         * input: _pin: the PIN set by the customer when opening this account
         * input: _kyc: customer's legal indentification ID
         */
        void init(unsigned int _pin, std::string _kyc);

        /* Put money into this account
         * input: from: the account number which money comes from
         * input: v: the amount of money to be put in
         * input: d: the date of transaction
         * input: desc: the description of the transaction
         */
        void put(const uint64_t &from, const uint64_t &v, const uint64_t d, const std::string &desc);

        /* Request to take money away from this account
         * input: _pin: PIN given for this transaction
         * input: to: the destination of money
         * input: v: the amount of money to be taken out
         * input: d: the date of transaction
         * input: desc: the description of the transaction
         * return: boolean value indicating if the transaction succeeds
         */
        bool take(const uint32_t &_pin, const uint64_t &to, const uint64_t &v, const uint64_t d, const std::string &desc);
};

#endif // ACCOUNT_H_
