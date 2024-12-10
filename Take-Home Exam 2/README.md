# Sorted Subsequences with Linked Lists

## Description

Given a list of integers this program returns sorted subsequences using a linked list data structure. Users provide a list of integers in a line to the program, and then each number is added sequentially to the list, maintaining them in either ascending or descending order while enforcing the subsequence constraint: when a new number is added, all subsequent numbers in the sorting order are automatically removed.

## Problem Statement

Given a list of integers and a specified sorting order, return a sorted subsequence in that order

#### Example

Input:
Sorting Order: Ascending \n
Integer list: 1 5 8 2 9 10 6 7 4

Output: 1 2 4

## Features

- Maintains a sorted linked list (ascending or descending)
- Prevents duplicate entries
- Automatically removes all subsequent values when inserting a new number
- Real-time display of list changes and deleted values
- Memory-safe implementation with proper cleanup

## Implementation Details

The program uses a singly linked list implementation with the following key components:

### Data Structure

```cpp
struct node {
    int value;
    node* next;
};
```

### Key Functions

- `AddInAscendingOrder/AddInDescendingOrder`: Insert nodes while maintaining sort order
- `DeleteOrder`: Removes and returns all nodes after a specified value
- `DisplayList`: Converts the current list state to a string
- `CheckInList`: Verifies uniqueness of values

## Usage

1. Run the program
2. Enter sort order:
   - 'A' for ascending order
   - 'D' for descending order
3. Enter a line of numbers separated by spaces
4. The program will process each number and show:
   - The number being processed
   - Whether it was already present
   - Which values were deleted (if any)
   - The updated list content

## Example

```
Please enter the order mode (A/D): A
Please enter the numbers in a line: 5 3 7 2 8

Next number: 5
Deleted nodes: None
Appended: 5
List content: 5

Next number: 3
Deleted nodes: 5
Appended: 3
List content: 3

Next number: 7
Deleted nodes: None
Appended: 7
List content: 3 7
```

## Technical Notes

- Uses C++ standard libraries
- Requires the "strutils.h" library for string utilities
- Implements proper memory management with deletion of nodes
- Input validation for sort order selection
- Handles both single and multiple number inputs
