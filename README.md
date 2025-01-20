# JumpList Project

This project is an implementation of a modified linked list data structure called **JumpList**. It assesses your knowledge of pointers, dynamic memory management, and classes.

---

## Motivation

The standard linked list data structure is simple but inefficient for traversing nodes during operations like searching. The JumpList introduces **jump pointers**, acting as a "fast lane" to speed up traversal. This project involves creating a software library for the JumpList data structure, which maintains an additional "jump" pointer for efficient operations. The JumpList is designed to maintain an **alphabetically ordered list of strings** and optimize operations through these jump pointers.

---

## Overview of the JumpList Data Structure

### Key Features:
1. **Alphabetical Order:** Strings are stored in alphabetical order.
2. **Jump Pointers:** Some nodes, known as *jump nodes*, have a pointer (`jump`) to the next jump node, skipping intermediate nodes.
3. **Segments:** The list is divided into segments of nodes, and jump pointers link the segments.
4. **Constraints:**
   - The maximum gap size between two jump nodes is defined as `MAX_GAP_SIZE = 5`.
   - The head of the list is always a jump node.

---

## Supported Operations

### 1. `size()`
- **Description:** Returns the number of elements stored in the JumpList.
- **Example:** For a list containing `a, b, blah, c, cat, d, etc, ooo..., x, zzz`, the size is `10`.

### 2. `find(const string& s)`
- **Description:** Returns `true` if the string `s` exists in the list, otherwise `false`.
- **Details:**
  - Searches the *fast lane* (jump pointers) to identify the relevant segment.
  - Performs a linear search within the segment.

### 3. `get(int i)`
- **Description:** Returns the string stored at index `i` (0-based indexing).
- **Example:**
  - `get(0)` returns `"a"`.
  - `get(4)` returns `"cat"`.
  - Out-of-bounds indices return an empty string.

### 4. `print()`
- **Description:** Returns a string representation of the JumpList contents, including:
  - All strings in order.
  - All strings in jump nodes.
  - Gap sizes of the jump nodes.
- **Output Format:**
  ```
  a b blah c cat d etc ooo... x zzz
  a d x
  5 3 2
  ```
  
### 5. `prettyPrint()` (Bonus)
- **Description:** Similar to `print()`, but includes visual arrows to represent pointers.
- **Output Format:**
  ```
  a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz
  a -------------------------------> d ---------------------> x
  5                                  3                        2
  ```

### 6. `insert(const string& s)`
- **Description:** Inserts a string `s` into the list while maintaining alphabetical order.
- **Special Cases:**
  - If the string already exists, returns `false`.
  - If a segment exceeds `MAX_GAP_SIZE` after insertion, it splits into two segments of equal size (or nearly equal, with the first segment slightly longer).
- **Example:**
  - Insert `"dog"` into the list:
    ```
    a --> b --> blah --> c --> cat --> d --> dog --> etc --> ooo... --> x --> zzz
    a -------------------------------> d -----------------------------> x
    5                                  4                                2
    ```
  - Insert `"A"` into the list:
    ```
    A --> a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz
    A --------------> blah ----------------> d ---------------------> x
    3                 3                      3                        2
    ```

### 7. `erase(const string& s)`
- **Description:** Removes a string `s` from the list if it exists.
- **Special Cases:**
  - If `s` is a jump node, segments are merged. If the resulting segment exceeds `MAX_GAP_SIZE`, it splits.
  - If the head is removed, the next node becomes the new head and a jump node.
- **Example:**
  - Delete `"blah"`:
    ```
    a --> b --> c --> cat --> d --> etc --> ooo... --> x --> zzz
    a ----------------------> d ---------------------> x
    4                         3                        2
    ```
  - Delete `"x"`:
    ```
    a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> zzz
    a -------------------------------> d
    5                                  4
    ```

---

## Compilation and Testing

### Prerequisites:
- Linux environment.
- GCC compiler.
- Make utility.

### Steps to Compile and Run:
1. Clone the repository and navigate to the folder containing the project files.
2. Run the following command to compile the project:
   ```bash
   make
   ```
   This will generate an executable named `JumpListTesterMain`.
3. Execute the program with test inputs:
   ```bash
   ./JumpListTesterMain a
   ```
   or
   ```bash
   ./JumpListTesterMain a b c d
   ```

---

## File Structure
- `JumpList.h`: Header file containing the JumpList class definition.
- `JumpList.cpp`: Implementation of the JumpList class methods.
- `JumpListTesterMain.cpp`: Tester program for executing test cases.
- `Makefile`: Build script for compiling the project.

---

## Example Output
For a list containing `a, b, blah, c, cat, d, etc, ooo..., x, zzz`, the following outputs are expected:

1. **`print()` Output:**
   ```
   a b blah c cat d etc ooo... x zzz
   a d x
   5 3 2
   ```

2. **`prettyPrint()` Output:**
   ```
   a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz
   a -------------------------------> d ---------------------> x
   5                                  3                        2
   ```

---