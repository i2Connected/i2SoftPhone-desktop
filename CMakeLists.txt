################################################################################
#
#  Copyright (c) 2010-2023 Belledonne Communications SARL.
# 
#  This file is part of linphone-desktop
#  (see https://www.linphone.org).
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.
#
################################################################################

cmake_minimum_required(VERSION 3.22)

get_cmake_property(vars CACHE_VARIABLES)
foreach(var ${vars})
	get_property(currentHelpString CACHE "${var}" PROPERTY HELPSTRING)
	if("${currentHelpString}" MATCHES "No help, variable specified on the command line." OR "${currentHelpString}" STREQUAL "")
		#message("${var} = [${${var}}]  --  ${currentHelpString}") # uncomment to see the variables being processed
		list(APPEND USER_ARGS "-D${var}=${${var}}")
		if( "${var}" STREQUAL "CMAKE_PREFIX_PATH")
			set(PREFIX_PATH ";${${var}}")
		endif()
	elseif("${var}" STREQUAL "CMAKE_GENERATOR_PLATFORM" AND NOT("${${var}}" STREQUAL ""))
		message(STATUS "User-Setting Platform to ${${var}}")
	endif()
endforeach()
if(ENABLE_BUILD_VERBOSE)
	message("User Args : ${USER_ARGS}")
endif()
if( APPLE )
	if( NOT CMAKE_OSX_DEPLOYMENT_TARGET)
		set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
	endif()
	if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
		set(LINPHONESDK_MACOS_ARCHS "arm64, x86_64" CACHE STRING "MacOS architectures to build for: comma-separated list of values in [arm64, x86_64]")
	else()
		set(LINPHONESDK_MACOS_ARCHS "x86_64" CACHE STRING "MacOS architectures to build for: comma-separated list of values in [x86_64]")
	endif()
endif()

project(linphoneqt)

include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(APPLICATION_OUTPUT_DIR "${CMAKE_BINARY_DIR}/OUTPUT")
#set(LINPHONE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/linphone-sdk/desktop")	# Fromp 5.3, this install output is no more usable. We have to install all into the same folder as the final folder.
#set(QTKEYCHAIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/qtkeychain")
set(LINPHONE_OUTPUT_DIR "${APPLICATION_OUTPUT_DIR}")
set(QTKEYCHAIN_OUTPUT_DIR "${APPLICATION_OUTPUT_DIR}")

set(QTKEYCHAIN_TARGET_NAME "EQt5Keychain")

# Avoid cmake warning if CMP0071 is not set.
if (POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif ()
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#------------------------------------------------------------------------------
# Prepare gobal CMAKE configuration specific to the current project

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/OUTPUT" CACHE PATH "Default linphone-app installation prefix" FORCE)
	set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT FALSE)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified")
	set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)
	# Set the available build type values for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

# ------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
#				SET OPTIONS
#-------------------------------------------------------------------------------

