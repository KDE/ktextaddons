# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoCorrectionCore")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTIONCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionCoreConfigVersion.cmake"
    SOVERSION 1
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAutoCorrectionTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoCorrectionCoreTargets.cmake
    NAMESPACE KF6::
)

kconfig_add_kcfg_files(textautocorrection_settings_SRCS
    settings/textautocorrectionsetting_base.kcfgc
)

add_library(KF6TextAutoCorrectionCore)
add_library(KF6::TextAutoCorrectionCore ALIAS KF6TextAutoCorrectionCore)
ecm_qt_declare_logging_category(KF6TextAutoCorrectionCore HEADER textautocorrection_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_LOG
        CATEGORY_NAME org.kde.kf.textautocorrection
        OLD_CATEGORY_NAMES org.kde.kf6.textautocorrection
	DESCRIPTION "KF6 (text AutoCorrection)"
	EXPORT KTEXTADDONS
)

ecm_qt_declare_logging_category(KF6TextAutoCorrectionCore HEADER textautocorrectionautocorrect_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_AUTOCORRECT_LOG
        CATEGORY_NAME org.kde.kf.textautocorrection.autocorrect
        OLD_CATEGORY_NAMES org.kde.kf6.textautocorrection.autocorrect
	DESCRIPTION "KF6 (AutoCorrection autocorrect text)"
	EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoCorrectionCore
    PRIVATE
        ${textautocorrection_settings_SRCS}
        autocorrection.cpp
        autocorrection.h
        autocorrectionutils.h
        autocorrectionutils.cpp
        autocorrectionsettings.h
        autocorrectionsettings.cpp
        import/importlibreofficeautocorrection.cpp
        import/importkmailautocorrection.cpp
        import/importabstractautocorrection.cpp
        import/importkmailautocorrection.h
        import/importlibreofficeautocorrection.h
        import/importabstractautocorrection.h
        export/exportabstractautocorrection.h
        export/exportabstractautocorrection.cpp
        export/exportlibreofficeautocorrection.h
        export/exportlibreofficeautocorrection.cpp
        settings/textautocorrectionsettings.h
        settings/textautocorrectionsettings.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAutoCorrectionCore
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextAutoCorrectionCore BASE_NAME textautocorrectioncore)

target_link_libraries(
    KF6TextAutoCorrectionCore
    PUBLIC
        Qt::Gui
        KF6::ConfigGui
    PRIVATE
        KF6::I18n
        KF6::Archive
        KF6::ColorScheme
        Qt::Xml
        Qt::Widgets
)

target_include_directories(
    KF6TextAutoCorrectionCore
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/>"
)

set_target_properties(
    KF6TextAutoCorrectionCore
    PROPERTIES
        VERSION
            ${TEXTAUTOCORRECTIONCORE_VERSION}
        SOVERSION
            ${TEXTAUTOCORRECTIONCORE_SOVERSION}
        EXPORT_NAME
            TextAutoCorrectionCore
)

install(TARGETS KF6TextAutoCorrectionCore EXPORT KF6TextAutoCorrectionTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

ecm_generate_headers(TextAutoCorrectionCore_Camelcaseautocorrection_HEADERS
    HEADER_NAMES
    AutoCorrection
    AutoCorrectionSettings
    AutoCorrectionUtils

    REQUIRED_HEADERS TextAutoCorrectionCore_autocorrection_HEADERS
    PREFIX TextAutoCorrectionCore
)

ecm_generate_headers(TextAutoCorrectionCore_Camelcaseautocorrectionimport_HEADERS
    HEADER_NAMES
    ImportLibreOfficeAutocorrection
    ImportKMailAutocorrection
    ImportAbstractAutocorrection

    REQUIRED_HEADERS TextAutoCorrectionCore_autocorrectionimport_HEADERS
    PREFIX TextAutoCorrectionCore
    RELATIVE import
)

ecm_generate_headers(TextAutoCorrectionCore_Camelcasesettings_HEADERS
    HEADER_NAMES
    TextAutoCorrectionSettings
    REQUIRED_HEADERS TextAutoCorrectionCore_settings_HEADERS
    PREFIX TextAutoCorrectionCore
    RELATIVE settings
)

install(
    FILES
        ${TextAutoCorrectionCore_Camelcaseautocorrection_HEADERS}
        ${TextAutoCorrectionCore_Camelcaseautocorrectionimport_HEADERS}
        ${TextAutoCorrectionCore_Camelcasesettings_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/TextAutoCorrectionCore
    COMPONENT Devel
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionsetting_base.h
        ${TextAutoCorrectionCore_autocorrection_HEADERS}
        ${TextAutoCorrectionCore_settings_HEADERS}
        ${TextAutoCorrectionCore_autocorrectionimport_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/textautocorrectioncore
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextAutoCorrectionCore_QCH
        NAME KF6TextAutoCorrectionCore
        BASE_NAME KF6TextAutoCorrectionCore
	VERSION ${TEXTAUTOCORRECTIONCORE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutoCorrectionCore_autocorrection_HEADERS}
        ${TextAutoCorrectionCore_settings_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOCORRECTIONCORE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextAutoCorrectionCore_QCH
        FILE KF6TextAutoCorrectionQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextAutoCorrectionQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoCorrectionCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionCoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/
    COMPONENT Devel
)
