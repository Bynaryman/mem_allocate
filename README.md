# mem_allocate

## Compilation

Compile with -O2 to achieve reasonable time for aligned mem

```
g++ -O2 -std=c++14 -o mem_allocate mem_allocate.cpp
```
## Execution

start program with 2 args, they have to be numbers, the program will allocate 2 ** (first_arg) bytes of 4K blocks aligned mem, and 2 ** (second_arg) bytes of non aligned mem.
The program also mesures times of allocations

Example :
```
./mem_allocate 30 30
```

Allocation of 1GB of aligned and non aligned mem

Output example:
```
TIME aligned mem allocation : 0.76654s
TIME non aligned mem allocation : 0.0807133s
```
