/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina <macmade@eosgarden.com>
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
 * @header      types.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Program's type definitions
 */

#ifndef _EGPACK_TYPES_H_
#define _EGPACK_TYPES_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    
    #include <stdc/bool.h>
    #include <stdint.h>
    #include <openssl/md5.h>
    
    /*!
     * 
     */
    typedef struct _egpack_cli_args
    {
        bool   archive;
        bool   unarchive;
        bool   version;
        bool   help;
        bool   debug;
        char * source;
    }
    egpack_cli_args;
    
    /*!
     * 
     */
    typedef struct _egpack_header
    {
        uint8_t  id[ 4 ];
        uint32_t ctime;
        uint8_t  pad[ 64 ];
    }
    egpack_header;
    
    /*!
     * 
     */
    typedef struct _egpack_header_entry
    {
        uint8_t  type;
        uint32_t depth;
        uint8_t  pad[ 64 ];
    }
    egpack_header_entry;
    
    /*!
     * 
     */
    typedef struct _egpack_header_entry_file
    {
        uint8_t   name[ FILENAME_MAX ];
        uint32_t  size;
        uint32_t  ctime;
        uint32_t  mtime;
        uint32_t  atime;
        uint32_t  mode;
        uint32_t  uid;
        uint32_t  gid;
        uint8_t   pad[ 64 ];
        uint8_t   md5[ MD5_DIGEST_LENGTH * 2 ];
    }
    egpack_header_entry_file;
    
    /*!
     * 
     */
    typedef struct _egpack_header_entry_dir
    {
        uint8_t  name[ FILENAME_MAX ];
    }
    egpack_header_entry_dir;
    
    /*!
     * 
     */
    typedef enum
    {
        EGPACK_OK                   = 0x00,
        EGPACK_ERROR_STAT           = 0x01,
        EGPACK_ERROR_INVALID_FILE   = 0x02,
        EGPACK_ERROR_OPENDIR        = 0x03,
        EGPACK_ERROR_MALLOC         = 0x04,
        EGPACK_ERROR_FOPEN          = 0x05,
        EGPACK_ERROR_FILE_ID        = 0x06,
        EGPACK_ERROR_MD5            = 0x07
    }
    egpack_status;
    
#ifdef __cplusplus
}
#endif

#endif /* _EGPACK_TYPES_H_ */

