# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextedittexttospeech\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextEditTextToSpeech")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTEDITTEXTTOSPEECH
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEditTextToSpeechConfigVersion.cmake"
    SOVERSION 1
)

add_subdirectory(kokoro)

add_library(KF6TextEditTextToSpeech)
add_library(KF6::TextEditTextToSpeech ALIAS KF6TextEditTextToSpeech)

target_sources(
    KF6TextEditTextToSpeech
    PRIVATE
        texttospeech.cpp
        texttospeechwidget.cpp
        texttospeechconfigwidget.cpp
        texttospeechinterface.cpp
        texttospeechconfiginterface.cpp
        texttospeechconfigdialog.cpp
        texttospeechlanguagecombobox.cpp
        texttospeechactions.cpp
        texttospeech.h
        texttospeechwidget.h
        texttospeechconfigwidget.h
        texttospeechinterface.h
        texttospeechconfiginterface.h
        texttospeechconfigdialog.h
        texttospeechlanguagecombobox.h
        texttospeechactions.h
        texttospeechsliderwidget.h
        texttospeechsliderwidget.cpp
        texttospeechutil.h
        texttospeechutil.cpp
        texttospeechcontainerwidget.h
        texttospeechcontainerwidget.cpp
        texttospeechvoicecombobox.h
        texttospeechvoicecombobox.cpp
)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        KF6TextEditTextToSpeech
        PRIVATE
            <QObject>
            <QDebug>
            <QStringList>
            <QString>
    )
endif()

target_link_libraries(
    KF6TextEditTextToSpeech
    PUBLIC
        Qt::TextToSpeech
    PRIVATE
        KF6::ConfigCore
        KF6::ConfigGui
        KF6::WidgetsAddons
        KF6::I18n
)

ecm_qt_declare_logging_category(KF6TextEditTextToSpeech HEADER textedittexttospeech_debug.h
    IDENTIFIER TEXTEDITTEXTTOSPEECH_LOG
    CATEGORY_NAME org.kde.kf.textedittexttospeech
    OLD_CATEGORY_NAMES org.kde.kf6.textedittexttospeech
    DESCRIPTION "KF6 (textedit text to speech)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextEditTextToSpeech
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextEditTextToSpeech BASE_NAME textedittexttospeech)

target_include_directories(
    KF6TextEditTextToSpeech
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech;>"
)

target_link_libraries(KF6TextEditTextToSpeech PRIVATE KF6::I18n)
target_link_libraries(KF6TextEditTextToSpeech PRIVATE Qt6::Core)

set_target_properties(
    KF6TextEditTextToSpeech
    PROPERTIES
        VERSION
            ${TEXTEDITTEXTTOSPEECH_VERSION}
        SOVERSION
            ${TEXTEDITTEXTTOSPEECH_SOVERSION}
        EXPORT_NAME
            TextEditTextToSpeech
)

install(TARGETS KF6TextEditTextToSpeech EXPORT KF6TextEditTextToSpeechTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

ecm_generate_headers(TextEdit_CamelCasetexttospeechs_HEADERS
    HEADER_NAMES
    TextToSpeech
    TextToSpeechActions
    TextToSpeechInterface
    TextToSpeechWidget
    TextToSpeechConfigWidget
    TextToSpeechConfigDialog
    TextToSpeechContainerWidget
    REQUIRED_HEADERS TextEdit_texttospeechs_HEADERS
    PREFIX TextEditTextToSpeech
)

install(
    FILES
        ${TextEdit_texttospeechs_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech/textedittexttospeech
    COMPONENT Devel
)
install(
    FILES
        ${TextEdit_CamelCasetexttospeechs_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech/TextEditTextToSpeech/
    COMPONENT Devel
)
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextEditTextToSpeech_QCH
        FILE KF6TextEditTextToSpeechQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextEditTextToSpeechQchTargets.cmake\")")
endif()

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextEditTextToSpeech_QCH
        NAME TextEditTextToSpeech
        BASE_NAME KF6TextEditTextToSpeech
        VERSION ${TEXTEDITTEXTTOSPEECH_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${TextEdit_texttospeechs_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTEDITTEXTTOSPEECH_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextEditTextToSpeechConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEditTextToSpeechConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEditTextToSpeechConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextEditTextToSpeechConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextEditTextToSpeechTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextEditTextToSpeechTargets.cmake
    NAMESPACE KF6::
)
