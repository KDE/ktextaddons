# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
# add_definitions(-DTRANSLATION_DOMAIN=\"libtextaddonswidgets\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextUtils")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTUTILS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textutils_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextUtilsConfigVersion.cmake"
    SOVERSION 1
)

add_subdirectory(cmark-rc)

add_library(KF6TextUtils)
add_library(KF6::TextUtils ALIAS KF6TextUtils)

target_sources(
    KF6TextUtils
    PRIVATE
        converttext/converttext.cpp
        converttext/converttext.h
        syntaxhighlighting/textutilsiconnamecache.cpp
        syntaxhighlighting/textutilsiconnamecache.h
        syntaxhighlighting/textutilssyntaxhighlighter.cpp
        syntaxhighlighting/textutilssyntaxhighlighter.h
        syntaxhighlighting/textutilssyntaxhighlightingmanager.cpp
        syntaxhighlighting/textutilssyntaxhighlightingmanager.h
        syntaxhighlighting/textutilsblockcodemanager.h
        syntaxhighlighting/textutilsblockcodemanager.cpp
        cmark/textutilsblockcmarksupport.h
        cmark/textutilsblockcmarksupport.cpp
)

target_link_libraries(
    KF6TextUtils
    PRIVATE
        Qt::Core
        KF6::SyntaxHighlighting
        KF6::IconThemes
        KF6::I18n
        cmark-rc
        KF6::CoreAddons
)

ecm_qt_declare_logging_category(KF6TextUtils HEADER textutils_debug.h
    IDENTIFIER TEXTUTILS_LOG
    CATEGORY_NAME org.kde.kf.textutils
    OLD_CATEGORY_NAMES org.kde.kf6.textutils
    DESCRIPTION "KF6 (textutils)" EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextUtils HEADER textutils_syntaxhighlighting_debug.h
    IDENTIFIER TEXTUTILS_SYNTAXHIGHLIGHTING_LOG
    CATEGORY_NAME org.kde.kf.textutils.syntaxhighlighting
    DESCRIPTION "KF6 (textutils syntaxhighlighting)" EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextUtils HEADER textutils_cmark_debug.h
    IDENTIFIER TEXTUTILS_CMARK_LOG
    CATEGORY_NAME org.kde.kf.textutils.cmark
    DESCRIPTION "KF6 (textutils cmark)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextUtils
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextUtils BASE_NAME TextUtils)

target_include_directories(KF6TextUtils INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils;>")

target_link_libraries(KF6TextUtils PUBLIC Qt::Gui)

set_target_properties(
    KF6TextUtils
    PROPERTIES
        VERSION
            ${TEXTUTILS_VERSION}
        SOVERSION
            ${TEXTUTILS_SOVERSION}
        EXPORT_NAME
            TextUtils
)

install(TARGETS KF6TextUtils EXPORT KF6TextUtilsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(TextUtils_CamelCase_HEADERS
    HEADER_NAMES
    ConvertText
    REQUIRED_HEADERS TextUtils_HEADERS
    PREFIX TextUtils
    RELATIVE converttext
)

ecm_generate_headers(TextUtils_Syntaxhighlighting_CamelCase_HEADERS
    HEADER_NAMES
    TextUtilsSyntaxHighlighter
    TextUtilsSyntaxHighlightingManager
    TextUtilsBlockCodeManager
    REQUIRED_HEADERS TextUtils_Syntaxhighlighting_HEADERS
    PREFIX TextUtils
    RELATIVE syntaxhighlighting
)

ecm_generate_headers(TextUtils_CMark_CamelCase_HEADERS
    HEADER_NAMES
    TextUtilsBlockCMarkSupport
    REQUIRED_HEADERS TextUtils_CMark_HEADERS
    PREFIX TextUtils
    RELATIVE cmark
)

install(
    FILES
        ${TextUtils_HEADERS}
        ${TextUtils_Syntaxhighlighting_HEADERS}
        ${TextUtils_CMark_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textutils_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils/textutils
    COMPONENT Devel
)
install(
    FILES
        ${TextUtils_CamelCase_HEADERS}
        ${TextUtils_Syntaxhighlighting_CamelCase_HEADERS}
        ${TextUtils_CMark_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils/TextUtils/
    COMPONENT Devel
)
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextUtils_QCH
        FILE KF6TextUtilsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextUtilsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextUtilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextUtilsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextUtilsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextUtilsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextUtilsTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textutils_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextUtils
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextUtils_QCH
        NAME KF6TextUtils
        BASE_NAME KF6TextUtils
	VERSION ${TEXTUTILS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextUtils_HEADERS}
        LINK_QCHS
        Qt6Core_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTUTILS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
