# Beej IPC
some quick test harnesses to get some concepts working based on the Beej IPC guide.

## Notes
- the posix mq demo doesn't compile on macos
    - figure out where the posix mq headers are?
    
- to compile the posix demo:
    - gcc main.c -lrt