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

## Command Reference

###  Core File Operations

```CREATE filename```
Creates a file with a root version (ID 0), empty content, and an initial snapshot
message. Note that the root is marked as a snapshot.

```READ filename```
Displays the content of the file’s currently active version.

```INSERT filename content```
Appends content to the file. This creates a new version if the active version is already a snapshot; otherwise, it modifies the active version in place.

```UPDATE filename content```
Replaces the file’s content. Follows the same versioning logic as INSERT.

```SNAPSHOT filename message```\
Marks the active version as a snapshot, making its content immutable. It stores the provided message and the current time.

```ROLLBACK filename version_id```
Sets the active version pointer to the specified versionID. If no ID is provided, it rolls back to the parent of the current active version.

```HISTORY filename```
Lists all snapshotted versions of the file chronologically, which lie on the path from active node to the root in the file tree, showing their ID, timestamp, and message.


### System-Wide Analytics

- RECENTFILES k
- BIGGESTTREES k