## Contents

The project includes two implementations:

### 1. Mobile Telephone Service Office (MTSO) Simulation

This program simulates a simplified mobile call management system.

The system handles three types of calls:

- **Emergency Calls** (highest priority)
- **Voice Calls**
- **Data Calls** (lowest priority)

Calls are stored in a **priority queue using a singly linked list**.

Rules used in the system:

- Emergency calls are inserted after existing emergency calls but before all other calls.
- Voice calls are inserted after emergency and voice calls but before data calls.
- Data calls are always inserted at the end of the queue.

Menu options:

1. Data Call coming  
2. Voice Call coming  
3. Emergency Call coming  
4. Serve a call  
5. Dismiss calls with least priority  
6. Display all calls  
7. Exit  

Features:

- Priority-based call insertion
- Serving calls from the front of the queue
- Removing lowest priority calls
- Saving calls to a file on exit
- Loading saved calls when the program starts

---

### 2. Doubly Sorted Linked List

This program implements a **doubly linked list sorted by key**.

Each node contains:

- Key (used for sorting)
- Information field
- Pointer to previous node
- Pointer to next node

Supported operations:

- Initialize the list
- Insert a new element in sorted order
- Delete an element by key
- Retrieve the deleted element information
- Traverse the list forward and backward
- Destroy the list

---

## Compilation

Use Case 1:

```bash
gcc main.c mtso.c -o mtso
./mtso
```

Use Case 2:

```bash
gcc main.c dsorted.c -o dsorted
./dsorted
```

