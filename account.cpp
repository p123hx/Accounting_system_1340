#include "account.h"
#include "interest.h"
#include <fstream>
#include <algorithm>

std::string account_database_filename(uint64_t id)
{
    std::string result;
    while(id)
    {
        result += static_cast<char>(id % 10 - '0');
        id /= 10;
    }
    std::reverse(result.begin(), result.end());
    return result + ".record";
}

void SavingAccount::read()
{
    std::ifstream fin(account_database_filename(account_id));
    fin >> kyc >> pin >> balance >> last_date_interest >> next_date_interest >> cumulative_balance;
    Transaction tx;
    while(fin >> tx.from_account_id >> tx.to_account_id >> tx.value >> tx.date >> tx.description)
    {
        transactions.push_back(tx);
    }
}

void SavingAccount::write()
{
    std::ofstream fout(account_database_filename(account_id));
    fout << kyc << ' ' << pin << ' ' << balance << ' ' << last_date_interest << ' ' << next_date_interest << ' ' << cumulative_balance << std::endl;
    for(const Transaction &tx : transactions)
    {
        fout << tx.from_account_id << ' ' << tx.to_account_id << tx.value << tx.date << tx.description << std::endl;
    }
    fout.close();
}

void SavingAccount::init(const unsigned int &_pin, const std::string &_kyc, const uint64_t &value, const uint64_t &date_now, const uint64_t &date_next_interest, const uint64_t &associated_acct)
{
    pin = _pin;
    kyc = _kyc;
    last_date_interest = date_now;
    next_date_interest = date_next_interest;
}

void SavingAccount::put(const uint64_t &from, const uint64_t &v, const uint64_t d, const std::string &desc)
{
    balance += v;
    transactions.emplace_back(from, account_id, v, d, desc);
}

bool SavingAccount::take(const uint32_t &_pin, const uint64_t &to, const uint64_t &v, const uint64_t d, const std::string &desc)
{
    if(_pin != pin || balance < v)
        return false;
    balance -= v;
    transactions.emplace_back(account_id, to, v, d, desc);
    return true;
}

uint64_t SavingAccount::settle(const uint64_t &date)
{
    cumulative_balance += balance;
    if(date == next_date_interest)
    {
        put(0, calculate_saving_interest(cumulative_balance, last_date_interest, next_date_interest), date, "SAVING INTEREST");
        next_date_interest = date + next_date_interest - last_date_interest;
        cumulative_balance = 0;
    }
    return 0;
}

void TimeDeposit::read()
{
    std::ifstream fin(account_database_filename(account_id));
    fin >> balance >> last_date_interest >> next_date_interest >> saving_acct;
}

void TimeDeposit::write()
{
    std::ofstream fout(account_database_filename(account_id));
    fout << balance << ' ' << last_date_interest << ' ' << next_date_interest << ' ' << saving_acct << std::endl;
    fout.close();
}

void TimeDeposit::init(const unsigned int &_pin, const std::string &_kyc, const uint64_t &value, const uint64_t &date_now, const uint64_t &date_next_interest, const uint64_t &associated_acct)
{
    balance = value;
    last_date_interest = date_now;
    next_date_interest = date_next_interest;
    saving_acct = associated_acct;
}

uint64_t TimeDeposit::settle(const uint64_t &date)
{
    if(date == next_date_interest)
    {
        return balance + calculate_time_deposit_interest(balance, last_date_interest, next_date_interest);
    }
    return 0;
}
