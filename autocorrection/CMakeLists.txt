# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5TextAutoCorrection")


configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5TextAutoCorrectionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextAutoCorrectionConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5TextAutoCorrectionConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextAutoCorrectionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextAutoCorrectionConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

add_subdirectory(src)

if (BUILD_QCH)
    ecm_add_qch(
        KF5TextAutoCorrection_QCH
        NAME KF5TextAutoCorrection
        BASE_NAME KF5TextAutoCorrection
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommon_autocorrection_HEADERS}
        ${PimCommon_autocorrectionwidgets_HEADERS}
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONAUTOCORRECTION_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
    ecm_install_qch_export(
        TARGETS KF5TextAutoCorrection_QCH
        FILE KF5TextAutoCorrectionQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5TextAutoCorrectionQchTargets.cmake\")")
endif()
