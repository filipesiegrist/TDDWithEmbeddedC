# CircularBuffer Module

## AI Summary

### 1. Overview
The CircularBuffer is a fixed-capacity, First-In-First-Out (FIFO) data structure designed for embedded software systems. It provides a bounded queue where items are retrieved in the exact order they were inserted. Memory is allocated statically or upfront during creation to ensure predictable runtime execution without dynamic reallocation during operation.

### 2. Terminology & Core States
- Capacity: The maximum number of elements the buffer can hold at any given time.
- Count: The current number of elements stored in the buffer.
- Head (Write Index): The location where the next incoming element will be stored.
- Tail (Read Index): The location from which the next element will be retrieved.
- Empty State: Occurs when Count is zero (Head equals Tail with no items present).
- Full State: Occurs when Count equals Capacity.

### 3. Operations Overview
#### Lifecycle Management
- Create / Initialization: Instantiates or configures the buffer instance with a defined capacity and element size. Sets all tracking pointers and counters to their default initial state.
- Destroy / Teardown: Releases resources or clears the instance state when the buffer is no longer needed.

#### Data Transfer
- Put / Push / Enqueue: Writes a single item into the buffer at the current Head position, then advances Head and increments Count.
- Get / Pop / Dequeue: Retrieves and removes a single item from the buffer at the current Tail position, then advances Tail and decrements Count.

#### State Querying
- Is Empty: Queries whether the buffer currently holds zero elements.
- Is Full: Queries whether the buffer has reached its maximum capacity.
- Get Capacity: Queries the total maximum number of items the buffer can store.
- Get Count / Get Size: Queries the current number of items stored in the buffer.
- Clear / Flush: Resets the buffer to the empty state without destroying the buffer structure itself.

### 4. Business Rules & Behavior
#### Rule 1: First-In, First-Out (FIFO) Ordering
Items must be retrieved in the exact sequential order they were added. The first item written to the buffer must be the first item read from it.

#### Rule 2: Wrap-Around Boundary Handling
When either Head or Tail reaches the end of the internal storage boundary, advancing the pointer must cleanly wrap around to the beginning (index 0). This circular movement ensures continuous operation within fixed memory boundaries.

#### Rule 3: Overflow Protection (Buffer Full Behavior)
Attempting to insert an item into a full buffer must fail gracefully.

The operation must return an explicit status (e.g., false or an error status) and must not overwrite unread data or alter the existing state of the buffer.

#### Rule 4: Underflow Protection (Buffer Empty Behavior)
Attempting to retrieve an item from an empty buffer must fail gracefully.
The operation must return an explicit status and must not alter the output buffer or advance the read index.

#### Rule 5: State Consistency
Inserting an item increases Count by 1 and transitions the buffer out of the Empty state.
Removing an item decreases Count by 1 and transitions the buffer out of the Full state.
Count must never be negative and must never exceed Capacity.

#### Rule 6: Defensive Execution & Null Safety
Operations receiving invalid or uninitialized buffer instances must immediately abort the operation gracefully without causing hardware faults, memory corruption, or system crashes.

#### Other important info:
- Queuing an item don't change its tail
- Dequeuing an item don't change its head
- There's an issue to identify if the queue is either full or empty when `head == tail` that has two solutions:
  - 1. Add one more position to the array that won't be used
  - 2. Keep a separate `Counter` along with the head and the tail
  - As it's a generic buffer, it's more memory efficient to keep a 2 bytes counter at the memory than reserving a possibly large item at the memory.

#### Parameters Business Rules
- `GetSize()` = `Buffer_Size`
- `IsEmpty()` = `(Buffer_Size == 0)`
- `IsEmpty()` = `(Head == Tail && Buffer_Size == 0)`
- `IsFull()` = `(Buffer_Size == CIRCULARBUFFER_CAPACITY)`


## Design decisions
- It will have a fixed size but I'll use dynamic memory allocation to allow multiple instancies
- In order to avoid memory leaks and allow test-driven memory, I'll use an interface module called `Memory` with `Allocator()` and `Deallocator()` which, in practice, is just an interface to `stdlib`. But this will allow me to spy into the buffers and guarantee memory integrity.
- Simple tests will use float values.
- Later I'll add more tests with custom types


## Test List (ZOMBIES Framework for Generic Types)

### Z - Zero
- [X] **Newly created buffer is empty**: Verify that `IsEmpty` returns true immediately after creation.
- [X] **Newly created buffer is not full**: Verify that `IsFull` returns false after creation.
- [X] **Newly created buffer has size zero**: Verify that `GetCount` returns 0.
- [X] **Get on empty buffer fails (Underflow)**: Verify that attempting to retrieve an item from a newly created buffer returns false or an error status without modifying the output pointer.

