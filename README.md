# Nexo - File System Simulator

## Overview

Nexo is an interactive command-line file system simulator that mimics the behavior of a real operating system's file management system. It provides a hybrid environment where you can create, navigate, and manage real files (on your computer) and virtual folders (in memory), just like you would in a real file system. Additionally, it includes a unique scheduling feature that allows you to batch multiple commands and execute them using different scheduling algorithms.

## What is Nexo?

Think of Nexo as a "mini operating system" that runs inside your computer. It creates a hybrid file system where:

- **Files are real**: Created on your actual computer's filesystem
- **Folders are virtual**: Organized in memory using a tree structure
- **Automatic cleanup**: When you exit, all created files are automatically deleted and memory is freed

You can:
- Create and organize virtual folders (directories)
- Create and manage real files on your computer
- Navigate between different locations
- Search for files and folders
- Execute multiple commands in sequence using scheduling algorithms

## Key Features

### 🗂️ File System Operations
- **Create folders** (`mkdir`) - Make new directories
- **Create files** (`touch`) - Create empty files
- **Navigate** (`cd`) - Move between folders
- **List contents** (`ls`) - See what's in the current folder
- **View current location** (`pwd`) - Show your current path
- **Remove files** (`rm`) - Delete files with confirmation
- **Remove folders** (`rmdir`) - Delete folders with confirmation
- **View file contents** (`cat`) - Display file contents
- **Write to files** (`echo`) - Add text to files
- **Search files** (`find`) - Find files by name
- **Search folders** (`finddir`) - Find folders by name

### ⏰ Command Scheduling
- **Batch execution** - Run multiple commands in sequence
- **FCFS (First-Come First-Served)** - Execute commands in the order they were entered
- **SJF (Shortest Job First)** - Execute commands based on their estimated execution time

## Project Structure

```
Nexo/
├── main.c          # Main program entry point and command loop
├── shell.c         # File system operations (mkdir, touch, ls, etc.)
├── shell.h         # Header file for shell functions
├── scheduling.c    # Command scheduling algorithms (FCFS, SJF)
├── scheduling.h    # Header file for scheduling functions
├── helper.c        # Utility functions and data structures
├── helper.h        # Header file for helper functions and structures
├── Makefile        # Build configuration
└── README.md       # This file
```

## How to Use

### Building the Project

1. Make sure you have a C compiler (like GCC) installed
2. Open a terminal in the project directory
3. Run the following command to compile:

```bash
make
```

This will create an executable called `nexo`.

### Running Nexo

1. Start the program:
```bash
./nexo
```

2. You'll see a prompt like this:
```
nexo>
```

3. Type commands and press Enter. For example:
```
nexo> mkdir documents
nexo> cd documents
nexo> touch myfile.txt
nexo> ls
```

### Available Commands

| Command | Description | Example |
|---------|-------------|---------|
| `mkdir <name>` | Create a new folder | `mkdir projects` |
| `cd <name>` | Change to a folder | `cd projects` |
| `cd ..` | Go to parent folder | `cd ..` |
| `pwd` | Show current location | `pwd` |
| `ls` | List files and folders | `ls` |
| `touch <name>` | Create a new file | `touch notes.txt` |
| `cat <file>` | View file contents | `cat notes.txt` |
| `echo <file>` | Write text to a file | `echo notes.txt` |
| `rm <file>` | Delete a file | `rm notes.txt` |
| `rmdir <folder>` | Delete a folder and all its contents | `rmdir projects` |
| `find <name>` | Search for a file | `find notes.txt` |
| `finddir <name>` | Search for a folder | `finddir projects` |
| `clear` | Clear the screen | `clear` |
| `scheduling` | Enter scheduling mode | `scheduling` |
| `help` | Show available commands | `help` |
| `exit` | Exit the program | `exit` |

### Using the Scheduling Feature

The scheduling feature allows you to execute multiple commands in sequence using different algorithms:

1. Type `scheduling` and press Enter
2. Enter the number of commands you want to execute
3. Type each command one by one
4. Choose an algorithm:
   - **FCFS (1)**: Executes commands in the order you entered them
   - **SJF (2)**: Executes commands based on their estimated execution time (faster commands first)

