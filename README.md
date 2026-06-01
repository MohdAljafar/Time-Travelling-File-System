# Time-Travelling File System

A simplified in-memory version control system inspired by Git.

This project was developed as part of COL106 (Data Structures and Algorithms).

## Features

- Version-controlled files
- Snapshot-based immutable versions
- Rollback support
- Branching version history
- Fast version lookup using HashMap
- Tree-based version storage
- System-wide analytics

## Data Structures Used

### Tree
Stores the version history of each file.

### HashMap
Provides O(1) average lookup of versions by version ID.

### Heap
Used for:
- Recent file tracking
- Largest version-tree tracking

---

## Build Instructions

### Compile

```
g++ .\src\*.cpp -o timeTravel
.\timeTravel.exe
```