### O - One
- [X] **Single item insertion (Float)**: Verify that putting a single `float` item makes `IsEmpty` return false.
- [X] **Single item retrieval and memory integrity (Float)**: Verify that putting a `float` and getting it copies the exact byte representation to the destination pointer.
- [X] **Return to empty state**: Verify that inserting one generic item and removing it leaves the buffer empty (`IsEmpty` returns true, `GetCount` is 0).
- [X] **Count update on single item**: Verify that inserting one item updates `GetCount` to 1, and retrieving it reduces `GetCount` back to 0.

### M - Many
- [X] **Multiple primitive items FIFO ordering**: Verify that inserting `float` values (e.g., 1.5f, 2.7f, 3.14f) retrieves them in exact sequence 1.5f, then 2.7f, then 3.14f.
- [X] **Multiple items count tracking**: Verify that inserting N generic items updates `GetCount` to N, and removing M items updates `GetCount` to N - M.
- [X] **Interleaved Put and Get with generic types**: Verify that performing alternating operations (e.g., Put, Put, Get, Put, Get) maintains strict FIFO order and correct byte copying.
- [X] **Multiple Buffers in parallel**: Create two buffers and guarantee both don't interfere with each other.
- [ ] **Multiple custom types / Structs FIFO ordering**: Verify that inserting and retrieving custom `struct` instances copies all internal fields correctly without data corruption.

### B - Boundaries
- [X] **Buffer reaches full capacity**: Verify that adding items up to maximum capacity transitions `IsFull` to true.
- [X] **Overflow protection**: Verify that attempting to put an item into a full buffer fails, returns false/error, and preserves existing buffer contents without overwriting unread memory.
- [X] **Transition out of full state**: Verify that removing a single item from a full buffer transitions `IsFull` back to false.
- [X] **Pointer Wrap-Around (Write)**: Verify that inserting generic items past the physical array boundary correctly calculates byte offsets and wraps around to index 0.
- [X] **Pointer Wrap-Around (Read)**: Verify that retrieving generic items when the read index reaches the array boundary correctly wraps around to index 0 and maintains byte integrity.
- [ ] **Continuous Wrap-Around cycles**: Verify that the buffer operates correctly after multiple full cycles of wrapping around capacity limits for various element sizes.

### I - Interfaces
- [X] **Create lifecycle with element size**: Verify that `Create` initializes all internal variables, pointers, capacity, and `element_size` settings correctly.
- [X] **Destroy lifecycle**: Verify that `Destroy` cleans up allocated memory blocks properly without memory leaks.
- [ ] **Clear operation**: Verify that calling `Clear` on a buffer containing generic items resets `GetCount` to 0, sets `IsEmpty` to true, and sets `IsFull` to false.
- [ ] **GetCapacity and GetElementSize queries**: Verify that `GetCapacity` and `GetElementSize` return the configured values throughout the buffer lifecycle.

### E - Exceptions
- [X] **Null instance safety**: Verify that passing a `NULL` buffer pointer to any function (`Put`, `Get`, `IsEmpty`, `IsFull`, `GetCount`, `Clear`, `Destroy`) is handled gracefully without causing segmentation faults.
- [X] **Null output pointer on Get**: Verify that calling `Get` with a valid buffer but a `NULL` destination pointer (`void* item`) fails safely without attempting a `memcpy`.
- [X] **Null input pointer on Put**: Verify that calling `Put` with a `NULL` source data pointer (`const void* item`) fails safely without attempting a `memcpy`.
- [X] **Zero capacity or zero element size creation**: Verify that attempting to create a buffer with capacity 0 or element size 0 fails safely and returns `NULL`.

### S - Simple Behaviors & Refactoring
- [X] **Hard-coded return passes**: Use hard-coded return values initially (e.g., `IsEmpty` always returning `true`) to validate Ceedling test harness setup.
- [X] **Decoupled memory allocator integration**: Verify that internal buffer allocation (for tracking structure and element storage) routes through the `MemoryService` interface rather than direct `stdlib` calls.

### Missing things:
- [X] Add custom capacities
- [X] Check for Capacities above 50
- [X] Check circular logic
- [X] Custom Capacities
- [X] Destroy (simple)
- [X] Destroy do actually work
- [X] Check for NULL at the Internal Array Structure
- [X] Memory limits/overflow at size allocation
- [ ] Multiple Types
- [ ] Memory Integrity throughout Buffer stress test
- [X] Prevent adding item to a full buffer
