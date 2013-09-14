/*----------------------------------------------------------------------------
| Copyright (C) 2013 Kévin Seroux                                              |
|                                                                              |
| This software is provided 'as-is', without any express or implied warranty.  |
| In no event will the authors be held liable for any damages arising from the |
| use of this software.                                                        |
|                                                                              |
| Permission is granted to anyone to use this software for any purpose         |
| including commercial applications, and to alter it and redistribute it       |
| freely, subject to the following restrictions:                               |
|                                                                              |
| 1. The origin of this software must not be misrepresented; you must not      |
| claim that you wrote the original software. If you use this software in a    |
| product, an acknowledgment in the product documentation would be appreciated |
| but is not required.                                                         |
|                                                                              |
| 2. Altered source versions must be plainly marked as such, and must not be   |
| be misrepresented as being the original software.                            |
|                                                                              |
| 3. This notice may not be removed or altered from any source distribution.   |
\_____________________________________________________________________________*/

#ifndef LTF__H
#define LTF__H

#include <stdint.h>

#ifdef WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

#define LTFLIB_SUCCESS 0
#define LTFLIB_ERROR_FILE_NOT_FOUND 1
#define LTFLIB_ERROR_OPEN_FAILED 2
#define LTFLIB_ERROR_FILE_CORRUPTED 3

struct LTF
{
	uint16_t width;
	uint16_t height;
	uint8_t depth;
	uint8_t* datas;
};
typedef struct LTF LTF;

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
/// \brief Export to the LTF format
///
/// \param[in] pLTF The structure which will be written
/// \param[in] pUrl The URL of the file to be written
///
/// \return LTFLIB_SUCCESS if success
/// \return LTFLIB_ERROR_OPEN_FAILED if the file could not be opened in write
///         mode
////////////////////////////////////////////////////////////////////////////////
IMPORT uint8_t const ExportToLTF(LTF const * const pLTF,
								 char const * const pUrl);

////////////////////////////////////////////////////////////////////////////////
/// \brief Load a LTF file
///
/// \param[in,out] pLTF The LTF structure which must be filled. But you must set
///                the depth value in the structure before to call this function
/// \param[in] pUrl The URL of the file to be read
///
/// \return LTFLIB_SUCCESS if success
/// \return LTFLIB_ERROR_FILE_NOT_FOUND if the file does not exist
/// \return LTFLIB_ERROR_OPEN_FAILED if the file could not be opened for unknown
///                                  reasons
/// \return LTFLIB_ERROR_FILE_CORRUPTED if the file is corrupted or a bad depth
///                                     has setted in the LTF structure.
///
/// \attention If the function return 0, you must free the memory allocated for
///            the member datas of the LTF structure with a call to FreeLTF()
////////////////////////////////////////////////////////////////////////////////
IMPORT uint8_t const LoadLTF(LTF * const pLTF, char const * const pUrl);

////////////////////////////////////////////////////////////////////////////////
/// \brief Free the memory allocated by LoadLTF()
///
///  \param[in] datas The datas member and not a pointer to his LTF structure
////////////////////////////////////////////////////////////////////////////////
IMPORT void FreeLTF(void * datas);

#ifdef __cplusplus
}
#endif

#undef IMPORT

#endif //LTF__H