//
// Copyright(C) 2014-2015 Samuel Villarreal
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

#ifndef __KEXLIB_H__
#define __KEXLIB_H__

#define KEX_ENGINE_TITLE        "Kex Engine"
#define KEX_ENGINE_BRANCH       "Anubis"
#define KEX_ENGINE_VERSION      3
#define KEX_ENGINE_SUBVERSION   0

#define KEX_GAME_TITLE          "Powerslave/Exhumed EX-Plus"
#define KEX_GAME_VERSION        1
#define KEX_GAME_SUBVERSION     0

// narrow down the windows preprocessor bullshit down to just one macro define
#if defined(__WIN32__) || defined(__WIN32) || defined(_WIN32_) || defined(_WIN32) || defined(WIN32)
#define KEX_WIN32
#else
#if defined(__APPLE__)
// lets us know what version of Mac OS X we're compiling on
#include "AvailabilityMacros.h"
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
// if compiling for iPhone
#define KEX_IPHONE
#else
// if not compiling for iPhone
#define KEX_MACOSX
#if MAC_OS_X_VERSION_MIN_REQUIRED < 1050
# error KexLIB for Mac OS X only supports deploying on 10.5 and above.
#endif // MAC_OS_X_VERSION_MIN_REQUIRED < 1050
#if MAC_OS_X_VERSION_MAX_ALLOWED < 1060
# error KexLIB for Mac OS X must be built with a 10.6 SDK or above.
#endif // MAC_OS_X_VERSION_MAX_ALLOWED < 1060
#endif // TARGET_OS_IPHONE
#endif // defined(__APPLE__)
#endif // WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#ifdef _MSC_VER
#include "win32/opndir.h"
#else
#include <dirent.h>
#endif
#include <time.h>
#ifndef KEX_WIN32
#include <unistd.h>
#endif
#include <new>

#define MAX_FILEPATH    512
#define MAX_HASH        2048

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned long   ulong;
typedef unsigned int    uint;
typedef unsigned int    dtexture;
typedef unsigned int    rcolor;
typedef char            filepath_t[MAX_FILEPATH];

typedef union
{
    int     i;
    float   f;
} fint_t;

#define ASCII_SLASH		47
#define ASCII_BACKSLASH 92

#ifdef KEX_WIN32
#define DIR_SEPARATOR '\\'
#define PATH_SEPARATOR ';'
#else
#define DIR_SEPARATOR '/'
#define PATH_SEPARATOR ':'
#endif

#include <limits.h>
#define D_MININT INT_MIN
#define D_MAXINT INT_MAX

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef BETWEEN
#define BETWEEN(l,u,x) ((l)>(x)?(l):(x)>(u)?(u):(x))
#endif

#ifndef BIT
#define BIT(num) (1<<(num))
#endif

#define ARRLEN(array) (sizeof(array) / sizeof(*array))
#define OFFSETOF(type, member) ((size_t) &(((type*)0)->member))

#if defined(KEX_WIN32) && !defined(__GNUC__)
#define KDECL __cdecl
#else
#define KDECL
#endif

#ifdef ALIGNED
#undef ALIGNED
#endif

#if defined(_MSC_VER)
#define ALIGNED(x) __declspec(align(x))
#define PACKED
#elif defined(__GNUC__)
#define ALIGNED(x) __attribute__ ((aligned(x)))
#define PACKED __attribute__((packed))
#else
#define ALIGNED(x)
#define PACKED
#endif

// function inlining is available on most platforms, however,
// the GNU C __inline__ is too common and conflicts with a 
// definition in other dependencies, so it needs to be factored
// out into a custom macro definition

#if defined(__GNUC__)
#define d_inline __inline__
#elif defined(_MSC_VER) || defined(KEX_WIN32)
#define d_inline __forceinline
#else
#define d_inline
#endif

#define KEXLIB_NAMESPACE_START(x)  namespace x {
#define KEXLIB_NAMESPACE_END    }

#define RGBA(r,g,b,a) ((rcolor)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((g)&0xff)<<8)|((r)&0xff)))

#define COLOR_WHITE         RGBA(0xFF, 0xFF, 0xFF, 0xFF)
#define COLOR_WHITE_A(a)    RGBA(0xFF, 0xFF, 0xFF, a)
#define COLOR_RED           RGBA(0xFF, 0, 0, 0xFF)
#define COLOR_GREEN         RGBA(0, 0xFF, 0, 0xFF)
#define COLOR_YELLOW        RGBA(0xFF, 0xFF, 0, 0xFF)
#define COLOR_CYAN          RGBA(0, 0xFF, 0xFF, 0xFF)

#include "kstring.h"
#include "memHeap.h"
#include "cmd.h"
#include "cvar.h"
#include "array.h"
#include "stack.h"
#include "queue.h"
#include "hashlist.h"
#include "dict.h"
#include "linkedlist.h"
#include "msort.h"
#include "mathlib.h"
#include "actions.h"
#include "binFile.h"
#include "endian.h"
#include "timer.h"
#include "thread.h"
#include "system.h"
#include "input.h"
#include "session.h"
#include "kpf.h"
#include "object.h"
#include "console.h"
#include "parser.h"
#include "glcontext.h"
#include "sound.h"
#include "defs.h"

class kex
{
public:
    static kexCvar              cvarDeveloper;
    static kexCvar              cvarBasePath;
    
    static kexSystem            *cSystem;
    static kexTimer             *cTimer;
    static kexEndian            *cEndian;
    static kexThread            *cThread;
    static kexInput             *cInput;
    static kexSound             *cSound;
    static kexCvarManager       *cCvars;
    static kexCommand           *cCommands;
    static kexInputAction       *cActions;
    static kexPakFile           *cPakFiles;
    static kexSession           *cSession;
    static kexGameLoop          *cGame;
    static kexConsole           *cConsole;
    static kexParser            *cParser;
    static kexGLContext         *cGLContext;
};

#endif
