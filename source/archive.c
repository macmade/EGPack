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
 * @header      archive.c
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Archiving functions
 */

/* Local includes */
#include "egpack.h"

/*!
 * @function    egpack_archive
 * @abstract    Archives source path into destination file
 * @param       source      The path to archive
 * @param       destination The archive file pointer
 * @result      The status code
 */
egpack_status egpack_archive( char * source, FILE * destination )
{
    struct stat              stat_buf;
    egpack_status            status;
    egpack_header            header;
    
    /* Gets informations about to file to archive */
    if( lstat( source, &stat_buf ) != 0 )
    {
        return EGPACK_ERROR_STAT;
    }
    
    /* Header initialization */
    memset( &header, 0, sizeof( egpack_header ) );
    memcpy( &( header.id ), EGPACK_FILE_ID, 4 );
    
    header.ctime = time( NULL );
    status       = EGPACK_OK;
    
    /* Writes the EGPK file header */
    fwrite( &header, sizeof( egpack_header ), 1, destination );
    
    /* Checks the path type */
    if( S_ISDIR( stat_buf.st_mode ) )
    {
        DEBUG( "Archiving directory" );
        
        /* Archives a directory */
        status = egpack_archive_dir( source, 0, destination );
    }
    else if( S_ISREG( stat_buf.st_mode ) )
    {
        DEBUG( "Archiving regular file" );
        
        /* Archives a single file */
        status = egpack_archive_file( source, 0, destination );
    }
    else if( S_ISLNK( stat_buf.st_mode ) )
    {
        DEBUG( "Archiving symbolic link" );
        
        /* Archives a single file */
        status = egpack_archive_file( source, 0, destination );
    }
    else
    {
        /* Error - File type unsupported */
        return EGPACK_ERROR_INVALID_FILE;
    }
    
    return status;
}

/*!
 * @function    egpack_archive_dir
 * @abstract    Archives a complete directory into destination file
 * @param       dirname     The name of the directory
 * @param       depth       The depth from the archive's root directory
 * @param       destination The archive file pointer
 * @result      The status code
 */
egpack_status egpack_archive_dir( char * dirname, unsigned int depth, FILE * destination )
{
    struct stat             stat_buf;
    DIR                   * dp;
    struct dirent         * ep;
    egpack_status           status;
    size_t                  path_length;
    char                  * filename;
    egpack_header_entry     entry;
    egpack_header_entry_dir dir;
    unsigned int            i;
    unsigned int            length;
    
    /* Path length for subfiles */
    path_length = strlen( dirname ) + EGPK_FILENAME_MAX + 2;
    
    /* Gets directory informations */
    if( stat( dirname, &stat_buf ) != 0 )
    {
        return EGPACK_ERROR_STAT;
    }
    
    /* Allocates memory for the subfiles paths */
    if( NULL == ( filename = calloc( sizeof( char ), path_length ) ) )
    {
        return EGPACK_ERROR_MALLOC;
    }
    
    DEBUG( "Opening directory pointer" );
    
    /* Opens a directory pointer */
    if( NULL == ( dp = opendir( dirname ) ) )
    {
        free( filename );
        return EGPACK_ERROR_OPENDIR;
    }
    
    /* Header initialization */
    memset( &entry, 0, sizeof( egpack_header_entry ) );
    memset( &dir,   0, sizeof( egpack_header_entry_dir ) );
    
    /* Length of the directory name */
    length = strlen( dirname );
    
    /* Gets only the basename */
    for( i = length; i > 0; i-- )
    {
        if( dirname[ i - 1 ] == EGPACK_DIR_SEPARATOR_CHAR )
        {
            break;
        }
    }
    
    /* Entry fields */
    entry.type  = EGPACK_ENTRY_TYPE_DIR;
    entry.depth = depth;
    
    /* Directory entry fields */
    dir.ctime = stat_buf.st_ctime;
    dir.mtime = stat_buf.st_mtime;
    dir.atime = stat_buf.st_atime;
    dir.mode  = stat_buf.st_mode;
    dir.uid   = stat_buf.st_uid;
    dir.gid   = stat_buf.st_gid;
    
    strcpy( ( char * )( dir.name ), dirname + i );
    strcat( ( char * )dir.name, EGPACK_DIR_SEPARATOR );
    
    /* Writes the entry and directory headers */
    fwrite( &entry, sizeof( egpack_header_entry ),     1, destination );
    fwrite( &dir,   sizeof( egpack_header_entry_dir ), 1, destination );
    
    status = EGPACK_OK;
    
    DEBUG
    (
        "Directory infos: %s\n"
        "    - Base name:         %s\n"
        "    - Depth:             %u\n"
        "    - Creation time:     %lu\n"
        "    - Modification time: %lu\n"
        "    - Access time:       %lu\n"
        "    - Mode:              0x%X\n"
        "    - UID:               %u\n"
        "    - GID:               %u",
        dirname,
        dir.name,
        depth,
        dir.ctime,
        dir.mtime,
        dir.atime,
        dir.mode,
        dir.uid,
        dir.gid
    );
    
    /* Reads the directory */
    while( ( ep = readdir( dp ) ) )
    {
        /* Full path to the subfile */
        memset( filename, 0, path_length );
        strcpy( filename, dirname );
        strcat( filename, EGPACK_DIR_SEPARATOR );
        strcat( filename, ep->d_name );
        
        /* Skip '.' and '..' */
        if( strcmp( ep->d_name, "." ) == 0 )
        {
            DEBUG( "Skipping '.'" );
            continue;
        }
        else if( strcmp( ep->d_name, ".." ) == 0 )
        {
            DEBUG( "Skipping '..'" );
            continue;
        }
        else
        {
            /* Gets informations about the subfile */
            if( lstat( filename, &stat_buf ) != 0 )
            {
                free( filename );
                closedir( dp );
                
                return EGPACK_ERROR_STAT;
            }
            
            /* Checks the subfile type */
            if( S_ISDIR( stat_buf.st_mode ) )
            {
                DEBUG( "Archiving directory: %s", filename );
                
                /* Archives a subdirectory */
                status = egpack_archive_dir( filename, depth + 1, destination );
                
                if( status != EGPACK_OK )
                {
                    free( filename );
                    closedir( dp );
                    
                    return status;
                }
            }
            else if( S_ISREG( stat_buf.st_mode ) )
            {
                DEBUG( "Archiving file: %s", filename );
                
                /* Archives a subfile */
                status = egpack_archive_file( filename, depth + 1, destination );
                
                if( status != EGPACK_OK )
                {
                    free( filename );
                    closedir( dp );
                    
                    return status;
                }
            }
            else if( S_ISLNK( stat_buf.st_mode ) )
            {
                DEBUG( "Archiving symbolic link: %s", filename );
                
                /* Archives a subfile */
                status = egpack_archive_link( filename, depth + 1, destination );
                
                if( status != EGPACK_OK )
                {
                    free( filename );
                    closedir( dp );
                    
                    return status;
                }
            }
            else
            {
                DEBUG( "Skipping invalid file: %s", filename );
                continue;
            }
        }
    }
    
    free( filename );
    DEBUG( "Closing directory pointer" );
    closedir( dp );
    
    return status;
}

