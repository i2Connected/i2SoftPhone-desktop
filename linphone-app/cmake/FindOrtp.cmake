############################################################################
# FindOrtp.cmake
# Copyright (C) 2023  Belledonne Communications, Grenoble France
#
############################################################################
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
############################################################################
#
# - Find the ortp include files and library
#
#  LINPHONE_TARGETS - Add usable targets into this list.
#  ORTP_FOUND - system has lib ortp
#  ORTP_INCLUDE_DIRS - the ortp include directory
#  ORTP_LIBRARIES - The library needed to use ortp
if(NOT TARGET ortp)
    set(EXPORT_PATH ${LINPHONE_OUTPUT_DIR})
    include(GNUInstallDirs)
    include(${EXPORT_PATH}/${CMAKE_INSTALL_LIBDIR}/cmake/ortp/ortpTargets.cmake)
endif()

if(TARGET ortp)
	list(APPEND LINPHONE_TARGETS ortp)
    set(ORTP_LIBRARIES ortp)
    get_target_property(ORTP_INCLUDE_DIRS ortp INTERFACE_INCLUDE_DIRECTORIES)

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(Ortp
            DEFAULT_MSG
            ORTP_INCLUDE_DIRS ORTP_LIBRARIES
    )

    mark_as_advanced(ORTP_INCLUDE_DIRS ORTP_LIBRARIES)

endif()
