# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextaddonswidgets\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgets")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTADDONSWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgetsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF${KF_MAJOR_VERSION}TextAddonsWidgets)
add_library(KF${KF_MAJOR_VERSION}::TextAddonsWidgets ALIAS KF${KF_MAJOR_VERSION}TextAddonsWidgets)

target_sources(KF${KF_MAJOR_VERSION}TextAddonsWidgets PRIVATE
    lineeditcatchreturnkey.h
    lineeditcatchreturnkey.cpp
)

target_link_libraries(KF${KF_MAJOR_VERSION}TextAddonsWidgets
    PRIVATE
    Qt::Widgets
)

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAddonsWidgets HEADER TextAddonsWidgets_debug.h
    IDENTIFIER TEXTADDONSWIDGETS_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textaddonswidgets
    DESCRIPTION "KF${KF_MAJOR_VERSION} (textaddons widgets)" EXPORT KTEXTADDONS)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextAddonsWidgets PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextAddonsWidgets BASE_NAME TextAddonsWidgets)

target_include_directories(KF${KF_MAJOR_VERSION}TextAddonsWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets;>")


target_link_libraries(KF${KF_MAJOR_VERSION}TextAddonsWidgets
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
)

set_target_properties(KF${KF_MAJOR_VERSION}TextAddonsWidgets PROPERTIES
    VERSION ${TEXTADDONSWIDGETS_VERSION}
    SOVERSION ${TEXTADDONSWIDGETS_SOVERSION}
    EXPORT_NAME TextAddonsWidgets
)

install(TARGETS KF${KF_MAJOR_VERSION}TextAddonsWidgets EXPORT KF${KF_MAJOR_VERSION}TextAddonsWidgetsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

#if(BUILD_TESTING)
#    add_subdirectory(autotests)
#    add_subdirectory(tests)
#endif()

ecm_generate_headers(TextAddonsWidgets_CamelCase_HEADERS
    HEADER_NAMES
    LineEditCatchReturnKey
    REQUIRED_HEADERS TextAddonsWidgets_HEADERS
    PREFIX TextAddonsWidgets
)

install(FILES
    ${TextAddonsWidgets_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets/textaddonswidgets
    COMPONENT Devel
)
install(FILES
    ${TextAddonsWidgets_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets/TextAddonsWidgets/
    COMPONENT Devel
)
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextAddonsWidgets_QCH
        FILE KF${KF_MAJOR_VERSION}TextAddonsWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgetsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAddonsWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgetsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAddonsWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF${KF_MAJOR_VERSION}TextAddonsWidgetsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextAddonsWidgetsTargets.cmake
    NAMESPACE KF${KF_MAJOR_VERSION}::
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets
    COMPONENT Devel
)


ecm_generate_pri_file(BASE_NAME textaddonswidgets LIB_NAME TextAddonsWidgets DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR
    ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets/)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextAddonsWidgets_QCH
        NAME KF${KF_MAJOR_VERSION}TextAddonsWidgets
        BASE_NAME KF${KF_MAJOR_VERSION}TextAddonsWidgets
        VERSION ${TEXTADDONSWIDGETS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAddonsWidgets_HEADERS}
        LINK_QCHS
        Qt${QT_MAJOR_VERSION}Core_QCH
        Qt${QT_MAJOR_VERSION}Gui_QCH
        Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTADDONSWIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

