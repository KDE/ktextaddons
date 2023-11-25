# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextcustomeditor\")

if(TARGET Qt${QT_MAJOR_VERSION}::TextToSpeech)
    set(HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT TRUE)
endif()

configure_file(config-textcustomeditor.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-textcustomeditor.h)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextCustomEditor")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTCUSTOMEDITOR
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textcustomeditor_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextCustomEditorConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF${KF_MAJOR_VERSION}TextCustomEditor)
add_library(KF${KF_MAJOR_VERSION}::TextCustomEditor ALIAS KF${KF_MAJOR_VERSION}TextCustomEditor)

target_sources(KF${KF_MAJOR_VERSION}TextCustomEditor PRIVATE
    plaintexteditor/plaintexteditfindbar.cpp
    plaintexteditor/plaintexteditor.cpp
    plaintexteditor/plaintexteditorwidget.cpp
    plaintexteditor/plaintextsyntaxspellcheckinghighlighter.cpp
    widgets/findutils.cpp
    widgets/textfindreplacewidget.cpp
    widgets/texteditfindbarbase.cpp
    widgets/textgotolinewidget.cpp
    widgets/textmessageindicator.cpp
    richtexteditor/richtexteditor.cpp
    richtexteditor/richtexteditfindbar.cpp
    richtexteditor/richtexteditorwidget.cpp
    plaintexteditor/plaintexteditfindbar.h
    plaintexteditor/plaintexteditor.h
    plaintexteditor/plaintexteditorwidget.h
    plaintexteditor/plaintextsyntaxspellcheckinghighlighter.h
    widgets/findutils.h
    widgets/textfindreplacewidget.h
    widgets/texteditfindbarbase.h
    widgets/textgotolinewidget.h
    widgets/textmessageindicator.h
    richtexteditor/richtexteditor.h
    richtexteditor/richtexteditfindbar.h
    richtexteditor/richtexteditorwidget.h

    richtextbrowser/richtextbrowser.cpp
    richtextbrowser/richtextbrowser.h
    richtextbrowser/richtextbrowserwidget.cpp
    richtextbrowser/richtextbrowserwidget.h
    richtextbrowser/richtextbrowserfindbar.cpp
    richtextbrowser/richtextbrowserfindbar.h

    core/texteditorcompleter.h
    core/texteditorcompleter.cpp
)

target_link_libraries(KF${KF_MAJOR_VERSION}TextCustomEditor
    PRIVATE
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    KF${KF_MAJOR_VERSION}::SonnetUi
    KF${KF_MAJOR_VERSION}::SonnetCore
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::SyntaxHighlighting
    KF${KF_MAJOR_VERSION}::TextUtils
    KF${KF_MAJOR_VERSION}::TextEmoticonsWidgets
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
)

if (TARGET Qt${QT_MAJOR_VERSION}::TextToSpeech)
    target_link_libraries(KF${KF_MAJOR_VERSION}TextCustomEditor PRIVATE KF${KF_MAJOR_VERSION}TextEditTextToSpeech
    )
endif()

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextCustomEditor HEADER textcustomeditor_debug.h
    IDENTIFIER TEXTCUSTOMEDITOR_LOG
    CATEGORY_NAME org.kde.kf.textcustomeditor
    OLD_CATEGORY_NAMES org.kde.kf${KF_MAJOR_VERSION}.textcustomeditor
    DESCRIPTION "KF${KF_MAJOR_VERSION} (textcustomeditor)" EXPORT KTEXTADDONS)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextCustomEditor PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextCustomEditor BASE_NAME TextCustomEditor)

