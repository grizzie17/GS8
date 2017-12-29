/// \file
/// \brief Font data structures
/// \author Bob Dyas
///
/// Copyright 2003, Digital Design Corporation, All Rights Reserved.
///
/// Font bitmap data is generated from X server fonts using the
/// capturexfont utility. The data structures generated correspond to 
/// those described here.
/// - Adapted from glutbitmap.h Copyright (c) Mark J. Kilgard, 1994.
/// - removed gl, glut and floating point data types

#ifndef FONTS_H
#define FONTS_H

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Character data
///
/// This structure provides information needed by the text and bitmap
/// routines to draw the bitmapped characters
typedef struct {
  const int width;		///< character bitmap width
  const int height;		///< character bitmap height
  const int xorig;		///< x displacement for start of bitmap
  const int yorig;		///< y displacement for start of bitmap
  const int advance;		///< x displacement for start of next bitmap
  const unsigned char *bitmap;	///< pointer to the bitmap data
} BitmapCharRec, *BitmapCharPtr;

/// \brief Font information structure
///
/// The structure which provides information on the font.
typedef struct {
  const char *name;		///< the X font name
  const int num_chars;		///< number of characters in the font
  const int first;		///< first allowable character of the font
  const BitmapCharRec * const *ch; ///< pointer to the character data
} BitmapFontRec, *BitmapFontPtr;

typedef void *BitmapFont;

#ifdef __cplusplus
}
#endif

#endif	/* FONTS_H */
