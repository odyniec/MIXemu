MIXemu
======

MIXemu is a simulator of the MIX computer invented by Donald Knuth and
described in his famous book "The Art of Computer Programming".

Two programs are included in the package: *mixemu*, a basic command line
interface for the MIX simulator, and *mixasm* - a MIXAL assembler.

Installation
------------

Installation instructions for the impatient:

    ./configure
    make
    make install

For more detailed installation instructions see the INSTALL file.

Basic usage instructions
------------------------

The MIXemu package includes an example MIX program (`examples/primes.mixal`)
that prints out the first five hundred prime numbers (the first MIX program
described by Donald Knuth in TAoCP Volume 1). To assemble it, use the `mixasm`
program:

    mixasm primes.mixal

This produces the MIX program file `primes.mp`.

Start the simulator:

    mixemu

You will see a ">" prompt. Initialize the printer device (with a device number
of 18) to output data to a file named `out`:

    set dev 18 out

Load the program:

    load primes.mp

The simulator will display the start address of the program. Start it using the
`run` command:

    run

You should see a message telling you that the program finished successfully. At
this point, a new file named `out` should be created in the current directory,
containing the output of the printer device -- the first five hundred primes.

Quit the simulator:

    quit