target_include_directories(KF${KF_MAJOR_VERSION}TextCustomEditor INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextCustomEditor;>")


set_target_properties(KF${KF_MAJOR_VERSION}TextCustomEditor PROPERTIES
    VERSION ${TEXTCUSTOMEDITOR_VERSION}
    SOVERSION ${TEXTCUSTOMEDITOR_SOVERSION}
    EXPORT_NAME TextCustomEditor
)

install(TARGETS KF${KF_MAJOR_VERSION}TextCustomEditor EXPORT KF${KF_MAJOR_VERSION}TextCustomEditorTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(TextCustomEditor_CamelCasetextrichtexteditor_HEADERS
    HEADER_NAMES
    RichTextEditorWidget
    RichTextEditor
    RichTextEditFindBar
    REQUIRED_HEADERS TextCustomEditor_richtexteditor_HEADERS
    PREFIX TextCustomEditor
    RELATIVE richtexteditor
    )

ecm_generate_headers(TextCustomEditor_CamelCaserichtextbrowser_HEADERS
    HEADER_NAMES
    RichTextBrowserWidget
    RichTextBrowser
    RichTextBrowserFindBar
    REQUIRED_HEADERS TextCustomEditor_richtextbrowser_HEADERS
    PREFIX TextCustomEditor
    RELATIVE richtextbrowser
    )

ecm_generate_headers(TextCustomEditor_CamelCaseplaintexteditor_HEADERS
    HEADER_NAMES
    PlainTextEditor
    PlainTextEditorWidget
    PlainTextEditFindBar
    PlainTextSyntaxSpellCheckingHighlighter
    REQUIRED_HEADERS TextCustomEditor_plaintexteditor_HEADERS
    PREFIX TextCustomEditor
    RELATIVE plaintexteditor
    )

ecm_generate_headers(TextCustomEditor_CamelCasetexteditor_widgets_HEADERS
    HEADER_NAMES
    TextGotoLineWidget
    TextEditFindBarBase
    REQUIRED_HEADERS TextCustomEditor_texteditor_widgets_HEADERS
    PREFIX TextCustomEditor
    RELATIVE widgets
    )

ecm_generate_headers(TextCustomEditor_CamelCasetexteditor_core_HEADERS
    HEADER_NAMES
    TextEditorCompleter
    REQUIRED_HEADERS TextCustomEditor_texteditor_core_HEADERS
    PREFIX TextCustomEditor
    RELATIVE core
    )

install(FILES
    ${TextCustomEditor_texteditor_core_HEADERS}
    ${TextCustomEditor_richtexteditor_HEADERS}
    ${TextCustomEditor_texteditor_widgets_HEADERS}
    ${TextCustomEditor_plaintexteditor_HEADERS}
    ${TextCustomEditor_richtextbrowser_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/textcustomeditor_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextCustomEditor/textcustomeditor
    COMPONENT Devel
)
install(FILES
    ${TextCustomEditor_CamelCasetexteditor_core_HEADERS}
    ${TextCustomEditor_CamelCasetextrichtexteditor_HEADERS}
    ${TextCustomEditor_CamelCaseplaintexteditor_HEADERS}
    ${TextCustomEditor_CamelCasetexteditor_widgets_HEADERS}
    ${TextCustomEditor_CamelCaserichtextbrowser_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextCustomEditor/TextCustomEditor/
    COMPONENT Devel
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextCustomEditorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextCustomEditorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF${KF_MAJOR_VERSION}TextCustomEditorTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextCustomEditorTargets.cmake
    NAMESPACE KF${KF_MAJOR_VERSION}::
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textcustomeditor_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextCustomEditor
    COMPONENT Devel
)


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextCustomEditor_QCH
        NAME KF${KF_MAJOR_VERSION}TextCustomEditor
        BASE_NAME KF${KF_MAJOR_VERSION}TextCustomEditor
        VERSION ${TEXTCUSTOMEDITOR_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextCustomEditor_richtexteditor_HEADERS}
        ${TextCustomEditor_texteditor_widgets_HEADERS}
        ${TextCustomEditor_plaintexteditor_HEADERS}
        ${TextCustomEditor_texteditor_core_HEADERS}
        ${TextCustomEditor_richtextbrowser_HEADERS}
        LINK_QCHS
        Qt${QT_MAJOR_VERSION}Core_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTCUSTOMEDITOR_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextCustomEditor_QCH
        FILE KF${KF_MAJOR_VERSION}TextCustomEditorQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextCustomEditorQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextCustomEditorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextCustomEditorConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

if (BUILD_TESTING)
    add_subdirectory(plaintexteditor/autotests)
    add_subdirectory(richtexteditor/autotests)
    add_subdirectory(richtextbrowser/autotests)
    add_subdirectory(widgets/autotests)
    add_subdirectory(plaintexteditor/tests)
    add_subdirectory(richtexteditor/tests)
    add_subdirectory(richtextbrowser/tests)
endif()

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

