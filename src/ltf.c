/*------------------------------------------------------------------------------
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

#include "ltf.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define EXPORT __declspec(dllexport)

EXPORT uint8_t const ExportToLTF(LTF const * const pLTF,
                                 char const * const pUrl)
{
	uint32_t countBytes, i;

	FILE* file = fopen(pUrl, "wb");
	if(file == NULL)
	{
		return LTFLIB_ERROR_OPEN_FAILED;
	}

	countBytes = pLTF->width * pLTF->height * pLTF->depth;

	fwrite(&pLTF->width, sizeof(uint16_t), 1, file);
	fwrite(&pLTF->height, sizeof(uint16_t), 1, file);
	for(i = 0; i < countBytes; i += pLTF->depth)
	{
		fwrite(pLTF->datas + i, 1, pLTF->depth, file);
	}

	fclose(file);

	return LTFLIB_SUCCESS;
}

EXPORT uint8_t const LoadLTF(LTF * const pLTF, char const * const pUrl)
{
	// We place the variable below otherwise MSVC fail to compile.
	// http://andre.stechert.org/urwhatu/2006/01/error_c2143_syn.html
	//
	uint32_t definition, i;
	size_t j;

	FILE* file = fopen(pUrl, "rb");
	if(file == NULL)
	{
		if(errno == ENOENT)
			return LTFLIB_ERROR_FILE_NOT_FOUND;

		return LTFLIB_ERROR_OPEN_FAILED;
	}

	fread(&pLTF->width, 2, 1, file);
	fread(&pLTF->height, 2, 1, file);

	definition = pLTF->width * pLTF->height;
	pLTF->datas = malloc(definition * pLTF->depth);

	j = fread(pLTF->datas, pLTF->depth, definition, file);
	if(j != definition)
	{
		free(pLTF->datas);
		return LTFLIB_ERROR_FILE_CORRUPTED;
	}

	fclose(file);

	return LTFLIB_SUCCESS;
}

EXPORT void FreeLTF(void * datas)
{
	free(datas);
}