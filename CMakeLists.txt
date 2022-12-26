# SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(KF_VERSION "5.102.0") # handled by release scripts
set(KF_DEP_VERSION "5.101.0") # handled by release scripts
project(KTEXTADDONS VERSION ${KF_VERSION})

include(FeatureSummary)
find_package(ECM 5.101.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
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

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets Core)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    ConfigWidgets
)

if(BUILD_TESTING)
    find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Test)
    add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

add_definitions(-DTRANSLATION_DOMAIN=\"ktextaddons\")

ecm_set_disabled_deprecation_versions(
    QT 5.15.2
    KF 5.101
)

add_subdirectory(autocorrection)

ki18n_install(po)
# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5TextAddons")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5TextAddons_QCH
        FILE KF5TextWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5TextAddonsQchTargets.cmake\")")
endif()

#configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KF5TextAddonsConfig.cmake.in"
#	"${CMAKE_CURRENT_BINARY_DIR}/KF5TextAddonsConfig.cmake"
#                              INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
#                             )

install(EXPORT KF5TextAddonssTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5TextAddonsTargets.cmake NAMESPACE KF5:: )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KF5TextAddonsConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/KF5TextAddonsConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
       )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ktextaddons_version.h
	DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KTextAddons COMPONENT Devel
       )


kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
