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
 * @header      constants.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Program's constants
 */

#ifndef _EGPACK_CONSTANTS_H_
#define _EGPACK_CONSTANTS_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @define      EGPACK_VERSION
 * @abstract    Program's version number
 */
#define EGPACK_VERSION                  "1.0.0"

/*!
 * @define      EGPACK_FILE_ID
 * @abstract    EGPK file signature
 */
#define EGPACK_FILE_ID                  "EGPK"

/*!
 * @define      EGPACK_FILE_EXT
 * @abstract    EGPK file extension
 */
#define EGPACK_FILE_EXT                 ".egpk"

/*!
 * @define      EGPACK_DIR_SEPARATOR
 * @abstract    Directory separator
 */
#define EGPACK_DIR_SEPARATOR            "/"

/*!
 * @define      EGPACK_DIR_SEPARATOR_CHAR
 * @abstract    Directory separator (char version)
 */
#define EGPACK_DIR_SEPARATOR_CHAR       '/'

/*!
 * @define      EGPACK_BUFFER_LENGTH
 * @abstract    Buffer length for the I/O operations
 */
#define EGPACK_BUFFER_LENGTH            4096

/*!
 * @define      EGPK_FILENAME_MAX
 * @abstract    The maximum number of characters to hold a filename, including
 *              the trailing 0.
 */
#define EGPK_FILENAME_MAX               512

#ifdef __cplusplus
}
#endif

#endif /* _EGPACK_CONSTANTS_H_ */

