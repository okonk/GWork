# source: https://github.com/liballeg/allegro5/blob/master/cmake/FindGDIPLUS.cmake

# Copyright (c) 2004-2015 the Allegro 5 Development Team
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source
#     distribution.

# - Find GDI+
# Find the GDI+ includes and libraries
#
#  GDIPLUS_INCLUDE_DIR - where to find gdiplus.h
#  GDIPLUS_LIBRARIES   - List of libraries when using GDI+.
#  GDIPLUS_FOUND       - True if GDI+ found.

if(GDIPLUS_INCLUDE_DIR)
    # Already in cache, be silent
    set(GDIPLUS_FIND_QUIETLY TRUE)
endif(GDIPLUS_INCLUDE_DIR)

macro(check_winsdk_root_dir key)
  get_filename_component(CANDIDATE ${key} ABSOLUTE)
  if (EXISTS ${CANDIDATE})
    set(WINSDK_ROOT_DIR ${CANDIDATE})
  endif()
endmacro()

check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Microsoft SDKs\\\\Windows\\\\v7.0;InstallationFolder]")
check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Microsoft SDKs\\\\Windows\\\\v7.0A;InstallationFolder]")
check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Microsoft SDKs\\\\Windows\\\\v7.1;InstallationFolder]")
check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Microsoft SDKs\\\\Windows\\\\v7.1A;InstallationFolder]")
check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Windows Kits\\\\Installed Roots;KitsRoot]")
check_winsdk_root_dir("[HKEY_LOCAL_MACHINE\\\\SOFTWARE\\\\Microsoft\\\\Windows Kits\\\\Installed Roots;KitsRoot81]")

find_path(GDIPLUS_INCLUDE_DIR
    NAMES
        GdiPlus.h
        gdiplus.h
    PATH_SUFFIXES
        Include
        Include/um
        Include/shared
    PATHS
        "${WINSDK_ROOT_DIR}"
    )
if(EXISTS ${GDIPLUS_INCLUDE_DIR}/GdiPlus.h)
    set(GDIPLUS_LOWERCASE 0 CACHE INTERNAL "Is GdiPlus.h spelt with lowercase?")
else()
    set(GDIPLUS_LOWERCASE 1 CACHE INTERNAL "Is GdiPlus.h spelt with lowercase?")
endif()

if (MINGW)
	find_library(GDIPLUS_LIBRARY NAMES libgdiplus gdiplus)
else(MINGW)
	set(GDIPLUS_LIBRARY gdiplus)
endif(MINGW)


# Handle the QUIETLY and REQUIRED arguments and set GDIPLUS_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GDIPLUS DEFAULT_MSG
    GDIPLUS_INCLUDE_DIR GDIPLUS_LIBRARY)

if(GDIPLUS_FOUND)
    set(GDIPLUS_LIBRARIES ${GDIPLUS_LIBRARY})
else(GDIPLUS_FOUND)
    set(GDIPLUS_LIBRARIES)
endif(GDIPLUS_FOUND)

mark_as_advanced(GDIPLUS_INCLUDE_DIR GDIPLUS_LIBRARY GDIPLUS_LOWERCASE)
