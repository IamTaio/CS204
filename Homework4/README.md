# Matrix Path Finding Program

## Description
This program implements a path-finding algorithm in a binary matrix that searches for specific bit patterns by moving only right and down. The program uses a dynamic stack data structure to track and backtrack paths through the matrix.

## Problem Statement

### Input
1. Matrix dimensions (rows and columns)
2. Input file containing a binary matrix
3. Bit string to search for

Example input file (`matrix.txt`):
```
1010
1111
0101
1010
```

Example bit string to search: "1101"

### Output
If a path is found, the program outputs the sequence of coordinates (row,col) that form the path matching the bit string.

Example:
```
Please enter a string of bits to search: 1101
The bit string 1101 is found following these cells:
(0,0) (0,1) (1,1) (1,2)
```

If no path is found, the program indicates that the bit string could not be found.

## Functions and Usage

### Main Components
1. `DynIndStack` class: Manages path coordinates using a dynamic stack
   - `push(row, col)`: Add coordinates to stack
   - `pop(row, col)`: Remove and return top coordinates
   - `isEmpty()`: Check if stack is empty

2. Matrix Operations
   - `MatrixEditor`: Reads matrix from file and initializes data structure
   - `FindString`: Core path-finding algorithm
   - `CheckRight/CheckDown`: Validate potential moves

### How to Use

1. Compile the program:
   ```
   g++ taiwovictor_Taiwo_VictorOluwalonimi_hw4_Main.cpp 
       taiwovictor_Taiwo_VictorOluwalonimi_hw4_DynIndStackClass.cpp -o pathfinder
   ```

2. Prepare input file:
   - Create a text file containing the binary matrix
   - Each line should contain a sequence of 0s and 1s
   - Number of characters should match specified dimensions

3. Run the program:
   ```
   ./pathfinder
   ```

4. When prompted:
   - Enter number of rows
   - Enter number of columns
   - Enter input file name
   - Enter bit strings to search
   - Use CTRL+Z (Windows) or CTRL+D (Unix) to exit

### Constraints
- Matrix can only be traversed by moving right or down
- Path must start from top-left corner (0,0)
- Input file must match specified dimensions
- Only binary digits (0 and 1) are accepted in the matrix

### Error Handling
The program validates:
- File existence and accessibility
- Matrix dimensions
- Matrix content format
- Movement boundaries

## Example Session
```
Please enter the number of rows: 4
Please enter the number of columns: 4
Please enter the name of the input file: matrix.txt

Please enter a string of bits to search (CTRL+Z to quit): 1101
The bit string 1101 is found following these cells:
(0,0) (0,1) (1,1) (1,2)

Please enter a string of bits to search (CTRL+Z to quit): 0101
The bit string 0101 could not be found.
---------------------------------------------------------
```
