// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright (C) 1998-2000 by DooM Legacy Team.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//-----------------------------------------------------------------------------
/// \file
/// \brief defines structures and exports for the standard 3D driver DLL used by Doom Legacy

#ifndef _HWR_DATA_
#define _HWR_DATA_

#if defined (_WIN32) && !defined (__CYGWIN__)
//#define WIN32_LEAN_AND_MEAN
#define RPC_NO_WINDOWS_H
#include <windows.h>
#endif

#include "../doomdef.h"
#include "../screen.h"

// ==========================================================================
//                                                               TEXTURE INFO
// ==========================================================================

//
// Texture formats
//

typedef enum
{
	GR_TEXFMT_P_8                = 0x01, // 8-bit palette
	GR_TEXFMT_AP_88              = 0x02, // 8-bit palette + 8-bit alpha

	GR_TEXFMT_ALPHA_8            = 0x03, // 8-bit alpha (fade masks)
	GR_TEXFMT_ALPHA_INTENSITY_88 = 0x04, // 8-bit alpha + 8-bit intensity (coronas and dynamic lights)

	GR_RGBA                      = 0x05, // 32 bit RGBA
} HWRTextureFormat;

// .data holds the address of the graphics data cached in heap memory
//                NULL if the texture is not in Doom heap cache.
struct GLMipmap_s
{
	// Basic texture info
	UINT16             width, height;
	UINT32             flags;         // Texture flags (TF_)
	HWRTextureFormat   format;        // GR_ enumeration
	void               *data;

	// Colormaps
	struct GLMipmap_s  *nextcolormap; // List of mipmaps with colormaps
	const  UINT8       *colormap;     // Colormap of this mipmap

	// APIs may handle this differently.
	UINT32             downloaded;    // Uploaded to the GPU

	// Mipmap after this one
	struct GLMipmap_s  *nextmipmap;
};
typedef struct GLMipmap_s GLMipmap_t;


//
// Doom texture info, as cached for hardware rendering
//
struct GLTexture_s
{
	GLMipmap_t  mipmap;
	float       scaleX;             //used for scaling textures on walls
	float       scaleY;
};
typedef struct GLTexture_s GLTexture_t;


// a cached patch as converted to hardware format, holding the original patch_t
// header so that the existing code can retrieve ->width, ->height as usual
// This is returned by W_CachePatchNum()/W_CachePatchName(), when rendermode
// is 'render_opengl'. Else it returns the normal patch_t data.

struct GLPatch_s
{
	// the 4 first fields come right away from the original patch_t
	INT16               width;
	INT16               height;
	INT16               leftoffset;     // pixels to the left of origin
	INT16               topoffset;      // pixels below the origin
	//
	float               max_s,max_t;
	UINT16              wadnum;      // the software patch lump num for when the hardware patch
	UINT16              lumpnum;     // was flushed, and we need to re-create it
	void                *rawpatch;   // :^)
	GLMipmap_t          *mipmap;
} ATTRPACK;
typedef struct GLPatch_s GLPatch_t;

#endif //_HWR_DATA_
