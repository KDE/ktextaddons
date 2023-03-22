# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextAutoCorrection")


configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoCorrectionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTION
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

add_subdirectory(src)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection/ COMPONENT Devel
    )
