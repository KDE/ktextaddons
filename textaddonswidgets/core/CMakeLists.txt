# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAddonsCore")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTADDONSCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textaddonscore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsCoreConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextAddonsCore)
add_library(KF6::TextAddonsCore ALIAS KF6TextAddonsCore)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        KF6TextAddonsCore
        PRIVATE
            <QObject>
            <QDebug>
            <QStringList>
            <QString>
    )
endif()

target_sources(
    KF6TextAddonsCore
    PRIVATE
        model/sortfilterproxymodelbase.h
        model/sortfilterproxymodelbase.cpp
)

target_link_libraries(KF6TextAddonsCore PUBLIC Qt::Core PRIVATE KF6::TextUtils)

ecm_qt_declare_logging_category(KF6TextAddonsCore HEADER textaddonscore_debug.h
    IDENTIFIER TEXTADDONSCORE_LOG
    CATEGORY_NAME org.kde.kf.textaddonscore
    OLD_CATEGORY_NAMES org.kde.kf6.textaddonscore
    DESCRIPTION "KF6 (textaddons core)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAddonsCore
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
ecm_generate_export_header(KF6TextAddonsCore
    BASE_NAME TextAddonsCore
    VERSION ${TEXTADDONSCORE_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)

target_include_directories(
    KF6TextAddonsCore
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsCore;>"
)

set_target_properties(
    KF6TextAddonsCore
    PROPERTIES
        VERSION
            ${TEXTADDONSCORE_VERSION}
        SOVERSION
            ${TEXTADDONSCORE_SOVERSION}
        EXPORT_NAME
            TextAddonsCore
)

install(TARGETS KF6TextAddonsCore EXPORT KF6TextAddonsCoreTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(TextAddonsCore_Camelcasemodel_HEADERS
    HEADER_NAMES
        SortFilterProxyModelBase
    REQUIRED_HEADERS TextAddonsCore_model_HEADERS
    PREFIX TextAddonsCore
    RELATIVE model
)

set(TEXTADDONSCORE_INCLUDES_FILES ${TextAddonsCore_model_HEADERS})

install(
    FILES
        ${TEXTADDONSCORE_INCLUDES_FILES}
        ${CMAKE_CURRENT_BINARY_DIR}/textaddonscore_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsCore/textaddonscore
    COMPONENT Devel
)
set(TextAddonsCore_List_CamelCase_HEADERS ${TextAddonsCore_Camelcasemodel_HEADERS})
install(
    FILES
        ${TextAddonsCore_List_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsCore/TextAddonsCore/
    COMPONENT Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAddonsCoreTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAddonsCoreTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textaddonscore_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsCore
    COMPONENT Devel
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAddonsCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

ecm_generate_qdoc(KF6TextAddonsCore textaddonscore.qdocconf)

ecm_add_installed_library_check(KF6TextAddonsCore
    PACKAGE_NAME "KF6TextAddonsCore"
    PACKAGE_VERSION ${TEXTADDONSCORE_VERSION}
    PACKAGE_TARGET_NAMESPACE "KF6::"
)

ecm_installed_library_check_include_strings(KF6TextAddonsCore
    HEADERS ${TEXTADDONSCORE_INCLUDES_FILES}
    PREFIX textaddonscore
)

ecm_installed_library_check_include_strings(KF6TextAddonsCore
    HEADERS
        ${TextAddonsCore_List_CamelCase_HEADERS}
    PREFIX TextAddonsCore
)
