PowerslaveEX-Plus GPL Source Code
=======================================

Please note: This does not 'yet' support the remastered data due to some issues.  This only supports the older EX 'game.kpf' file.  I will not say where to find it and I will never supply it.  If you have the required data already, I strongly urge you to also buy the remastered version, if only to support the efforts of the ND team and the rights holders.

Compiling on Windows:
-------------------

A project file for Microsoft Visual Studio 2022 is provided in kex3_anubis/msvc/
Just open, and build.  All dependencies are assumed to be done via 'vcpkg' on windows and the default path reflects this.

Compiling on macOS:
-------------------

A project file and all required dependencies are located in kex3_anubis/xcode/
Just open, and build.

Compiling on GNU/Linux:
-------------------

A Makefile is supplied in kex3_anubis/source
Dependencies are assumed to already be installed (the -dev / -devel versions) from your package manager.

Dependencies
-------------------

Powerslave EX uses the following third-party libraries (included in this repo)
* SDL2
* Angelscript <-- already supplied as 2.30.2 in kex3_anubis/angelscript
* OpenAL
* Vorbis
* LibPNG
* ZLib

Please Note: FFMPEG support was removed as I do not know the API and have no interest in learning it, the version used was extremely old and would have required a lot of effort to simply play a few movies.  Contributors are welcome to do a PR with a multiplatform implementation of the latest version if they so wish.

Paths
-------------------
* On Windows, place the 'game.kpf' file in the same directory as the binary.
* On macOS, place the 'game.kpf' file in Library/Application Support/ExhumedEXPlus
* On GNU/Linux, place the 'game.kpf' file in the same directory as the binary.