/*!
 * @function    egpack_archive_dir
 * @abstract    Archives a single file into destination file
 * @param       dirname     The name of the file
 * @param       depth       The depth from the archive's root directory
 * @param       destination The archive file pointer
 * @result      The status code
 */
egpack_status egpack_archive_file( char * filename, unsigned int depth, FILE * destination )
{
    struct stat              stat_buf;
    egpack_header_entry      entry;
    egpack_header_entry_file file;
    unsigned int             i;
    unsigned int             length;
    double                   hsize;
    char                     unit[ 3 ] = { 0, 0, 0 };
    FILE                   * fp;
    uint8_t                  buffer[ EGPACK_BUFFER_LENGTH ];
    
    /* Gets informations about the file */
    if( stat( filename, &stat_buf ) != 0 )
    {
        return EGPACK_ERROR_STAT;
    }
    
    DEBUG( "Opening file handle" );
    
    /* Opens a file handle */
    if( NULL == ( fp = fopen( filename, "rb" ) ) )
    {
        return EGPACK_ERROR_FOPEN;
    }
    
    /* Header initialization */
    memset( &entry, 0, sizeof( egpack_header_entry ) );
    memset( &file,  0, sizeof( egpack_header_entry_file ) );
    
    /* Length of the file name */
    length = strlen( filename );
    
    /* Gets only the basename */
    for( i = length; i > 0; i-- )
    {
        if( filename[ i - 1 ] == EGPACK_DIR_SEPARATOR_CHAR )
        {
            break;
        }
    }
    
    strcpy( ( char * )( file.name ), filename + i );
    
    /* Entry fields */
    entry.type  = EGPACK_ENTRY_TYPE_FILE;
    entry.depth = depth;
    
    /* File fields */
    file.size   = stat_buf.st_size;
    file.ctime  = stat_buf.st_ctime;
    file.mtime  = stat_buf.st_mtime;
    file.atime  = stat_buf.st_atime;
    file.mode   = stat_buf.st_mode;
    file.uid    = stat_buf.st_uid;
    file.gid    = stat_buf.st_gid;
    
    /* Gets a MD% checksum of the file */
    egpack_file_md5_checksum( fp, ( char * )&( file.md5 ) );
    
    /* Debug only - Human readable size */
    if( file.size < 1000000 )
    {
        /* Kilo-bytes */
        hsize = ( double )file.size / ( double )1000;
        
        strcpy( unit, "KB" );
    }
    else if( file.size < 1000000000 )
    {
        /* Mega-bytes */
        hsize = ( ( double )file.size / ( double )1000 ) / ( double )1000;
        
        strcpy( unit, "MB" );
    }
    else
    {
        /* Giga-bytes */
        hsize = ( ( ( double )file.size / ( double )1000 ) / ( double )1000 ) / ( double )1000;
        
        strcpy( unit, "GB" );
    }
    
    DEBUG
    (
        "File infos: %s\n"
        "    - Base name:         %s\n"
        "    - Depth:             %u\n"
        "    - Size:              %.02f %s\n"
        "    - Creation time:     %lu\n"
        "    - Modification time: %lu\n"
        "    - Access time:       %lu\n"
        "    - Mode:              0x%X\n"
        "    - UID:               %u\n"
        "    - GID:               %u"
        "    - MD5:               %s",
        filename,
        file.name,
        depth,
        hsize,
        unit,
        file.ctime,
        file.mtime,
        file.atime,
        file.mode,
        file.uid,
        file.gid,
        file.md5
    );
    
    /* Writes the entry and file headers */
    fwrite( &entry, sizeof( egpack_header_entry ),      1, destination );
    fwrite( &file,  sizeof( egpack_header_entry_file ), 1, destination );
    
    DEBUG( "Writing file data" );
    
    /* Reads the file's data and writes it on the archive */
    while( ( length = fread( buffer, sizeof( uint8_t ), EGPACK_BUFFER_LENGTH, fp ) ) )
    {
        fwrite( buffer, sizeof( uint8_t ), length, destination );
    }
    
    DEBUG( "Closing file handle" );
    fclose( fp );
    
    return EGPACK_OK;
}

