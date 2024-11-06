# Timing App
Records execution time of different algorithms across specified test cases saved in .txt file for your desired repeatations. Runs on Windows 64-bit PC and Raspberry Pi 4 ARM architecture.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Built With](#built-with)
- [What's Next](#whats-next)
- [Usage](#usage)

## Overview
The Timing App is a C++ program designed to accurately measure the execution time of various algorithms across different architectures, including Windows 64-bit PCs and Raspberry Pi 4 (ARM). It allows users to benchmark algorithm performance through command-line execution with results saved in a `.txt` file for specified test cases and repetition counts.

## Features
- **Precise Execution Time Measurement**: Enables accurate measurement and recording of execution times for any algorithm by calling a dedicated timing function.
- **Cross-Architecture Compatibility**: Runs seamlessly on both Windows 64-bit and Raspberry Pi 4 ARM architecture.
- **Decimal Conversion**: Automatically converts very small values or values in scientific notation to decimal format for better readability.
- **Custom Test Cases**: Allows users to load test cases from a `.txt` file, specifying the desired number of repetitions for each case.
- **Python Scripting**: Automates the generation of test scripts with Python, simplifying the process of creating and managing multiple test cases.

## Built With
- **C++**: Core language used for timing functions and algorithm execution.
- **CMake**: Build configuration management.
- **Python**: Automates the creation of test scripts and data processing.

## What's Next
This program aims to delever data that researchers can leverage with Python's `pandas` and `matplotlib` libraries to:
- **Visualize Timing Data**: Generate plots and visualizations to easily interpret the performance of algorithms across different test cases.
- **Make Inferences**: Analyze and compare execution times to derive meaningful insights for performance optimization.

## Usage
1. Place your test cases in a `.txt` file.
2. Specify the desired number of repetitions for each test case.
3. Run the program from the command line, specifying your test file and options for timing measurements.


