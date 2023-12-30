/*
Write a program that calls fork(). 
Before calling fork(), have the main  process access a variable (e.g., x) and set its value to something (e.g., 100).  
What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x? 

Arpaci-Dusseau, Remzi; Arpaci-Dusseau, Andrea. Operating Systems: Three Easy Pieces (p. 48). Arpaci-Dusseau Books. Kindle Edition.

SOLUTION: The threads have different memory. The child will get the original number (100), but updating it will not change the parents number.

*/
extern void test1(void);

/*
Write a program that opens a file (with the open() system call) and then  calls fork() to create a new process. 
Can both the child and parent access the file descriptor returned by open()? 
What happens when they are  writing to the file concurrently, i.e., at the same time? 

Arpaci-Dusseau, Remzi; Arpaci-Dusseau, Andrea. Operating Systems: Three Easy Pieces (p. 48). Arpaci-Dusseau Books. Kindle Edition. 

SOLUTION: Both of the threads can access the file descriptor. If we write to the file concurrently, without waiting for the other thread to finish,
the end of the main thread will think that only "parent" has been written, and the end of the child thread will think that only "child" has been written.
*/
extern void test2(void);

/*
Write another program using fork(). 
The child process should print “hello”;  the parent process should print “goodbye”. 
You should try to ensure that  the child process always prints first; 
can you do this without calling wait() in  the parent? 

Arpaci-Dusseau, Remzi; Arpaci-Dusseau, Andrea. Operating Systems: Three Easy Pieces (p. 48). Arpaci-Dusseau Books. Kindle Edition. 

SOLUTION: One solution without using wait() is to use sleep() in the parent thread.
Another solution is a little more complicated. We can use a pipe to send a message from the child to the parent.
*/
extern void test3(void);

/*
Write a program that calls fork() and then calls some form of exec() to  run the program /bin/ls. 
See if you can try all of the variants of exec(),  
including (on Linux) execl(), execle(), execlp(), execv(), execvp(),  and execvpe().

Arpaci-Dusseau, Remzi; Arpaci-Dusseau, Andrea. Operating Systems: Three Easy Pieces (p. 48). Arpaci-Dusseau Books. Kindle Edition. 
*/
extern void test4(void);