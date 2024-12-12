# Hybrid Linked List for Displaying All Ordered Subsequences 

## Overview
This program implements a linked list of linked lists to generate and maintain ordered subsequences from a sequence of input numbers.  NOTE: Generation of subsequences is dependent on order of integer entry.

## Problem Statement
Given a sequence of integers as input, return the list of all possible ordered (ascending) subsequences from that sequence.

### Example:
Input: 1 3 2
Output: 
1
2
3
1 2
1 3


## Functionality

### Input Processing
- Takes a line of space-separated integers as input
- Positive numbers trigger addition operations
- Negative numbers trigger deletion operations (using absolute value)

### Key Operations

1. **Adding Subsequences** (`AddSubSeq`):
   - For a new positive number N:
   - Adds [N] as an individual subsequence
   - Creates new valid ordered subsequences by appending N to existing subsequences where N is greater than all elements
   - Maintains sorted order in the list

2. **Deleting Subsequences** (`DeleteSubSeqHead`):
   - For a number N:
   - Removes all subsequences containing |N|
   - Maintains the structure of remaining subsequences

3. **Display** (`DisplayList`):
   - Shows all current subsequences
   - Format: "size | value1 --> value2 --> value3"

### Example Usage
```
Input: 1 3 2
Output subsequences:
1 | 1
1 | 2
1 | 3
2 | 1 --> 2
2 | 1 --> 3
```

## Implementation Details

### Key Features
- Maintains subsequences in sorted order
- Prevents duplicate entries
- Efficiently handles both addition and deletion operations
- Manages memory through proper deletion of nodes

### Helper Functions
- `IsSubSeq`: Checks if a new ordered subsequence can be created
- `TailFinder`: Finds the last value in a subsequence
- `CreateSubSeq`: Creates a new ordered subsequence
- `SmallerSubSeq`: Compares two subsequences for ordering
- `Contains`: Checks if a value exists in a subsequence

## Memory Management
The program includes proper memory management:
- Deletes subsequences when removing elements
- Clears all allocated memory when the program ends
- Handles memory for both the main list and subsequences properly
