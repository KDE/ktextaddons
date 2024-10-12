# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextEmoticonsCore")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTEMOTICONSCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textemoticonscore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsCoreConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextEmoticonsCore)
add_library(KF6::TextEmoticonsCore ALIAS KF6TextEmoticonsCore)

target_sources(KF6TextEmoticonsCore PRIVATE
    emoticoncategory.cpp
    emoticoncategory.h
    emoticonunicodeutils.cpp
    emoticonunicodeutils.h
    unicodeemoticon.cpp
    unicodeemoticon.h
    unicodeemoticonmanager.cpp
    unicodeemoticonmanager.h
    unicodeemoticonparser.cpp
    unicodeemoticonparser.h
    emojimodel.cpp
    emojimodel.h
    emojisortfilterproxymodel.cpp
    emojisortfilterproxymodel.h
    emojimodelmanager.cpp
    emojimodelmanager.h

    customemoji.h
    customemoji.cpp

    customemojiiconmanager.h
    customemojiiconmanager.cpp
    runninganimatedimage.h
    runninganimatedimage.cpp

    emojicategory.cpp
    emojicategory.h
)

target_link_libraries(KF6TextEmoticonsCore
    PUBLIC
    Qt::Gui
    PRIVATE
    KF6::ConfigCore
    KF6::CoreAddons
)

ecm_qt_declare_logging_category(KF6TextEmoticonsCore HEADER textemoticonscore_debug.h
    IDENTIFIER TEXTEMOTICONSCORE_LOG
    CATEGORY_NAME org.kde.kf.textemoticonscore
    OLD_CATEGORY_NAMES org.kde.kf6.textemoticonscore
    DESCRIPTION "KF6 (textaddons textemotions core)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextEmoticonsCore
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextEmoticonsCore BASE_NAME TextEmoticonsCore)

target_include_directories(
    KF6TextEmoticonsCore
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsCore;>"
)

target_link_libraries(KF6TextEmoticonsCore PRIVATE KF6::I18n)

set_target_properties(
    KF6TextEmoticonsCore
    PROPERTIES
        VERSION
            ${TEXTEMOTICONSCORE_VERSION}
        SOVERSION
            ${TEXTEMOTICONSCORE_SOVERSION}
        EXPORT_NAME
            TextEmoticonsCore
)

install(TARGETS KF6TextEmoticonsCore EXPORT KF6TextEmoticonsCoreTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

ecm_generate_headers(TextEmoticonsCore_CamelCase_HEADERS
    HEADER_NAMES
    UnicodeEmoticonManager
    UnicodeEmoticon
    CustomEmoji
    EmoticonCategory
    EmoticonUnicodeUtils
    EmojiModel
    EmojiSortFilterProxyModel
    EmojiModelManager
    UnicodeEmoticonParser
    CustomEmojiIconManager
    RunningAnimatedImage
    REQUIRED_HEADERS TextEmoticonsCore_HEADERS
    PREFIX TextEmoticonsCore
)

install(
    FILES
        ${TextEmoticonsCore_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textemoticonscore_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsCore/textemoticonscore
    COMPONENT Devel
)
install(
    FILES
        ${TextEmoticonsCore_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsCore/TextEmoticonsCore/
    COMPONENT Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextEmoticonsCoreTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextEmoticonsCoreTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textemoticonscore_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsCore
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextEmoticonsCore_QCH
        NAME KF6TextEmoticonsCore
        BASE_NAME KF6TextEmoticonsCore
        VERSION ${TEXTEMOTICONSCORE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextEmoticonsCore_HEADERS}
        LINK_QCHS
        Qt6Core_QCH
        Qt6Gui_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTEMOTICONSCORE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextEmoticonsCore_QCH
        FILE KF6TextEmoticonsCoreQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextEmoticonsCoreQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextEmoticonsCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

add_subdirectory(data)
