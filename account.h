#pragma once
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>
#include <string>
#include <cstdint>

struct transaction
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
    transaction(uint64_t from, uint64_t to, uint64_t v, uint64_t d, std::string desc) :
        from_account_id(from), to_account_id(to), value(v), date(d), description(desc) {}
};

class account
{
    private:
        uint64_t account_id;
        unsigned int pin;
        std::string kyc;
        std::vector<transaction> transactions;
    public:
        /* Constructor function of class account for reading database
         * input: id: the account number
         * input: file_name: the file name which stores data
         */
        account(uint64_t id, std::string file_name);

        /* Constructor function of class account for opening account
         * input: id: the account number
         * input: _pin: the PIN set by the customer when opening this account
         * input: _kyc: customer's legal indentification ID
         */
        account(uint64_t id, unsigned int _pin, std::string _kyc) :
            account_id(id), pin(_pin), kyc(_kyc) {}

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
