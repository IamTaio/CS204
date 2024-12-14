# Wallet Class Implementation

## 1. Project Overview

The Wallet class provides a C++ implementation for managing multiple currency accounts within a digital wallet.

### Key Features

- Dynamic management of multiple currency accounts
- Support for adding and removing currency amounts
- Deep copy and assignment operations
- Comparison operations between wallets and specific currency amounts
- Currency-specific balance tracking
- String representation for display purposes

### Technologies

- C++
- Dynamic memory allocation
- Operator overloading
- Stream manipulation

## 2. Problem Statement

This implementation solves the problem of managing multiple currency accounts within a single wallet system.

### Inputs

- Currency name (string)
- Currency amount (double)
- Operations (add/subtract/compare)

Example input:

```cpp
Money t;
t.currency = "USD";
t.amount = 33.2;
```

### Outputs

- Wallet state as formatted string
- Comparison results
- Operation success/failure indicators

Example output:

```
USD 33.2 - EUR 25.0 - GBP 15.5
```

## 3. Implementation Details

### Core Components

#### Money Struct

```cpp
struct Money {
    string currency;
    double amount;
};
```

#### Wallet Class

Key member variables:

- `Money* accounts`: Dynamic array of currency accounts
- `int size`: Number of currency accounts

### Key Functions

#### Constructors/Destructor

- Default constructor: Creates empty wallet
- Copy constructor: Deep copy of existing wallet
- Destructor: Proper cleanup of dynamic memory

#### Operators

- `+`: Add currency to wallet
- `-`: Remove currency from wallet
- `+=`: Combine two wallets
- `=`: Assignment with deep copy
- `>=`, `<=`, `==`: Comparison operations

#### Utility Functions

- `getCurrencyIndex`: Find currency position in wallet
- `TransferCurrencies`: Copy currencies between wallets
- `tostring`: String representation of wallet contents

### Data Structures

- Dynamic array for storing Money objects
- Each Money object contains currency name and amount

## 4. Usage Instructions

### Requirements

- C++ compiler
- Standard C++ libraries

### Basic Usage Example

```cpp
// Create a wallet
Wallet myWallet;

// Add currency
Money usd;
usd.currency = "USD";
usd.amount = 100.0;
myWallet = myWallet + usd;

// Display wallet contents
cout << myWallet << endl;
```

## 5. Error Handling

The class handles several error conditions:

- Insufficient funds during withdrawal
- Memory allocation failures
- Invalid currency operations
- Empty wallet operations

Constraints:

- Currency amounts must be positive
- Currency names must be non-empty strings
- Memory must be available for dynamic allocation

## 6. Example Session

An example session can be seen by looking at and compiling the code present in main.cpp.
