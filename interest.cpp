#include "interest.h"

uint64_t calculate_saving_interest(const uint64_t cumulative_balance, const uint64_t last_date_interest, const uint64_t next_date_interest)
{
    static const double apr = 0.00125;
    return cumulative_balance * apr / 360 * (next_date_interest - last_date_interest);
}

uint64_t calculate_time_deposit_interest(const uint64_t balance, const uint64_t last_date_interest, const uint64_t next_date_interest)
{
    static const double apr = 0.004;
    return balance * apr / 360 * (next_date_interest - last_date_interest);
}
