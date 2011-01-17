EGPack
======

Read me
-------

$Id$

### About

EGPack is an archive utility, similar to the TAR utility.                       
A specific file format is used. Please see `FORMAT.txt` for further
informations about the EGPK file format.

### Compiling and installing

Egpack should compile on every POSIX compliant operating system with an ANSI-C
compiler.

To compile EGPack, simply type `make` from a console prompte, from the EGPack
root directory.

Installation of the `egpack` utility is done through the `make install`
command.

### Usage

In order to archive a file or a directory, invoke the `egpack` binary with the
`-a` argument, followed by the name of the file or directory to archive:

    egpack -a path/to/directory/

Un-archiving is done with the `-u`option:

    egpack -u path/to/archive.egpk

Here are the available command line arguments that can be passed to the `egpack`
binary:

*   -a                                                                          
    Archives a file or a directory.
*   -u                                                                          
    Un-archives an EGPK archive file.
*   -v                                                                          
    Prints the EGPK version number.
*   -h                                                                          
    Prints the EGPK help dialog
*   -d                                                                          
    Turns on debugging mode

### Support

EGPack documentation can be found on the eosgarden website:                     
http://www.eosgarden.com/

### License

EGPack is a free software, distributed under the terms of the Boos license.     
Please see `LICENSE.txt` for the full license terms.
