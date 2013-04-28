/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina - www.xs-labs.com
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
 * @header      md5.h
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    MD5 functions
 */

/* System includes */
#if defined( __APPLE__ )
    
    #include <CommonCrypto/CommonDigest.h>
    
    #ifdef MD5_DIGEST_LENGTH
        
        #undef MD5_DIGEST_LENGTH
        
    #endif
    
    #define MD5_Init            CC_MD5_Init
    #define MD5_Update          CC_MD5_Update
    #define MD5_Final           CC_MD5_Final
    #define MD5_DIGEST_LENGTH   CC_MD5_DIGEST_LENGTH
    #define MD5_CTX             CC_MD5_CTX
    
#else
    
    #include <openssl/md5.h>

#endif

#ifndef _EGPACK_MD5_H_
#define _EGPACK_MD5_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    /*!
     * @function    egpack_file_md5_checksum
     * @abstract    Gets a MD5 checksum of a file pointer
     * @param       fp      The file pointer
     * @param       hash    Character buffer (2x MD5_DIGEST_LENGTH)
     * @result      void
     */
    void egpack_file_md5_checksum( FILE * fp, char * hash );

#ifdef __cplusplus
}
#endif

#endif /* _EGPACK_MD5_H_ */
