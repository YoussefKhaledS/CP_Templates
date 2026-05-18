#include <bits/stdc++.h>
using namespace std;

// ================= BUILTIN BIT FUNCTIONS =================

// __builtin_popcount(x)
// Returns number of 1s in binary representation of int.
//
// Example:
// 13 = 1101 -> returns 3
__builtin_popcount(x);


// __builtin_popcountll(x)
// Same as popcount but for long long.
__builtin_popcountll(x);


// __builtin_parity(x)
// Returns:
// 1 -> odd number of set bits
// 0 -> even number of set bits
//
// Example:
// 7 = 111 -> 3 bits -> returns 1
__builtin_parity(x);


// __builtin_clz(x)
// Count Leading Zeros.
//
// Returns number of zeros before first 1 bit.
//
// Example (32-bit int):
// 8 = 000...1000 -> returns 28
//
// WARNING:
// undefined if x == 0
__builtin_clz(x);


// __builtin_ctz(x)
// Count Trailing Zeros.
//
// Returns number of zeros after last 1 bit.
//
// Example:
// 40 = 101000 -> returns 3
//
// WARNING:
// undefined if x == 0
__builtin_ctz(x);


// __builtin_ffs(x)
// Find First Set bit.
//
// Returns 1-based index of first 1 from right.
//
// Example:
// 18 = 10010 -> returns 2
//
// Returns 0 if x == 0
__builtin_ffs(x);


// Long long versions
__builtin_clzll(x);
__builtin_ctzll(x);

// NOTE:
// clz(0) and ctz(0) => undefined



// ================= BITSET =================

// Create bitset
bitset<8> bs;

// Init from number
bitset<8> bs1(13);

// Init from binary string
bitset<8> bs2("101101");



// ================= ACCESS =================

// Access bit
bs[i];

// Check bit
bs.test(i);



// ================= MODIFY =================

// Set bit i = 1
bs.set(i);

// Set all = 1
bs.set();

// Reset bit i = 0
bs.reset(i);

// Reset all = 0
bs.reset();

// Flip bit
bs.flip(i);

// Flip all bits
bs.flip();



// ================= INFO =================

// Count set bits
bs.count();

// Any bit = 1
bs.any();

// All bits = 1
bs.all();

// All bits = 0
bs.none();



// ================= BITWISE OPS =================

bs1 & bs2;   // AND
bs1 | bs2;   // OR
bs1 ^ bs2;   // XOR
~bs1;        // NOT

bs <<= 2;    // Left shift
bs >>= 2;    // Right shift



// ================= CONVERT =================

// To string
bs.to_string();

// To ulong
bs.to_ulong();

// To ullong
bs.to_ullong();



// ================= EXAMPLE =================

bitset<5> b("10010");

b.set(0);      // 10011
b.reset(1);    // 10001
b.flip(4);     // 00001

cout << b.count(); // 1



// ================= BITSET SHIFTS =================

// Left Shift: <<
//
// Moves bits to the left.
// Zeros are added from the right.
//
// Example:
// 00101 << 2 -> 10100

bitset<5> bs1("00101");

cout << (bs1 << 2) << endl;



// Right Shift: >>
//
// Moves bits to the right.
// Zeros are added from the left.
//
// Example:
// 10100 >> 2 -> 00101

bitset<5> bs2("10100");

cout << (bs2 >> 2) << endl;



// Shift and Assign: <<=
//
// Updates the original bitset.
//
// Example:
// 00101 <<= 1 -> 01010

bitset<5> bs3("00101");

bs3 <<= 1;

cout << bs3 << endl;



// Shift and Assign: >>=
//
// Updates the original bitset.
//
// Example:
// 10100 >>= 2 -> 00101

bitset<5> bs4("10100");

bs4 >>= 2;

cout << bs4 << endl;



// ================= IMPORTANT NOTES =================
//
// Bits shifted outside are lost.
//
// Example:
// 10101 << 2 -> 10100
//
// Leftmost bits disappear.
//
// ---------------------------------------------------
//
// Shift amount >= size:
//
// bitset<5>("10101") << 5
// result -> 00000
//