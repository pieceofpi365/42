#ifndef BITCOIN_TIMESTAMPS_H
#define BITCOIN_TIMESTAMPS_H
static const unsigned int CHECKLOCKTIMEVERIFY_SWITCH_TIME = 1478476800; // Monday, 07 Nov 2016 00:00:00 UTC
// Threshold for nLockTime: below this value it is interpreted as block number, otherwise as UNIX timestamp.
static const unsigned int LOCKTIME_THRESHOLD = 500000000; // Tue Nov  5 00:53:20 1985 UTC
#endif