option(ENABLE_APP_LICENSE "Enable the license in packages." ON)
option(ENABLE_APP_OAUTH2 "Build with OAuth2 support for remote provisioning." OFF) # Experimental.
option(ENABLE_APP_PACKAGING "Enable packaging" OFF)
option(ENABLE_APP_PACKAGE_ROOTCA "Embed the rootca file into the package" ON)
option(ENABLE_APP_PDF_VIEWER "Enable Pdf viewer" ON)
option(ENABLE_APP_WEBVIEW "Enable webviews." OFF) # Webview is not fully supported because of deployments. Used for subscription.
option(ENABLE_BUILD_APP_PLUGINS "Enable the build of plugins" ON)
option(ENABLE_BUILD_EXAMPLES "Enable the build of examples" OFF)
option(ENABLE_BUILD_VERBOSE "Enable the build generation to be more verbose" OFF)
option(ENABLE_CONSOLE_UI "Turn on or off compilation of console interface." OFF)
option(ENABLE_DAEMON "Enable the linphone daemon interface." OFF)
option(ENABLE_DOC "Enable API documentation generation." OFF)
option(ENABLE_FFMPEG "Build mediastreamer2 with ffmpeg video support." OFF)# No more needed
option(ENABLE_LDAP "Enable LDAP support." YES)
option(ENABLE_NON_FREE_CODECS "Enable the use of non free codecs" YES)
set(ENABLE_NON_FREE_FEATURES ${ENABLE_NON_FREE_CODECS})
option(ENABLE_OPENH264 "Enable the use of OpenH264 codec" YES)
option(ENABLE_QT_KEYCHAIN "Build QtKeychain to manage VFS from System key stores." ON)
option(ENABLE_QRCODE "Enable QRCode support" OFF)#Experimental
option(ENABLE_RELATIVE_PREFIX "Set Internal packages relative to the binary" ON)
option(ENABLE_SANITIZER "Enable sanitizer." OFF)
option(ENABLE_STRICT "Build with strict compilator flags e.g. -Wall -Werror" OFF)
option(ENABLE_TESTS "Build with testing binaries of SDK" OFF)
option(ENABLE_TESTS_COMPONENTS "Build libbctoolbox-tester" OFF)
option(ENABLE_TOOLS "Enable tools of SDK" OFF)
option(ENABLE_UNIT_TESTS "Enable unit test of SDK." OFF)
option(ENABLE_UPDATE_CHECK "Enable update check." ON)
option(ENABLE_VIDEO "Enable Video support." YES)
option(ENABLE_WINDOWS_TOOLS_CHECK "Enable tools checks on Windows for auto install." OFF)


option(LINPHONE_SDK_MAKE_RELEASE_FILE_URL "Make a RELEASE file that work along check_version and use this URL" "")

# QtKeychain
option(LIBSECRET_SUPPORT "Build with libsecret support" OFF) # Need libsecret-devel

if(WIN32)
	option(ENABLE_OPENSSL_EXPORT "Enable OpenSSL deployment" YES)
elseif(APPLE)
	option(ENABLE_OPENSSL_EXPORT "Enable OpenSSL deployment" OFF)
else()
	option(ENABLE_V4L "Ability to capture and display video using libv4l2 or libv4l." YES)
	option(ENABLE_OPENSSL_EXPORT "Enable OpenSSL deployment" OFF)
endif()

# Set some SDK variables to configure the APP build as we want it
set(ENABLE_CXX_WRAPPER ON CACHE BOOL "Build the C++ wrapper for Liblinphone." FORCE)
set(ENABLE_THEORA OFF)
set(ENABLE_QT_GL ${ENABLE_VIDEO})

find_package(Qt5 5.10 COMPONENTS Core REQUIRED)

if(NOT Qt5_FOUND)
	message(FATAL_ERROR "Minimum supported Qt5 version is 5.10!")
endif()

if(NOT LINPHONE_QT_ONLY)

	function(add_linphone_sdk)
		set(CMAKE_INSTALL_PREFIX "${LINPHONE_OUTPUT_DIR}")
		set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # Prevent project from overriding the options we just set here
		add_subdirectory("linphone-sdk")
	endfunction()
	add_linphone_sdk()

	if(ENABLE_QT_KEYCHAIN)
		function(add_linphone_keychain)
			set(CMAKE_INSTALL_PREFIX "${QTKEYCHAIN_OUTPUT_DIR}")
			add_subdirectory("external/qtkeychain")
		endfunction()
		add_linphone_keychain()
	endif()

endif()

function(add_linphone_app)
	set(CMAKE_INSTALL_PREFIX "${APPLICATION_OUTPUT_DIR}")
	set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # Prevent project from overriding the options we just set here
	if(APPLE)
		add_compile_definitions("ENABLE_FAT_BINARY=ON") # Disable XCFrameworks as it is not supported.
	elseif(UNIX)
		set(CMAKE_INSTALL_RPATH "$ORIGIN:$ORIGIN/lib64:$ORIGIN/../lib64:$ORIGIN/lib:$ORIGIN/../lib")
	endif()

	add_subdirectory("linphone-app")
endfunction()
add_linphone_app()


if(ENABLE_BUILD_APP_PLUGINS)
	add_subdirectory("plugins" "plugins-app")
endif()
