# Production Line Simulation System

## 1. Project Overview
A C++ implementation of a production line simulation using multithreading and dynamic queues. The system simulates a manufacturing process with three stages: production, filling, and packaging.

### Key Features
- Multi-threaded production line simulation
- Dynamic queue implementation for inter-thread communication
- Concurrent processing with multiple workers
- Thread-safe operations using mutexes
- Real-time operation logging with timestamps
- Configurable timing parameters

### Technologies
- C++ 
- STL Threads
- Mutexes for synchronization
- Chrono library for timing
- Dynamic memory management

## 2. Problem Statement
The system simulates a production line where:
- One producer creates empty boxes
- Two fillers process the boxes
- Two packagers complete the final packaging
- Items move through queues between stages

### Inputs
- Total number of items to produce
- Time ranges for each operation:
  - Production min/max time
  - Filling min/max time
  - Packaging min/max time

Example input:
```
Total number of items: 10
Producer time range: 1-3 seconds
Filler time range: 2-4 seconds
Packager time range: 1-2 seconds
```

### Outputs
- Real-time operation logs with timestamps
- Queue size updates
- Worker status updates
- Operation completion messages

Example output:
```
Producer has enqueued a new box 1 to filling queue (filling queue size is 1): 14:30:22
Filler 1 started filling the box 1 (filling queue size is 0): 14:30:23
Filler 1 finished filling the box 1: 14:30:25
```

## 3. Implementation Details

### Core Components

#### Dynamic Integer Queue
```cpp
class HW7DynIntQueue {
private:
    ItemNode* front;
    ItemNode* rear;
    int currentSize;
public:
    // Queue operations
    void enqueue(int id);
    void dequeue(int& id);
    bool isEmpty() const;
    // ... other methods
};
```

#### Worker Threads
- Producer Thread: Creates empty boxes
- Filler Threads (2): Fill empty boxes
- Packager Threads (2): Package filled boxes

### Key Features

#### Thread Synchronization
- Mutex-protected queue operations
- Thread-safe console output
- Synchronized access to shared resources

#### Queue Management
- Dynamic memory allocation
- FIFO operation
- Thread-safe enqueue/dequeue
- Size tracking

## 4. Usage Instructions

### Requirements
- C++ compiler with C++11 support
- Standard library support for threads
- Sufficient memory for queue operations

### Basic Usage
```cpp
int main() {
    // Configure simulation parameters
    int total_box_count = 10;
    int min_production = 1, max_production = 3;
    int min_filling = 2, max_filling = 4;
    int min_packaging = 1, max_packaging = 2;

    // Create and start threads
    thread producer(produce, min_production, max_production, ptm);
    thread filler1(fill, 1, ref(packagingqueue), min_filling, max_filling, ptm);
    // ... start other threads
    
    // Wait for completion
    producer.join();
    // ... join other threads
}
```

## 5. Error Handling

The system handles several error conditions:
- Queue underflow protection
- Memory allocation failures
- Thread synchronization issues
- Invalid time ranges

Constraints:
- Positive time ranges required
- Sufficient memory for queue operations
- Valid thread creation conditions

## 6. Example Session

```
Please enter the total number of items: 5
Please enter the min-max waiting time range of producer:
Min: 1
Max: 3
Please enter the min-max waiting time range of filler workers:
Min: 2
Max: 4
Please enter the min-max waiting time range of packager workers:
Min: 1
Max: 2

Simulation starts 14:30:00
Producer has enqueued a new box 1 to filling queue (filling queue size is 1): 14:30:02
Filler 1 started filling the box 1 (filling queue size is 0): 14:30:03
// ... simulation continues
End of simulation: 14:35:00
```

Note: The implementation uses mutexes for thread synchronization and dynamic memory management for queue operations. The simulation provides real-time feedback about the production line's status and ensures thread-safe operations throughout the process.
