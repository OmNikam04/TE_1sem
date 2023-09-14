## Fork()
`fork()`: The fork() system call is used to create a separate, duplicate process.
- Separate duplicate system process is created using fork only difference is that newly created child process of **different `process id`**

## Exec()

`exec()`: When on `exec()` system call is invoked, the program specified in the parameter to exec() will _replace the entire process_ -- including all threads.
- In other words, `exec()` is used to replace a process with another process, then they will have the **same process id**.
- Exec call replaces the address space, text segment, data segment, etc. of the current process.

## Fork:

```
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	fork();
	fork();
	fork();
	printf("This is process with fork %d\t\n", getpid());
	return 0;
}
```
`` Total 8 prcess created by above program here is breakdown of it. ``

- First fork() call: It creates one child process, so there are now two processes (the parent and the child). 
- Second fork() call: Both the parent and the child process created in the first call execute the second fork() call. This creates two more child processes, making the total number of processes four (one parent and three child processes).  
- Third fork() call: Now, all four processes execute the third fork() call, creating four more child processes, making the total number of processes seven (one parent and six child processes).

`` With n fork statements, there are always 2^n – 1 child processes and 2^n total process``
