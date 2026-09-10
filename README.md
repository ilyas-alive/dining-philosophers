*This project has been created as part of the 42 curriculum by iel-ghan.*

# Codexion

## Description

Codexion is a multithreaded simulation inspired by the classic Dining Philosophers problem. In this project, multiple coders sit in a circle and share limited resources (USB dongles) to alternate between compiling, debugging, and refactoring. 

The main goal is to manage shared resources using threads and mutexes while avoiding common concurrency issues like deadlocks, race conditions, and starvation. 

The project supports two scheduling policies using a custom linked-list queue:
- **FIFO** (First In, First Out)
- **EDF** (Earliest Deadline First)

## Instructions

### Compilation

To compile the project, run:
```bash
make
```

### Execution

The program requires exactly 8 arguments:
```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

**Example:**
```bash
./codexion 5 3000 200 200 200 10 400 edf
```

**Arguments:**
- `number_of_coders`: Number of threads and shared dongles.
- `time_to_burnout`: Max time (in ms) a coder can wait before they burn out.
- `time_to_compile`: Time (in ms) spent compiling (requires 2 dongles).
- `time_to_debug`: Time (in ms) spent debugging.
- `time_to_refactor`: Time (in ms) spent refactoring.
- `number_of_compiles_required`: Target number of compiles for the simulation to stop.
- `dongle_cooldown`: Wait time (in ms) before a released dongle can be taken again.
- `scheduler`: Must be `fifo` or `edf`.

## Resources

- POSIX Threads (pthreads) documentation (`man pthreads`).
- The Dining Philosophers Problem and Coffman's conditions for deadlocks.
- Earliest Deadline First (EDF) scheduling.
- **AI Usage:** AI was used only to help understand multithreading concepts, find resources   and debugging were done manually.

## Blocking cases handled

- **Deadlock prevention (Coffman's conditions):** To stop a circular wait (where everyone holds one dongle and waits forever for the second), every coder takes their left dongle then their right, except for the very last coder who takes the right one first.
- **Starvation prevention:** A custom linked list is used as a queue. Coders are added to the back (FIFO) or sorted by their burnout deadline (EDF) so no coder is skipped forever.
- **Cooldown handling:** If a dongle is released, waiting coders use `pthread_cond_timedwait` to wait exactly until the cooldown time finishes before taking it.
- **Precise burnout detection:** A separate monitor thread constantly checks the coders' timestamps to stop the program the exact moment someone burns out.
- **Log Serialization:** All printed messages are locked with a mutex so the text doesn't mix together on the screen. The "burned out" message is always forced to be the very last thing printed.

## Thread synchronization mechanisms

This project uses specific POSIX tools to keep shared data safe and coordinate access to resources:

- **`pthread_mutex_t` (Mutexes):**
  - `print_lock`: Makes sure only one thread can print to the terminal at a time.
  - `over_lock`: Protects the simulation status so threads safely know when to stop.
  - `time_mutex`: Protects each coder's personal data (last compile time and compile count).
  - `dongle->mutex`: Protects the state (availability and cooldown) and waiting queue of each individual dongle.

- **`pthread_cond_t` (Condition Variables):**
  - `dongle->cond`: Used to put coders to sleep without wasting CPU. It wakes them up using `pthread_cond_broadcast` when a dongle is released or when the simulation ends.

- **Example of preventing race conditions:**
  When a coder updates their `count` of finished compiles, they lock `time_mutex`. The monitor thread also locks `time_mutex` before reading that count. This prevents a race condition where the monitor might read a broken or half-updated number while the coder is changing it.

- **Thread-safe communication between coders and the monitor:**
  The coders and the monitor never talk directly to each other. They communicate safely through shared variables (`is_over` and `time_compiled`) protected by mutexes. For example, if the monitor detects a burnout, it locks `over_lock`, changes `is_over` to 1, and unlocks it. It then broadcasts a signal to all dongle condition variables. Sleeping coders wake up safely, check `is_over`, realize the simulation is done, and exit cleanly.
