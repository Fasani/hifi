# 
#  FindFaceshift.cmake
# 
#  Try to find the GnuTLS library
#
#  You can provide a GNUTLS_ROOT_DIR which contains lib and include directories
#
#  Once done this will define
#
#  GNUTLS_FOUND - system found GnuTLS
#  GNUTLS_INCLUDE_DIR - the GnuTLS include directory
#  GNUTLS_LIBRARY - Link this to use GnuTLS
#
#  Created on 3/31/2014 by Stephen Birarda
#  Copyright (c) 2014 High Fidelity
#
#  Distributed under the Apache License, Version 2.0.
#  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
#

if (GNUTLS_LIBRARY AND GNUTLS_INCLUDE_DIRS)
  # in cache already
  set(GNUTLS_FOUND TRUE)
else ()
  
  set(GNUTLS_SEARCH_DIRS "${GNUTLS_ROOT_DIR}" "$ENV{HIFI_LIB_DIR}/gnutls")
  
  find_path(GNUTLS_INCLUDE_DIR gnutls.h PATH_SUFFIXES include/gnutls gnutls HINTS ${GNUTLS_SEARCH_DIRS})

  find_library(GNUTLS_LIBRARY NAMES gnutls libgnutls libgnutls-28 PATH_SUFFIXES lib bin HINTS ${GNUTLS_SEARCH_DIRS})
  
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(GNUTLS DEFAULT_MSG GNUTLS_INCLUDE_DIR GNUTLS_LIBRARY)
endif ()