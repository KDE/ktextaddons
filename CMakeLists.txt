# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(KF_VERSION "5.102.0") # handled by release scripts
set(KF_DEP_VERSION "5.101.0") # handled by release scripts
set(KTEXTADDONS_CURRENT_VERSION "1.0.1")
#project(KTextAddons VERSION ${KF_VERSION})
project(KTextAddons VERSION ${KTEXTADDONS_CURRENT_VERSION})

include(FeatureSummary)
find_package(ECM 5.101.0  NO_MODULE)
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

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets Core Network)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    ConfigWidgets
    Archive
    XmlGui
    CoreAddons
)

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

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")


ecm_set_disabled_deprecation_versions(
    QT 5.15.2
    KF 5.102
)

add_subdirectory(autocorrection)
add_subdirectory(textgrammarcheck)
add_subdirectory(texttranslator)

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


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