Example scheduling session:
```
nexo> scheduling
How many commands you want to execute? 3
nexo> mkdir test
nexo> touch file.txt
nexo> ls

Choose the algorithm: 
[1] FCFS (First-Come First-Served)
[2] SJF (Shortest Job First)

Enter: 1
```

## How It Works

### File System Structure
Nexo uses a hybrid approach:
- **Virtual Folders**: Organized in memory using a tree-like structure
- **Real Files**: Created on your actual computer's filesystem
- **Folder Structure**: Each virtual folder can contain other folders and references to real files
- **Root**: The system starts with a "home" folder as the root
- **Cleanup**: When exiting, all real files are deleted and virtual folder memory is freed

### Command Processing
1. You type a command at the `nexo>` prompt
2. The system parses your input into words
3. It looks for the command in its list of available commands
4. If found, it executes the corresponding function
5. If not found, it shows an error message

### Scheduling Algorithms
- **FCFS**: Simple queue-based execution - first command entered is executed first
- **SJF**: Commands are sorted by estimated execution time before running

## Important Notes

- **Hybrid System**: Files are real and created on your computer; folders are virtual and exist only in memory while the program is running
- **Automatic Cleanup**: All files created by Nexo are deleted and all memory is freed when you exit the program
- **Confirmation**: The `rm` and `rmdir` commands ask for confirmation before deleting files or folders
- **Echo Limitation**: When using scheduling, `echo` commands collect input before any scheduled commands run
- **Exit Restriction**: You cannot use `exit` inside scheduling mode

## Limitations and Potential Errors

### System Limitations
- **Memory Constraints**: The virtual folder system is limited by available memory - creating too many folders may cause memory issues
- **Name Length**: File and folder names have practical length limits
- **Nesting Depth**: Very deep folder structures may cause stack overflow
- **File Size**: Real files are limited by available disk space
- **No Persistence**: All virtual folders and real files are automatically deleted when the program exits

### Command Limitations
- **File Operations**: 
  - `touch` creates real files on your computer's filesystem
  - `cat` reads from real files created by the simulator
  - `echo` writes to real files on your computer
- **Folder Operations**:
  - `mkdir` creates virtual folders in memory only
  - `rmdir` recursively deletes virtual folders and removes real files within them
  - Requires confirmation before deletion
- **Navigation**:
  - `cd ..` won't work when already at the root ("home") folder
  - Cannot navigate to non-existent folders

### Error Scenarios
- **Duplicate Names**: The system prevents creating files or folders with the same name in the same location (shows "File already exists" or "Folder already exists")
- **Invalid Commands**: Unknown commands will show an error message
- **Missing Arguments**: Some commands require arguments and will fail without them
- **File Not Found**: Operations on non-existent files will fail
- **Folder Not Found**: Operations on non-existent folders will fail
- **Permission Issues**: The simulator doesn't implement real file permissions

### Scheduling Limitations
- **Recursive Scheduling**: Cannot call `scheduling` command from within scheduling mode
- **Input Collection**: All `echo` inputs are collected before any commands execute
- **No Exit**: `exit` command is disabled during scheduling mode
- **Algorithm Limitations**: SJF uses estimated execution times, not actual measurements
- **Memory Usage**: Storing many commands for scheduling increases memory usage

### Technical Limitations
- **Single User**: No multi-user support
- **No Networking**: Cannot access remote files or systems
- **No File Types**: All files are treated as text files
- **No Compression**: No support for compressed files
- **No Encryption**: No file encryption or security features
- **Platform Dependent**: Requires a C compiler and may behave differently on different systems

## Getting Help

- Use the `help` command to see all available commands
- Each command has built-in error checking and helpful messages
- The system will guide you if you make mistakes

## Cleaning Up

To remove compiled files and start fresh:
```bash
make clean
```

## Why Nexo?

This project demonstrates fundamental concepts of:
- **File System Design**: How directories and files are organized
- **Command Line Interfaces**: How users interact with systems
- **Process Scheduling**: How multiple tasks can be organized and executed
- **Data Structures**: Trees, linked lists, and dynamic memory management
- **System Programming**: Low-level file and memory operations

Nexo is perfect for learning about operating system concepts, file management, and command-line interfaces in a safe, controlled environment.

