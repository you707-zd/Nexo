# Nexo

## Scope

Nexo is a C-based command-line simulator that implements:
- File system operations
- Shell-style command execution
- CPU scheduling simulation for command batches

The project models operating-system behavior for learning and experimentation.

## Purpose

The project was built to practice:
- Directory tree design and traversal
- Command parsing and dispatch
- Scheduling policy implementation (FCFS, SJF)
- Dynamic memory management for hierarchical data

## Architecture

Nexo uses a hybrid storage model:
- Directory nodes are maintained in memory as a tree.
- Files are created and modified on disk.
- Folder deletion is recursive and removes contained file entries.
- Program exit triggers cleanup of allocated memory and generated files.

## Components

```
Nexo/
├── main.c          # Entry point and REPL loop
├── shell.c         # Command handlers for file/folder operations
├── shell.h         # Shell interfaces
├── scheduling.c    # FCFS and SJF scheduling logic
├── scheduling.h    # Scheduling interfaces
├── helper.c        # Shared utilities and structures
├── helper.h        # Helper interfaces and types
├── Makefile        # Build targets
└── README.md
```

## Build and Run

Build:
```bash
make
```

Run:
```bash
./nexo
```

Prompt:
```
nexo>
```

Clean artifacts:
```bash
make clean
```

## Command Interface

| Command | Behavior |
|---------|----------|
| `mkdir <name>` | Create folder node in current directory |
| `cd <name>` | Move to child folder |
| `cd ..` | Move to parent folder |
| `pwd` | Print current path |
| `ls` | List files and folders |
| `touch <name>` | Create file on disk and track it in current node |
| `cat <file>` | Print contents of a tracked file in the current directory |
| `echo <file>` | Append user input to a tracked file in the current directory |
| `rm <file>` | Remove file (confirmation required) |
| `rmdir <folder>` | Recursively remove folder subtree (confirmation required) |
| `find <name>` | Search file by name |
| `finddir <name>` | Search folder by name |
| `clear` | Clear terminal output |
| `scheduling` | Enter batch scheduling mode |
| `help` | Print command list |
| `exit` | Exit program and run cleanup |

## Scheduling Mode

Flow:
1. Enter `scheduling`.
2. Provide number of commands.
3. Enter commands.
4. Select algorithm:
   - `FCFS`: Execute in input order.
   - `SJF`: Sort by estimated runtime, then execute.

Constraints:
- `scheduling` cannot be called from scheduling mode.
- `exit` is disabled inside scheduling mode.
- `echo` input is collected before batch execution starts.

## Execution Model

Command processing:
1. Read input line.
2. Tokenize into command and arguments.
3. Resolve command handler.
4. Validate arguments.
5. Execute handler and report result/error.

File system behavior:
- Root node is the top-level folder.
- `cd ..` at root is blocked.
- Duplicate names in one directory are rejected.
- Recursive traversal is used by search and deletion operations.

## Limitations

System-level:
- In-memory folder tree size depends on available memory.
- Deep folder nesting can increase recursion depth risk.
- File operations depend on host filesystem permissions and disk availability.
- Platform behavior can vary by C runtime and OS.

Model-level:
- No persistence across sessions for the virtual tree.
- No multi-user model.
- No networking support.
- No permission model inside the simulator.
- No file type metadata beyond plain file handling.
- Text-oriented file handling only: `cat` and `echo` use text-style read/write operations.
- `cat` and `echo` operate only on files tracked in the current folder tree node; untracked paths/files are rejected as "no such file".
- `touch`, `cat`, and `echo` enforce an extension allowlist: only `.txt` and `.csv` are accepted.
- File validation is extension-based only; file content is not inspected.

Scheduling-level:
- SJF uses estimated, not measured, execution time.
- Large batches increase memory usage for queued commands.

## Error Conditions

Typical failure cases:
- Unknown command
- Missing required arguments
- Duplicate file/folder name in current directory
- Target file/folder does not exist
- Invalid navigation target

