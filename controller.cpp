#include "controller.h"
#include "fastrng.h"
#include <fstream>

uint64_t generate_id()
{
    return 1000000000 + rng() % 1000000000;
}

uint64_t Controller::allocate_id()
{
    uint64_t id;
    while(accounts.find(id = generate_id()) != accounts.end());
    return id;
}

void Controller::read()
{
    std::ifstream fin("controller.record");
    fin >> calendar;
    uint64_t acct;
    std::string type;
    while(fin >> acct >> type);
    {
        if(type == "SAVING")
        {
            accounts[acct] = new SavingAccount(acct);
            accounts[acct]->read();
        }
        else if(type == "TIME")
        {
            accounts[acct] = new TimeDeposit(acct);
            accounts[acct]->read();
        }
    }
}

void Controller::write()
{
    std::ofstream fout("controller.record");
    fout << calendar << std::endl;
    for(const auto &i : accounts)
        fout << i.first << ' ' << (i.second->get_account_type() == SAVING ? "SAVING" : "TIME" ) << std::endl;
    fout.close();
}

bool Controller::exec_transaction(const uint64_t &from, const uint64_t &to, const uint64_t &value, const std::string &pin, const uint64_t &date, const std::string &desc)
{
    if((from == 0 || accounts.find(from) != accounts.end()) && (to == 0 || accounts.find(to) != accounts.end()))
    {
        if(from == 0 || accounts[from]->take(pin, to, value, date, desc))
        {
            if(to > 0)
            {
                accounts[to]->put(from, value, date, desc);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

uint64_t Controller::open_account(const std::string &pin, const std::string &kyc)
{
    uint64_t id = allocate_id();
    accounts[id] = new SavingAccount(id);
    accounts[id]->init(pin, kyc, 0, calendar, calendar + 10, 0);
    return id;
}

bool Controller::close_account(const uint64_t &account_id, const std::string &pin)
{
    if(accounts.find(account_id) == accounts.end())
        return false;
    accounts[account_id]->write();
    delete accounts[account_id];
    accounts.erase(account_id);
    return true;
}

bool Controller::deposit(const uint64_t &account_id, const uint64_t &value)
{
    return exec_transaction(0, account_id, value, "", calendar, "DEPOSIT");
}

bool Controller::withdraw(const uint64_t &account_id, const uint64_t &value, const std::string &pin)
{
    return exec_transaction(account_id, 0, value, pin, calendar, "WITHDRAW");
}

bool Controller::purchase(const uint64_t &account_id, const uint64_t &value, const std::string &pin)
{
    return exec_transaction(account_id, 0, value, pin, calendar, "PURCHASE");
}

bool Controller::transfer(const uint64_t &from, const uint64_t &to, const uint64_t &value, const std::string &pin)
{
    return exec_transaction(from, to, value, pin, calendar, "TRANSFER");
}

bool Controller::time_deposit(const uint64_t &account_id, const uint64_t &value, const std::string &pin, const uint64_t &period)
{
    uint64_t id = allocate_id();
    if(!exec_transaction(account_id, id, value, pin, calendar, "OPEN TIME DEPOSIT"))
        return false;
    accounts[id] = new TimeDeposit(id);
    accounts[id]->init("", "", value, calendar, calendar + period, account_id);
    return true;
}

void Controller::settle()
{
    std::vector<uint64_t> finished_time_deposits;
    for(auto &i : accounts)
    {
        if(i.second->get_account_type() == SAVING)
        {
            i.second->settle(calendar);
        }
    }
    for(auto &i : accounts)
    {
        if(i.second->get_account_type() == TIME)
        {
            uint64_t money = i.second->settle(calendar);
            if(money > 0)
            {
                exec_transaction(i.first, i.second->get_saving_account(), money, "", calendar, "TIME DEPOSIT FINISHED");
                finished_time_deposits.push_back(i.first);
            }
        }
    }
    for(const auto &i : finished_time_deposits)
        accounts.erase(i);
    ++calendar;
}
