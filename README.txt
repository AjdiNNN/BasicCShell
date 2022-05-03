Members:
    -Ajdin Hukić
    -Bilal Duraković
Github:
    -https://github.com/AjdiNNN/BasicCShell
List of files in project:
    -.git
    -README.md
    -README.txt
    -'Task 1.5.docx'
    -cat
    -cat.c
    -clear
    -clear.c
    -cowsay
    -cowsay.c
    -exit
    -exit.c
    -forkbomb
    -forkbomb.c
    -help
    -help.c
    -rm
    -rm.c
    -shell
    -shell.c
Task 1.5: Provide a concise and descriptive answer to the following questions.
    /*-------------------------------------------------------------------------------------------------------------*\
    Q1: What does the mmap() function do?
        -The linux manual will help with the basic definition of this function: 
        mmap, munmap - map or unmap files or devices into memory
        -The mmap() function creates a mapping in the virtual adress space of the process in which it is called.
        -The function takes the following parametres:
            void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
        -First of all, we see that this function is of type void – it doesn't return any parameter.
        -The addr argument specifies the starting adress where the new mapping will be created. 
        -The length parameter contains the length of the new mapping – hence it must be greater than zero.
        -The prot argument can be used for selecting the desired memory protection of the mapping
        -It can have one or more of the following values / flags:
            PROT_EXEC: Pages may be executed.
            PROT_READ: Pages may be read.
            PROT_WRITE: Pages may be written.
            PROT_NONE: Pages may not be accessed.
        -The flags argument determines whether updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through 
            to the underlying file.
        It can have one or more of the following values / flags:
            MAP_SHARED, MAP_SHARED_VALIDATE,MAP_PRIVATE, MAP_32BIT, MAP_ANON/ MAP_ANONYMOUS
    /*-------------------------------------------------------------------------------------------------------------*\
    Q2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.
        -A context switch is a process that involves switching of the CPU from one process or task to another. In this phenomenon, the execution of the process that 
            is present in the running state is suspended by the kernel and another process that is present in the ready state is executed by the CPU.
        -Context is the contents of a CPU's registers and program counter(PC) at any point in time. Context switching can happen due to the following reasons:
        ⦁	When a process of high priority comes in the ready state. In this case, the execution of the running process should be stopped and the higher priority process 
            should be given the CPU for execution.
        ⦁	When an interrupt occurs - the process in the running state should be stopped and the CPU should handle the interrupt before doing something else.
        ⦁	When a transition between the user mode and kernel mode is required then context switching is required.
What we did in an assigment:
    -Firstly we made c program to handle and ask user for input continusly, then we made program prints machinename@username:~$ before input.
    -Next step was to parse commands, after that we made 5 helper programs to run our commands with excev rm, cat, clear, cowsay then we made helper program help to display
        help in shell. After cat got 2 arguments support for -n to print line numbers and -s to print start and end of every file. Then cowsay got arguments for -h help,
        -t thoughts to print bubble thoughts line "differently", and argument -e to change char for eyes ex. cowsay -e A Text message.
    -The most challenging was implemenation of pipe, as we spent the most time trying to make it work, at end we got it working now it is possible to do 2 pipes ex. cat filename | /bin/more
    -In pipe calls fork(),wait(),execv() were used, for non piped command execv() was used too.
    -After that forkbomb command was made, and it was tested by using all 16GB of my machine i had to do restart, so it WORKS :D
    -At end purple color was added to machinename@username:~$ and red color to some error messages, like forking erros or command exectuing error.
    -And before that we answered on questions mentioned above.
How to compile program/s:
    sudo apt-get install libreadline-dev 
    gcc shell.c -o shell -lreadline
    gcc cowsay.c -o cowsay
    gcc cat.c -o cat
    gcc exit.c -o exit
    gcc rm.c -o rm
    gcc help.c -o help
    gcc forkbomb.c -o forkbomb
    gcc clear.c -o clear
    ./shell
Sources used for this project:
    stackoverflow my thread - did not get answer needed, figure out myself.
    stackoverflow other threads, got logic for piping from it
    cowsay wikipedia
    geeksforgeeks shell examples, piping examples, execv examples
    linux github repository
    and many more i can't remember took so long to get everything working :D
Everything works as it should except adding name to shell I did not get where to add name.