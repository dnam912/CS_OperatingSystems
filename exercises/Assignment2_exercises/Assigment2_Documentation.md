# Instruction
Topic: Banker’s Algorithm for deadlock avoidance.

Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:

Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

Input file (you should create an input file, e.g., .txt, with your customized format that stores the data that is provided in the table).
Your code should print out the safe sequence if the system is safe.

### Keywords
1. Banker's Algorithm
2. Avoiding Deadlock
3. Safe / Unsafe State
4. Managing Resources
5. Allocation, Maximum, Available, Need


----
# Step 1: Creating Input File & a Table

### Input File


### The Table
![[Screenshot 2024-11-21 at 10.49.49 PM.png]]

### Calculates Need and Total Resources
- Need = (maximum - allocation)
- Total Resources of A, B, C = (allocation + available)
```
A(first_index), B(second_index), C(third_index)

A += allocation[row][first_index];
B += allocation[row][second_index];
C += allocation[row][third_index];
```


-----
# Step 2: Banker's Algorithm

P0 1 

2 3 4

Failed  0 
Executed 1



3 4

Failed  0 2
Executed 1