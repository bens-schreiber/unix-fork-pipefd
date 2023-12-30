#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>
#include "tests.h"

#define END_TEST(t) printf("\n" #t " passed \n------------------\n\n");

void test1(void)
{

    int x = 100;
    int rc = fork();

    assert(rc >= 0);

    // child proccess
    if (rc == 0)
    {
        assert(x == 100);
        x--;

        // x is 99 on the child process
        assert(x == 99);

        exit(0);
        return;
    }

    // main process
    assert(x == 100);
    x++;
    wait(NULL);

    // x is 101 on the main process
    assert(x == 101);

    END_TEST("test1");
}

void test2(void)
{

    int fd = open("./foo", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(fd >= 0);

    int rc = fork();

    // child proccess
    if (rc == 0)
    {
        write(fd, "child", 6);

        // reset file pointer to the beginning of the file
        lseek(fd, 0, SEEK_SET);

        // read file
        char buf[100];
        ssize_t bytesRead = read(fd, buf, sizeof(buf));
        assert(bytesRead >= 0);
        buf[bytesRead] = '\0';

        assert(strcmp(buf, "parentchild") == 0);

        exit(0);
        return;
    }

    // main process
    write(fd, "parent", 6);

    // reset file pointer to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // read file
    char buf[100];
    ssize_t bytesRead = read(fd, buf, sizeof(buf));
    assert(bytesRead >= 0);
    buf[bytesRead] = '\0';

    assert(strcmp(buf, "parent") == 0);

    wait(NULL);

    close(fd);

    END_TEST("test2");
}

void test3(void)
{
    int pipefd[2];
    assert(pipe(pipefd) == 0); // pipefd[0] is read end, pipefd[1] is write end
    int rc = fork();

    if (rc == 0)
    {
        // child process
        close(pipefd[0]);
        printf("hello\n");
        write(pipefd[1], "c", 1);
        close(pipefd[1]);
        exit(0);
        return;
    }

    // main process
    close(pipefd[1]);
    char c;
    read(pipefd[0], &c, 1); // block
    close(pipefd[0]);
    printf("goodbye\n");

    wait(NULL);

    END_TEST("test3");
}

void test4(void) {
    int rc = fork();

    if (rc == 0) {
        // child process

        char *args[] = {"/bin/ls", "-l", NULL};
        execv(args[0], args);

        // char *args[] = {"ls", "-l", NULL};
        // execvp(args[0], args);
        
        exit(0);
        return;
    }

    // main process
    wait(NULL);

    END_TEST("test4");
}