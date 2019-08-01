# CPP Select
## Simple example of `select` syscall

I'm developing on MacOS so for other OS's commands might be different

## Create 2 pipes
`mkfifo f1.fifo; mkfifo f2.fifo`

## Compile and run
`g++ main.c && ./a.out`

## Write data to pipes
`echo Hello > f1.fifo`
`echo Hello > f2.fifo`
`cat ex > f1.fifo`

Using `select` the process is not blocking on one of pipes but on select that is responsible to notify the process when there will be data to read
