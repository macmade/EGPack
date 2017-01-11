EGPack
======

[![Build Status](https://img.shields.io/travis/macmade/EGPack.svg?branch=master&style=flat)](https://travis-ci.org/macmade/EGPack)
[![Issues](http://img.shields.io/github/issues/macmade/EGPack.svg?style=flat)](https://github.com/macmade/EGPack/issues)
![Status](https://img.shields.io/badge/status-inactive-lightgray.svg?style=flat)
![License](https://img.shields.io/badge/license-boost-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)  
[![Donate-Patreon](https://img.shields.io/badge/donate-patreon-yellow.svg?style=flat)](https://patreon.com/macmade)
[![Donate-Gratipay](https://img.shields.io/badge/donate-gratipay-yellow.svg?style=flat)](https://www.gratipay.com/macmade)
[![Donate-Paypal](https://img.shields.io/badge/donate-paypal-yellow.svg?style=flat)](https://paypal.me/xslabs)

About
-----

EGPack is an archive utility, similar to the TAR utility.  

Documentation
-------------

### Compiling and installing

EGPack should compile on every POSIX compliant operating system with an ANSI-C
compiler.

To compile EGPack, simply type `make` from a console prompt, from the EGPack
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

File format specification
-------------------------

### About

EGPack uses its own specific file format, which is not compatible with other
archive formats, such as the TAR format.

### Format

The EGPack format consists of several specific header blocks, followed by the
file(s) content.

An EPKG file must start with the main header, which is 72 bytes long.

The first four bytes represent the file format signature, which consists of
the ASCII `EGPK` characters (0x45 0x47 0x50 0x4B).  
The next four bytes are used to store the archive creation time.

Other bytes are reserved for format extension, and should be all zeros.

In C, the EGPK header is represented the following way:

    struct egpack_header
    {
        uint8_t  id[ 4 ];
        uint32_t ctime;
        uint8_t  pad[ 64 ];
    };

Each file or directory entry is preceded by an entry header, which is 72 bytes
long.

The first byte is used for the entry type. It's value can be:

*   0:  Regular file
*   1:  Directory
*   2:  Symbolic link

The second four bytes are used to store the depth of the file, from the
archive's root directory.                                                       
In order to avoid limitations on the path length, all filenames are stored
without the path (only the basename with extension).                            
So the depth value is used to indicate the file or directory depth, relative
to the previous entry.

Other bytes are reserved for format extension, and should be all zeros.

In C, an entry header is represented the following way:

    struct egpack_header_entry
    {
        uint8_t  type;
        uint32_t depth;
        uint8_t  pad[ 64 ];
    };

Depending on the entry type, the following bytes are used to represents a file,
directory, or symbolic link informations.

An file entry header is 641 bytes long

The first 512 bytes are used for the filename, which is a NULL terminated
string.

The next four bytes are used to store the file size, in bytes.

Following 12 bytes represents respectively the file's creation time, the last
modification time, and the last access time.                                    
Each value is 4 bytes long.

The next fours bytes are used for the file's permissions.

The next eight bytes represents respectively the owner ID and the group ID.     
Each value is 4 bytes long.

Following 33 bytes are the MD5 checksum of the file.                            
The value is a NULL terminated string.

Other bytes are reserved for format extension, and should be all zeros.

In C, a file entry header is represented the following way:

    struct egpack_header_entry_file
    {
        uint8_t   name[ 512 ];
        uint64_t  size;
        uint32_t  ctime;
        uint32_t  mtime;
        uint32_t  atime;
        uint32_t  mode;
        uint32_t  uid;
        uint32_t  gid;
        uint8_t   md5[ 33 ];
        uint8_t   pad[ 64 ];
    };

A directory entry header contains the same fields, except the `size` and `md5`
fields.

A directory header is 600 bytes long.

In C, a file entry header is represented the following way:

    struct egpack_header_entry_dir
    {
        uint8_t   name[ 512 ];
        uint32_t  ctime;
        uint32_t  mtime;
        uint32_t  atime;
        uint32_t  mode;
        uint32_t  uid;
        uint32_t  gid;
        uint8_t   pad[ 64 ];
    };

A symbolic link header is the same as a file entry header, with the addition of
a `target` field, representing the symbolic link target file, and without the
`md5` field.

A directory header is 1632 bytes long.

In C, a file entry header is represented the following way:

    struct egpack_header_entry_symlink
    {
        uint8_t   name[ 512 ];
        uint8_t   target[ 1024 ];
        uint32_t  ctime;
        uint32_t  mtime;
        uint32_t  atime;
        uint32_t  mode;
        uint32_t  uid;
        uint32_t  gid;
        uint8_t   pad[ 64 ];
    };

For files, the entry is followed by the file's data.

For directories, the directory header is immediately followed by other entries
headers.

License
-------

EGPack is released under the terms of the Boost Software License - Version 1.0.

Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade