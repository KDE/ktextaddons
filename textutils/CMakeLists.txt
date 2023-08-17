# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
# add_definitions(-DTRANSLATION_DOMAIN=\"libtextaddonswidgets\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextUtils")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTUTILS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textutils_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextUtilsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF${KF_MAJOR_VERSION}TextUtils)
add_library(KF${KF_MAJOR_VERSION}::TextUtils ALIAS KF${KF_MAJOR_VERSION}TextUtils)

target_sources(KF${KF_MAJOR_VERSION}TextUtils PRIVATE
    converttext.cpp
    converttext.h
)

target_link_libraries(KF${KF_MAJOR_VERSION}TextUtils
    PRIVATE
    Qt::Core
)

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextUtils HEADER textutils_debug.h
    IDENTIFIER TEXTUTILS_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textutils
    DESCRIPTION "KF${KF_MAJOR_VERSION} (textutils)" EXPORT KTEXTADDONS)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextUtils PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextUtils BASE_NAME TextUtils)

target_include_directories(KF${KF_MAJOR_VERSION}TextUtils INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils;>")


target_link_libraries(KF${KF_MAJOR_VERSION}TextUtils
    PRIVATE
    Qt::Core
)

set_target_properties(KF${KF_MAJOR_VERSION}TextUtils PROPERTIES
    VERSION ${TEXTUTILS_VERSION}
    SOVERSION ${TEXTUTILS_SOVERSION}
    EXPORT_NAME TextUtils
)

install(TARGETS KF${KF_MAJOR_VERSION}TextUtils EXPORT KF${KF_MAJOR_VERSION}TextUtilsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(TextUtils_CamelCase_HEADERS
    HEADER_NAMES
    ConvertText
    REQUIRED_HEADERS TextUtils_HEADERS
    PREFIX TextUtils
)

install(FILES
    ${TextUtils_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/textutils_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils/textutils
    COMPONENT Devel
)
install(FILES
    ${TextUtils_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils/TextUtils/
    COMPONENT Devel
)
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextUtils_QCH
        FILE KF${KF_MAJOR_VERSION}TextUtilsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextUtilsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextUtilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextUtilsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF${KF_MAJOR_VERSION}TextUtilsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextUtilsTargets.cmake
    NAMESPACE KF${KF_MAJOR_VERSION}::
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textutils_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils
    COMPONENT Devel
)


ecm_generate_pri_file(BASE_NAME textaddonswidgets LIB_NAME TextUtils DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR
    ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils/)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextUtils_QCH
        NAME KF${KF_MAJOR_VERSION}TextUtils
        BASE_NAME KF${KF_MAJOR_VERSION}TextUtils
	VERSION ${TEXTUTILS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextUtils_HEADERS}
        LINK_QCHS
        Qt${QT_MAJOR_VERSION}Core_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTADDONSWIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
