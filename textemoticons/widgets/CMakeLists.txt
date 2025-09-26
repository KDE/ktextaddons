# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextEmoticonsWidgets")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTEMOTICONSWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textemoticonswidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsWidgetsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextEmoticonsWidgets)
add_library(KF6::TextEmoticonsWidgets ALIAS KF6TextEmoticonsWidgets)

target_sources(
    KF6TextEmoticonsWidgets
    PRIVATE
        emoticontexteditselector.cpp
        emoticontexteditselector.h
        emoticoncategorybuttons.cpp
        emoticoncategorybuttons.h
        emoticonlistview.cpp
        emoticonlistview.h
        textemoticonswidgets_private_export.h
        emoticontexteditaction.h
        emoticontexteditaction.cpp
        emoticoncategorybutton.h
        emoticoncategorybutton.cpp
        emoticonitemdelegate.cpp
        emoticonitemdelegate.h
        emoticontonecombobox.h
        emoticontonecombobox.cpp
        emoticonwidgetaction.h
        emoticonwidgetaction.cpp
        emoticonwidgetactionwidget.h
        emoticonwidgetactionwidget.cpp
)

target_link_libraries(
    KF6TextEmoticonsWidgets
    PUBLIC
        KF6::WidgetsAddons
        KF6::TextEmoticonsCore
    PRIVATE
        Qt::Widgets
)

ecm_qt_declare_logging_category(KF6TextEmoticonsWidgets HEADER textemoticonswidgets_debug.h
    IDENTIFIER TEXTEMOTICONSWIDGETS_LOG
    CATEGORY_NAME org.kde.kf.textemoticonswidgets
    OLD_CATEGORY_NAMES org.kde.kf6.textemoticonswidgets
    DESCRIPTION "KF6 (textaddons textemoticons widgets)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextEmoticonsWidgets
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextEmoticonsWidgets BASE_NAME TextEmoticonsWidgets)

target_include_directories(
    KF6TextEmoticonsWidgets
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsWidgets;>"
)

target_link_libraries(KF6TextEmoticonsWidgets PRIVATE KF6::I18n)

set_target_properties(
    KF6TextEmoticonsWidgets
    PROPERTIES
        VERSION
            ${TEXTEMOTICONSWIDGETS_VERSION}
        SOVERSION
            ${TEXTEMOTICONSWIDGETS_SOVERSION}
        EXPORT_NAME
            TextEmoticonsWidgets
)

install(TARGETS KF6TextEmoticonsWidgets EXPORT KF6TextEmoticonsWidgetsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

ecm_generate_headers(TextEmoticonsWidgets_CamelCase_HEADERS
    HEADER_NAMES
    EmoticonTextEditSelector
    EmoticonTextEditAction
    EmoticonWidgetActionWidget
    EmoticonWidgetAction
    REQUIRED_HEADERS TextEmoticonsWidgets_HEADERS
    PREFIX TextEmoticonsWidgets
)

install(
    FILES
        ${TextEmoticonsWidgets_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textemoticonswidgets_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsWidgets/textemoticonswidgets
    COMPONENT Devel
)
install(
    FILES
        ${TextEmoticonsWidgets_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsWidgets/TextEmoticonsWidgets/
    COMPONENT Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsWidgetsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextEmoticonsWidgetsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextEmoticonsWidgetsTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textemoticonswidgets_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticonsWidgets
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextEmoticonsWidgets_QCH
        NAME KF6TextEmoticonsWidgets
        BASE_NAME KF6TextEmoticonsWidgets
        VERSION ${TEXTEMOTICONSWIDGETS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextEmoticonsWidgets_HEADERS}
        LINK_QCHS
        Qt6Core_QCH
        Qt6Gui_QCH
        Qt6Widgets_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTEMOTICONSWIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextEmoticonsWidgets_QCH
        FILE KF6TextEmoticonsWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextEmoticonsWidgetsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextEmoticonsWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEmoticonsWidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)
