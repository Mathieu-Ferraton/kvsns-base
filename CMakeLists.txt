cmake_minimum_required(VERSION 2.6.4)
cmake_policy(SET CMP0017 NEW)

PROJECT(libkvsns C)
set(LIBKVSNS_MAJOR_VERSION 1)
set(LIBKVSNS_MINOR_VERSION 3)
set(LIBKVSNS_PATCH_LEVEL 1)
set(LIBKVSNS_EXTRA_VERSION "")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_SOURCE_DIR}/include -fPIC -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(LIBKVSNS_BASE_VERSION ${LIBKVSNS_MAJOR_VERSION}.${LIBKVSNS_MINOR_VERSION}.${LIBKVSNS_PATCH_LEVEL})

message( STATUS "cmake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" )
message( STATUS "libkvsns version ${LIBKVSNS_BASE_VERSION}")

# Final tuning

include(CheckIncludeFiles)
include(CheckLibraryExists)

## Check ini_config
check_include_files("ini_config.h" HAVE_INI_CONFIG_H)
find_library(HAVE_INI_CONFIG ini_config)
check_library_exists(
	ini_config
	config_from_file
	""
	HAVE_INI_CONFIG
	)

# Build ancillary libs
add_subdirectory(kvsns)
add_subdirectory(tests)
add_subdirectory(kvsns_shell)
add_subdirectory(kvsns_script)
add_subdirectory(kvsns_attach)
add_subdirectory(kvsns_hsm)

# CPack / rpmbuild specific stuff
set(CPACK_PACKAGE_FILE_NAME "libkvsns-Source" )
set(CPACK_PACKAGE_VENDOR "KVSNS")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "KVSNS - a namespace on top of a KVS")
SET(CPACK_PACKAGE_VERSION_MAJOR ${LIBKVSNS_MAJOR_VERSION})
SET(CPACK_PACKAGE_VERSION_MINOR ${LIBKVSNS_MINOR_VERSION})
SET(CPACK_PACKAGE_VERSION_PATCH ${LIBKVSNS_PATCH_LEVEL})

# Tell CPack the kind of packages to be generated
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_SOURCE_IGNORE_FILES
  "/.git/;/.gitignore/;/build/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")

include(CPack)

set(PKG_NAME "${CPACK_PACKAGE_NAME}.tar.gz")
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# Create the .pc file
configure_file(
  "${PROJECT_SOURCE_DIR}/libkvsns.pc-in.cmake"
  "${PROJECT_SOURCE_DIR}/libkvsns.pc"
)

# Now create a useable specfile
configure_file(
  "${PROJECT_SOURCE_DIR}/libkvsns.spec-in.cmake"
  "${PROJECT_SOURCE_DIR}/libkvsns.spec"
)

set(RPMDEST "--define '_srcrpmdir ${CMAKE_CURRENT_BINARY_DIR}'")

add_custom_target( rpms DEPENDS dist)
add_custom_command(TARGET rpms
                  COMMAND sh -c "rpmbuild ${RPMDEST} -ta ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                  VERBATIM
                  DEPENDS dist)

add_custom_target( rpm DEPENDS dist)
add_custom_command(TARGET rpm
                  COMMAND sh -c "rpmbuild ${RPMDEST} -tb ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                  VERBATIM
                  DEPENDS dist)

add_custom_target( srpm DEPENDS dist)
add_custom_command(TARGET srpm
                  COMMAND sh -c "rpmbuild ${RPMDEST} -ts ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.gz"
                  VERBATIM
                  DEPENDS dist)

# INSTALL
install(FILES ${PROJECT_SOURCE_DIR}/libkvsns.pc DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/iosea DESTINATION include)
