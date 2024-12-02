# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_factarial_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED factarial_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(factarial_FOUND FALSE)
  elseif(NOT factarial_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(factarial_FOUND FALSE)
  endif()
  return()
endif()
set(_factarial_CONFIG_INCLUDED TRUE)

# output package information
if(NOT factarial_FIND_QUIETLY)
  message(STATUS "Found factarial: 0.0.0 (${factarial_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'factarial' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${factarial_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(factarial_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${factarial_DIR}/${_extra}")
endforeach()
