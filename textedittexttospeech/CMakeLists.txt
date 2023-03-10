# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextedittexttospeech\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeech")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTEDITTEXTTOSPEECH
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeechConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF${KF_MAJOR_VERSION}TextEditTextToSpeech)
add_library(KF${KF_MAJOR_VERSION}::TextEditTextToSpeech ALIAS KF${KF_MAJOR_VERSION}TextEditTextToSpeech)

if (TEXTEDIT_TEXT_TO_SPEECH)
    target_sources(KF${KF_MAJOR_VERSION}TextEditTextToSpeech PRIVATE
        texttospeech.cpp
        texttospeechwidget.cpp
        texttospeechconfigwidget.cpp
        texttospeechinterface.cpp
        abstracttexttospeechinterface.cpp
        abstracttexttospeechconfiginterface.cpp
        texttospeechconfiginterface.cpp
        texttospeechconfigdialog.cpp
        texttospeechlanguagecombobox.cpp
        texttospeechactions.cpp
        texttospeech.h
        texttospeechwidget.h
        texttospeechconfigwidget.h
        texttospeechinterface.h
        abstracttexttospeechinterface.h
        abstracttexttospeechconfiginterface.h
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
    )
endif()

if (TEXTEDIT_TEXT_TO_SPEECH)
    target_link_libraries(KF${KF_MAJOR_VERSION}TextEditTextToSpeech
        PRIVATE
        KF${KF_MAJOR_VERSION}::WidgetsAddons
        KF${KF_MAJOR_VERSION}::ConfigWidgets
        KF${KF_MAJOR_VERSION}::XmlGui
        KF${KF_MAJOR_VERSION}::I18n
        Qt::TextToSpeech
        )
endif()

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextEditTextToSpeech HEADER textedittexttospeech_debug.h
    IDENTIFIER TEXTEDITTEXTTOSPEECH_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textedittexttospeech
        DESCRIPTION "KF${KF_MAJOR_VERSION} (textedit text to speech)" EXPORT KTEXTADDONS)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextEditTextToSpeech PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextEditTextToSpeech BASE_NAME textedittexttospeech)

target_include_directories(KF${KF_MAJOR_VERSION}TextEditTextToSpeech INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech;>")


target_link_libraries(KF${KF_MAJOR_VERSION}TextEditTextToSpeech
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    )

set_target_properties(KF${KF_MAJOR_VERSION}TextEditTextToSpeech PROPERTIES
    VERSION ${TEXTEDITTEXTTOSPEECH_VERSION}
    SOVERSION ${TEXTEDITTEXTTOSPEECH_SOVERSION}
    EXPORT_NAME TextEditTextToSpeech
    )

install(TARGETS KF${KF_MAJOR_VERSION}TextEditTextToSpeech EXPORT KF${KF_MAJOR_VERSION}TextEditTextToSpeechTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

if (TEXTEDIT_TEXT_TO_SPEECH)
    if(BUILD_TESTING)
        add_subdirectory(autotests)
        add_subdirectory(tests)
    endif()
endif()

if (TEXTEDIT_TEXT_TO_SPEECH)
    ecm_generate_headers(TextEdit_CamelCasetexttospeechs_HEADERS
        HEADER_NAMES
        TextToSpeech
        TextToSpeechActions
        TextToSpeechInterface
        TextToSpeechWidget
        TextToSpeechConfigWidget
        TextToSpeechConfigDialog
        AbstractTextToSpeechInterface
        AbstractTextToSpeechConfigInterface
        TextToSpeechContainerWidget
        REQUIRED_HEADERS TextEdit_texttospeechs_HEADERS
        PREFIX TextEditTextToSpeech
    )
endif()

if (TEXTEDIT_TEXT_TO_SPEECH)
    install(FILES
        ${TextEdit_texttospeechs_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_export.h
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech/textedittexttospeech
        COMPONENT Devel
        )
    install(FILES
        ${TextEdit_CamelCasetexttospeechs_HEADERS}
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech/TextEditTextToSpeech/
        COMPONENT Devel
        )
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextEditTextToSpeechConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeechConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeechConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeechConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextEditTextToSpeechTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextEditTextToSpeechTargets.cmake
    NAMESPACE KF${KF_MAJOR_VERSION}::
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textedittexttospeech_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech
    COMPONENT Devel
    )


ecm_generate_pri_file(BASE_NAME TextEditTextToSpeech LIB_NAME TextEditTextToSpeech DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR
    ${KDE_INSTALL_INCLUDEDIR_KF}/TextEditTextToSpeech/)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextEditTextToSpeech_QCH
        NAME TextEditTextToSpeech
        BASE_NAME KF${KF_MAJOR_VERSION}TextEditTextToSpeech
        VERSION ${TEXTEDITTEXTTOSPEECH_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${TextEdit_texttospeechs_HEADERS}
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTEDITTEXTTOSPEECH_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextEditTextToSpeech_QCH
        FILE KF${KF_MAJOR_VERSION}TextEditTextToSpeechQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextEditTextToSpeechQchTargets.cmake\")")
endif()