/*!
 * @function    egpack_archive_link
 * @abstract    Archives a symbolic link into destination file
 * @param       dirname     The name of the file
 * @param       depth       The depth from the archive's root directory
 * @param       destination The archive file pointer
 * @result      The status code
 */
egpack_status egpack_archive_link( char * filename, unsigned int depth, FILE * destination )
{
    struct stat                 stat_buf;
    egpack_header_entry         entry;
    egpack_header_entry_symlink symlnk;
    unsigned int                i;
    unsigned int                length;
    
    /* Gets informations about the file */
    if( lstat( filename, &stat_buf ) != 0 )
    {
        return EGPACK_ERROR_STAT;
    }
    
    /* Header initialization */
    memset( &entry, 0, sizeof( egpack_header_entry ) );
    memset( &symlnk,  0, sizeof( egpack_header_entry_symlink ) );
    
    /* Length of the file name */
    length = strlen( filename );
    
    /* Gets only the basename */
    for( i = length; i > 0; i-- )
    {
        if( filename[ i - 1 ] == EGPACK_DIR_SEPARATOR_CHAR )
        {
            break;
        }
    }
    
    strcpy( ( char * )( symlnk.name ), filename + i );
    readlink( filename, ( char * )symlnk.target, EGPK_SYMLINK_TARGET_MAX - 1 );
    
    /* Entry fields */
    entry.type  = EGPACK_ENTRY_TYPE_SYMLINK;
    entry.depth = depth;
    
    /* File fields */
    symlnk.ctime  = stat_buf.st_ctime;
    symlnk.mtime  = stat_buf.st_mtime;
    symlnk.atime  = stat_buf.st_atime;
    symlnk.mode   = stat_buf.st_mode;
    symlnk.uid    = stat_buf.st_uid;
    symlnk.gid    = stat_buf.st_gid;
    
    DEBUG
    (
        "Symbolic link infos: %s\n"
        "    - Base name:         %s\n"
        "    - Target:            %s\n"
        "    - Depth:             %u\n"
        "    - Creation time:     %lu\n"
        "    - Modification time: %lu\n"
        "    - Access time:       %lu\n"
        "    - Mode:              0x%X\n"
        "    - UID:               %u\n"
        "    - GID:               %u",
        filename,
        symlnk.name,
        symlnk.target,
        depth,
        symlnk.ctime,
        symlnk.mtime,
        symlnk.atime,
        symlnk.mode,
        symlnk.uid,
        symlnk.gid
    );
    
    /* Writes the entry and file headers */
    fwrite( &entry, sizeof( egpack_header_entry ),      1, destination );
    fwrite( &symlnk,  sizeof( egpack_header_entry_symlink ), 1, destination );
    
    return EGPACK_OK;
}
