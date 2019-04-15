# Banking Back-end Accounting System

HKU ENGG 1340 group project.

## Problem Statement

By the aid of the rapid development of electronic technology over the past few decades, banking has no longer only been to deposit and withdraw money by handing a passbook and queueing in front of counters, but, with modern bank cards and Internet nowadays, banking also includes making purchases and consumptions via settlement network, managing various forms of assets on e-banking, etc. Transactions not only happen just in counters in the banks, but may also take place anytime anywhere. It is absolutely essential for modern banks to incoporate electronized automated accounting system to carry out transactions 7/24. This project aims to build a simple banking back-end accounting system to fulfill such demands.

## Program Features

The program serves as a back-end system of a bank such that customers at the front-end are able to

- Open saving accounts linked with customer identity (KYC ID) and password (PIN)
- Deposit and withdraw cash to/from saving accounts
- Purchase commodities by a bank card associated with a saving account
- Open time deposits
- Receive interests of saving accounts and time deposits
- Trasnfer money from a saving account to another
- Close accounts

For simplicity, instructions are to be given in the form of string in the command-line, and corresponding results will be shown in the command-line as well.

## Internal data formats

### Storage of monetary values

Since IEEE floating point numbers come with limited precision, there would be information loss if we were to store monetary values using floating point numbers. For the sake of accuracy, in this project, we will be using 64-bit integers to represent monetary values. Specifically, considering the nature of Hong Kong Dollars, we will be storing monetary values in the unit of cents. That is, 12.34 HKD will be 1234 in the memory.

### Account numbers

In this project, account numbers are 64-bit, 10-digit integers, starting with 1 at highest digit, and ending with a checksum digit at lowest digit.

### Transactions

Each transaction consists of 5 parts of information, respectively the amount of money transferred, where the money is originated, where the money goes, the date when the transaction takes place, and the description of the transaction.

### Account

When opening account, a randomly picked free account number gets associated with customer's identification ID (a.k.a. KYC) and a 6-digit PIN set by the customer. Afterwards, whenever a transaction that withdraws money from the account is requested, the system verifies PIN, and executes the transaction if PIN matches.
