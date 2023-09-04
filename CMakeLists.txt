# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(KTEXTADDONS_CURRENT_VERSION "1.4.80")
project(KTextAddons VERSION ${KTEXTADDONS_CURRENT_VERSION})

include(FeatureSummary)
set(KF_MIN_VERSION "5.105.0")
find_package(ECM ${KF_MIN_VERSION}  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://invent.kde.org/frameworks/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

set(REQUIRED_QT_VERSION 5.15.2)


include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEGitCommitHooks)

include(ECMGenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMAddQch)
include(ECMAddTests)
include(ECMDeprecationSettings)
include(CMakeDependentOption)
include(ECMQtDeclareLoggingCategory)
include(ECMGeneratePriFile)

if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.5.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets Core Network)

find_package(KF${KF_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    ConfigWidgets
    Archive
    XmlGui
    CoreAddons
    Sonnet
    KIO
    SyntaxHighlighting
)

option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")

find_package(Qt${QT_MAJOR_VERSION}Keychain CONFIG)
set_package_properties(Qt${QT_MAJOR_VERSION}Keychain PROPERTIES
                                   DESCRIPTION "Provides support for secure credentials storage"
                                   URL "https://github.com/frankosterfeld/qtkeychain"
                                   TYPE REQUIRED)

if(BUILD_TESTING)
    find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Test)
    add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

option(BERGAMOT_TRANSLATOR_PLUGIN "Build bergamot translator plugin" OFF)
add_feature_info(BERGAMOT_TRANSLATOR_PLUGIN ${BERGAMOT_TRANSLATOR_PLUGIN} "Bergamot translator plugin (local translation)")

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")


ecm_set_disabled_deprecation_versions(
    QT 6.5.0
    KF 5.240.0
)

add_subdirectory(textaddonswidgets)
add_subdirectory(textautocorrection)
add_subdirectory(textgrammarcheck)
add_subdirectory(texttranslator)
add_subdirectory(textemoticons)
add_subdirectory(textutils)
add_subdirectory(textcustomeditor)

find_package(Qt${QT_MAJOR_VERSION}TextToSpeech ${QT_REQUIRED_VERSION} CONFIG)
set_package_properties(Qt${QT_MAJOR_VERSION}TextToSpeech PROPERTIES DESCRIPTION
    "Add support for text to speech"
    TYPE OPTIONAL
)
if(TARGET Qt${QT_MAJOR_VERSION}::TextToSpeech)
    add_definitions(-DHAVE_TEXT_TO_SPEECH_SUPPORT)
    set(TEXTEDIT_TEXT_TO_SPEECH TRUE)
    add_subdirectory(textedittexttospeech)
endif()

ecm_qt_install_logging_categories(
        EXPORT KTEXTADDONS
        FILE ktextaddons.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
