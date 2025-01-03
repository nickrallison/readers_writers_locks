# Readers-Writers Locks

## Overview
This project provides implementations of three different solutions to the classic Readers-Writers problem in concurrent programming. The Readers-Writers problem involves managing access to a shared resource, where multiple readers can access the resource simultaneously, but writers require exclusive access. The project is implemented in C and uses semaphores to ensure proper synchronization.

## Features
- **Three Solutions**: Implements three distinct solutions to the Readers-Writers problem, each with different trade-offs in terms of fairness and performance.
- **Performance Metrics**: Tracks and outputs average turnaround times (TAT) for readers and writers, providing insights into the efficiency of each solution.
- **Thread Management**: Utilizes POSIX threads (pthreads) to simulate concurrent readers and writers.
- **Semaphore Implementation**: Includes a custom semaphore implementation to manage synchronization between threads.

## Project Structure
The project is organized into the following files:
- **main.c**: The entry point of the program, responsible for running the three solutions and printing performance metrics.
- **semaphore.c**: Implements the custom semaphore functionality, including initialization, wait, signal, and destruction.
- **semaphore.h**: Header file defining the semaphore data structures and function prototypes.
- **sol1.c**: Implements the first solution to the Readers-Writers problem.
- **sol2.c**: Implements the second solution to the Readers-Writers problem.
- **sol3.c**: Implements the third solution to the Readers-Writers problem.
- **CMakeLists.txt**: CMake configuration file for building the project.

## Key Files
- **main.c**: Coordinates the execution of the three solutions and prints the average turnaround times for readers and writers.
- **semaphore.c**: Contains the implementation of the semaphore functions used for thread synchronization.
- **sol1.c**, **sol2.c**, **sol3.c**: Implement the three different solutions to the Readers-Writers problem, each with its own approach to managing reader and writer access.

## Usage
To build and run the project, follow these steps:

1. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run the Program**:
   ```bash
   ./CPSC457_A4
   ```

   The program will execute the three solutions and output the average turnaround times for readers and writers in seconds.

## Output
The program outputs the following metrics for each solution:
- **Writers**: Number of writers in the simulation.
- **AVG reader TAT**: Average turnaround time for readers.
- **AVG writer TAT**: Average turnaround time for writers.
- **AVG TAT**: Overall average turnaround time for both readers and writers.

Example output:
```
Readers-Writers Solution 1 (time in seconds)
Writers  AVG reader TAT  AVG writer TAT  AVG TAT
0        0.161316        N/A             0.161316
1        0.127671        0.158353        0.130460
...
```

## Testing
The project does not include a formal testing framework, but the correctness of the solutions can be verified by analyzing the output metrics and ensuring that the average turnaround times are reasonable for the given number of readers and writers.

## Acknowledgments
- This project was developed as part of a course assignment for CPSC 457.
- Special thanks to the teaching staff for their guidance and support.
