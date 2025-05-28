# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(KTEXTADDONS_CURRENT_VERSION "1.5.81")
project(KTextAddons VERSION ${KTEXTADDONS_CURRENT_VERSION})

set(QT_REQUIRED_VERSION "6.8.0")
set(KF_MIN_VERSION "6.11.0")
set(QT6KEYCHAIN_LIB_VERSION "0.14.2")
set(CMAKE_CXX_STANDARD 20)
include(FeatureSummary)
find_package(ECM ${KF_MIN_VERSION}  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://invent.kde.org/frameworks/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${ECM_MODULE_PATH})

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
include(ECMCheckOutboundLicense)

file(GLOB_RECURSE ALL_SOURCE_FILES
textaddonswidgets/*.cpp
textaddonswidgets/*.h
textedittexttospeech/*.cpp
textedittexttospeech/*.h
textspeechtotext/*.cpp
textspeechtotext/*.h
textautocorrection/*.cpp
textautocorrection/*.h
textemoticons/*.cpp
textemoticons/*.h
texttranslator/*.cpp
texttranslator/*.h
textcustomeditor/*.cpp
textcustomeditor/*.h
textgrammarcheck/*.cpp
textgrammarcheck/*.h
textutils/*.cpp
textutils/*.h
textautogeneratetext/*.h
textautogeneratetext/*.cpp
)
ecm_check_outbound_license(LICENSES GPL-2.0-only  FILES ${ALL_SOURCE_FILES})

option(BUILD_QUICK "Build with QtQuick support (experimental)" OFF)
if (BUILD_QUICK)
    include(ECMQmlModule)
endif ()

find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Core Network Xml Sql)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    ColorScheme
    Archive
    CoreAddons
    Sonnet
    SyntaxHighlighting
    WidgetsAddons
    TextWidgets
)
option(BUILD_KIO_SUPPORT "Build with KIO support" ON)
add_feature_info(KIO_SUPPORT ${BUILD_KIO_SUPPORT} "Build with KIO support")

if(${BUILD_KIO_SUPPORT})
    find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS KIO)
endif()

option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")

find_package(Qt6Keychain ${QT6KEYCHAIN_LIB_VERSION} CONFIG)
set_package_properties(Qt6Keychain PROPERTIES
                                   DESCRIPTION "Provides support for secure credentials storage"
                                   URL "https://github.com/frankosterfeld/qtkeychain"
                                   TYPE REQUIRED)

if(BUILD_TESTING)
    find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Test)
    add_definitions(-DBUILD_TESTING)
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if(USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

option(BERGAMOT_TRANSLATOR_PLUGIN "Build bergamot translator plugin" OFF)
add_feature_info(BERGAMOT_TRANSLATOR_PLUGIN ${BERGAMOT_TRANSLATOR_PLUGIN} "Bergamot translator plugin (local translation) (Experimental. Need to download bergamot source code first)")

option(SPEAK_TO_TEXT_VOSK_PLUGIN "Build vosk speak to text support" OFF)
add_feature_info(SPEAK_TO_TEXT_VOSK_PLUGIN ${SPEAK_TO_TEXT_VOSK_PLUGIN} "Vosk speak to text plugin (local text to speak) (Experimental)")

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

option(DISABLE_AUTOTEST_BROKEN_CI "Disable autotest broken on CI (work locally)" OFF)

add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
ecm_set_disabled_deprecation_versions(
    QT 6.9.0
    KF 6.14.0
)

if(BERGAMOT_TRANSLATOR_PLUGIN)
   find_package(slimt)
   set_package_properties(slimt PROPERTIES DESCRIPTION
       "Add local translation based on Bergamot"
       TYPE OPTIONAL
  )
endif()


add_subdirectory(textaddonswidgets)
add_subdirectory(textautocorrection)
add_subdirectory(textgrammarcheck)
add_subdirectory(texttranslator)
add_subdirectory(textemoticons)
add_subdirectory(textutils)
find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED MultimediaWidgets)
add_subdirectory(textspeechtotext)
add_subdirectory(textautogeneratetext)

find_package(Qt6TextToSpeech ${QT_REQUIRED_VERSION} CONFIG)
set_package_properties(Qt6TextToSpeech PROPERTIES DESCRIPTION
    "Add support for text to speech"
    TYPE OPTIONAL
)
if(TARGET Qt6::TextToSpeech)
    add_subdirectory(textedittexttospeech)
endif()

add_subdirectory(textcustomeditor)
ecm_qt_install_logging_categories(
        EXPORT KTEXTADDONS
        FILE ktextaddons.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
