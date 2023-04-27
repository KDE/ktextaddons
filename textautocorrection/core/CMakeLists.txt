# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none


set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionCore")



ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTIONCORE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionCoreConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF${KF_MAJOR_VERSION}TextAutoCorrectionCoreTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

kconfig_add_kcfg_files(textautocorrection_settings_SRCS
    settings/textautocorrectionsetting_base.kcfgc
    )

add_library(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore )
add_library(KF${KF_MAJOR_VERSION}::TextAutoCorrectionCore ALIAS KF${KF_MAJOR_VERSION}TextAutoCorrectionCore)
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore HEADER textautocorrection_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textautocorrection
	DESCRIPTION "KF${KF_MAJOR_VERSION} (text AutoCorrection)"
	EXPORT KTEXTADDONS
    )

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore HEADER textautocorrectionautocorrect_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_AUTOCORRECT_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textautocorrection.autocorrect
	DESCRIPTION "KF${KF_MAJOR_VERSION} (AutoCorrection autocorrect text)"
	EXPORT KTEXTADDONS
    )

target_sources(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore PRIVATE
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

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore BASE_NAME textautocorrectioncore)


target_link_libraries(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore
    PUBLIC
    Qt::Gui
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Archive
    Qt::Xml
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrectionCore PROPERTIES
    VERSION ${TEXTAUTOCORRECTIONCORE_VERSION}
    SOVERSION ${TEXTAUTOCORRECTIONCORE_SOVERSION}
    EXPORT_NAME TextAutoCorrectionCore
    )

install(TARGETS
    KF${KF_MAJOR_VERSION}TextAutoCorrectionCore
    EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

if (BUILD_TESTING)
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

ecm_generate_pri_file(BASE_NAME TextAutoCorrectionCore
    LIB_NAME KF${KF_MAJOR_VERSION}TextAutoCorrectionCore
    DEPS "KConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore
    )


install(FILES
    ${TextAutoCorrectionCore_Camelcaseautocorrection_HEADERS}
    ${TextAutoCorrectionCore_Camelcaseautocorrectionimport_HEADERS}
    ${TextAutoCorrectionCore_Camelcasesettings_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/TextAutoCorrectionCore
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_export.h
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionsetting_base.h
    ${TextAutoCorrectionCore_autocorrection_HEADERS}
    ${TextAutoCorrectionCore_settings_HEADERS}
    ${TextAutoCorrectionCore_autocorrectionimport_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/textautocorrectioncore
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextAutoCorrectionCore_QCH
        NAME KF${KF_MAJOR_VERSION}TextAutoCorrectionCore
        BASE_NAME KF${KF_MAJOR_VERSION}TextAutoCorrectionCore
	VERSION ${TEXTAUTOCORRECTIONCORE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutoCorrectionCore_autocorrection_HEADERS}
        ${TextAutoCorrectionCore_settings_HEADERS}
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOCORRECTIONCORE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextAutoCorrectionCore_QCH
        FILE KF${KF_MAJOR_VERSION}TextAutoCorrectionQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionQchTargets.cmake\")")
endif()

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoCorrectionCoreConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionCoreConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectioncore_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionCore/ COMPONENT Devel
    )
