#pragma once
#ifndef INTEREST_H_
#define INTEREST_H_

#include <cstdint>

uint64_t calculate_saving_interest(const uint64_t cumulative_balance, const uint64_t last_date_interest, const uint64_t next_date_interest);
uint64_t calculate_time_deposit_interest(const uint64_t balance, const uint64_t last_date_interest, const uint64_t next_date_interest);


#endif // INTEREST_H_
