/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

/*!
 * @header      error.c
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Error management functions
 */

/* Local includes */
#include "egpack.h"

/*!
 * @function    egpack_err_str
 * @abstract    Gets an error message about a specific error code
 * @param       status  The error code
 * @return      The error message corresponding to the error code
 */
char * egpack_err_str( egpack_status status )
{
    switch( status )
    {
        case EGPACK_OK:                     return "no error";
        case EGPACK_ERROR_STAT:             return "stat() error";
        case EGPACK_ERROR_INVALID_FILE:     return "invalid EGPK file type - only regular files, directories and symbolic links are supported in EGPK archives";
        case EGPACK_ERROR_OPENDIR:          return "unable to open directory";
        case EGPACK_ERROR_MALLOC:           return "malloc() error";
        case EGPACK_ERROR_FOPEN:            return "unable to open file";
        case EGPACK_ERROR_FILE_ID:          return "invalid file ID";
        case EGPACK_ERROR_MD5:              return "invalid MD5 checksum - archive seems corrupted";
        case EGPACK_ERROR_INVALID_ENTRY:    return "invalid EGPK entry in archive file - archive seems corrupted";
        case EGPACK_ERROR_MKDIR:            return "unable to create directory";
        case EGPACK_ERROR_CHMOD:            return "unable to apply file mode";
        case EGPACK_ERROR_READLINK:         return "readlink() error";
        case EGPACK_ERROR_SYMLINK :         return "symlink() error";
        default:                            return "unknown error";
    }
}
