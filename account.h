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
    Transaction() {}
};

enum AccountType
{
    SAVING,
    TIME
};

class Account
{
    protected:
        uint64_t account_id, balance, last_date_interest, next_date_interest;
        AccountType account_type;
    public:
        AccountType get_account_type() { return account_type; }

        /* Read account information from disk file */
        virtual void read() = 0;

        /* Write account information into disk file */
        virtual void write() = 0;

        /* Generic function of initializing an account
         * input: pin: PIN, only applicable to saving accounts
         * input: kyc: KYC, only applicable to saving accounts
         * input: value: Initial value of the account, only applicable to time deposits
         * input: date_now: Current date
         * input: date_next_interest: The date of next interest settlement
         * input: associated_acct: The associated saving account, only applicable to time deposits
         */
        virtual void init(const std::string &_pin, const std::string &_kyc, const uint64_t &value, const uint64_t &date_now, const uint64_t &date_next_interest, const uint64_t &associated_acct) = 0;

        /* Put money into this account, only applicable to saving accounts
         * input: from: the account number which money comes from
         * input: v: the amount of money to be put in
         * input: d: the date of transaction
         * input: desc: the description of the transaction
         */
        virtual void put(const uint64_t &from, const uint64_t &v, const uint64_t d, const std::string &desc) = 0;

        /* Request to take money away from this account, only applicable to saving accounts
         * input: _pin: PIN given for this transaction
         * input: to: the destination of money
         * input: v: the amount of money to be taken out
         * input: d: the date of transaction
         * input: desc: the description of the transaction
         * return: boolean value indicating if the transaction succeeds
         */
        virtual bool take(const std::string &_pin, const uint64_t &to, const uint64_t &v, const uint64_t d, const std::string &desc) = 0;

        /* Settle interest
         * input: date: Current date
         * */
        virtual uint64_t settle(const uint64_t &date) = 0;

        virtual uint64_t get_saving_account() = 0;
};

class SavingAccount : public Account
{
    protected:
        std::string pin;
        std::string kyc;
        std::vector<Transaction> transactions;
        uint64_t cumulative_balance;
    public:
        SavingAccount(const uint64_t &id) { account_id = id; }
        void read();
        void write();
        void init(const std::string &_pin, const std::string &_kyc, const uint64_t &value, const uint64_t &date_now, const uint64_t &date_next_interest, const uint64_t &associated_acct);
        void put(const uint64_t &from, const uint64_t &v, const uint64_t d, const std::string &desc);
        bool take(const std::string &_pin, const uint64_t &to, const uint64_t &v, const uint64_t d, const std::string &desc);
        uint64_t settle(const uint64_t &date);
        uint64_t get_saving_account() { return 0; }
};

class TimeDeposit : public Account
{
    protected:
        uint64_t saving_acct;
    public:
        TimeDeposit(const uint64_t &id) { account_id = id; }
        void read();
        void write();
        void init(const std::string &_pin, const std::string &_kyc, const uint64_t &value, const uint64_t &date_now, const uint64_t &date_next_interest, const uint64_t &associated_acct);
        void put(const uint64_t &from, const uint64_t &v, const uint64_t d, const std::string &desc) {}
        bool take(const std::string &_pin, const uint64_t &to, const uint64_t &v, const uint64_t d, const std::string &desc) { return false; }
        uint64_t settle(const uint64_t &date);
        uint64_t get_saving_account() { return saving_acct; }
};

#endif // ACCOUNT_H_
