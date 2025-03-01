# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtextautogeneratetext\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutogenerateText")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutogenerateTextConfigVersion.cmake"
    SOVERSION 1
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutogenerateTextConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutogenerateTextConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF6TextAutogenerateTextTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF6TextAutogenerateTextTargets.cmake NAMESPACE KF6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutogenerateText/ COMPONENT Devel
)

add_library(KF6TextAutogenerateText)
add_library(KF6::TextAutogenerateText ALIAS KF6TextAutogenerateText)
ecm_qt_declare_logging_category(KF6TextAutogenerateText HEADER textautogeneratetext_debug.h
    IDENTIFIER TEXTAUTOGENERATETEXT_LOG
    CATEGORY_NAME org.kde.kf.textautogeneratetext
    DESCRIPTION "KF6 (TextAutogenerateText)"
    EXPORT KTEXTADDONS
)

target_sources(KF6TextAutogenerateText PRIVATE
    core/textautogenerateengineplugin.h
    core/textautogenerateengineplugin.cpp
    core/textautogenerateengineloader.cpp
    core/textautogenerateengineloader.h
    core/textautogeneratetextclient.h
    core/textautogeneratetextclient.cpp
    core/textautogeneratetextplugin.h
    core/textautogeneratetextplugin.cpp
    core/textautogeneratemanager.h
    core/textautogeneratemanager.cpp

    core/textautogenerateengineutil.h
    core/textautogenerateengineutil.cpp
)

target_sources(KF6TextAutogenerateText PRIVATE
    widgets/textautogenerateconfigurewidget.h
    widgets/textautogenerateconfigurewidget.cpp
    widgets/textautogeneratetextconfigurecombowidget.cpp
    widgets/textautogeneratetextconfigurecombowidget.h

    widgets/textautogeneratetextlineeditwidget.h
    widgets/textautogeneratetextlineeditwidget.cpp

    widgets/textautogenerateresultwidget.h
    widgets/textautogenerateresultwidget.cpp
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

add_subdirectory(autogenerate/plugins)


if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF6TextAutogenerateText PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF6TextAutogenerateText BASE_NAME textautogeneratetext)


target_link_libraries(KF6TextAutogenerateText
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::Network
    PRIVATE
    KF6::I18n
    KF6::ConfigCore
)

target_include_directories(KF6TextAutogenerateText INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutogenerateText/>")

set_target_properties(KF6TextAutogenerateText PROPERTIES
    VERSION ${TEXTAUTOGENERATETEXT_VERSION}
    SOVERSION ${TEXTAUTOGENERATETEXT_SOVERSION}
    EXPORT_NAME TextAutogenerateText
)

ecm_generate_headers(TextAutogenerateText_Camelcasestextautogeneratetextcore_HEADERS
    HEADER_NAMES
    TextAutogenerateEnginePlugin
    TextAutogenerateTextClient
    TextAutogenerateTextPlugin
    REQUIRED_HEADERS TextAutogenerateText_textautogeneratetextcore_HEADERS
    PREFIX TextAutogenerateText
    RELATIVE core
)

ecm_generate_headers(TextAutogenerateText_Camelcasestextautogeneratetextwidgets_HEADERS
    HEADER_NAMES
    TextAutogenerateConfigureWidget
    TextAutogenerateResultWidget
    REQUIRED_HEADERS TextAutogenerateText_textautogeneratetextwidgets_HEADERS
    PREFIX TextAutogenerateText
    RELATIVE widgets
)

install(TARGETS
    KF6TextAutogenerateText
    EXPORT KF6TextAutogenerateTextTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutogenerateText/ COMPONENT Devel
)

install(FILES
    ${TextAutogenerateText_Camelcasestextautogeneratetextcore_HEADERS}
    ${TextAutogenerateText_Camelcasestextautogeneratetextwidgets_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutogenerateText/TextAutogenerateText
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetext_export.h
    ${TextAutogenerateText_textautogeneratetextcore_HEADERS}
    ${TextAutogenerateText_textautogeneratetextwidgets_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutogenerateText/textautogeneratetext
    COMPONENT Devel
)


if(BUILD_QCH)
    ecm_add_qch(
        KF6TextAutogenerateText_QCH
        NAME KF6TextAutogenerateText
        BASE_NAME KF6TextAutogenerateText
        VERSION ${TEXTAUTOGENERATETEXT_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutogenerateText_textautogeneratetextcore_HEADERS}
        ${TextAutogenerateText_textautogeneratetextwidgets_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOGENERATETEXT_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextAutogenerateText_QCH
        FILE KF6TextAutogenerateTextQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
)
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextAutogenerateTextQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutogenerateTextConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutogenerateTextConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)
