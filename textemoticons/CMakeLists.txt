# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextemoticons\")

add_subdirectory(core)
add_subdirectory(widgets)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextEmoticons")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTEMOTICONS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textemoticons_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEmoticonsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF${KF_MAJOR_VERSION}TextEmoticons)
add_library(KF${KF_MAJOR_VERSION}::TextEmoticons ALIAS KF${KF_MAJOR_VERSION}TextEmoticons)

target_sources(KF${KF_MAJOR_VERSION}TextEmoticons PRIVATE
)

target_link_libraries(KF${KF_MAJOR_VERSION}TextEmoticons
    PRIVATE
    Qt::Widgets
)

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextEmoticons HEADER TextEmoticons_debug.h
    IDENTIFIER TEXTEMOTICONS_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textemoticons
    DESCRIPTION "KF${KF_MAJOR_VERSION} (textaddons widgets)" EXPORT KTEXTADDONS)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextEmoticons PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextEmoticons BASE_NAME TextEmoticons)

target_include_directories(KF${KF_MAJOR_VERSION}TextEmoticons INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticons;>")


target_link_libraries(KF${KF_MAJOR_VERSION}TextEmoticons
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
)

set_target_properties(KF${KF_MAJOR_VERSION}TextEmoticons PROPERTIES
    VERSION ${TEXTEMOTICONS_VERSION}
    SOVERSION ${TEXTEMOTICONS_SOVERSION}
    EXPORT_NAME TextEmoticons
)

install(TARGETS KF${KF_MAJOR_VERSION}TextEmoticons EXPORT KF${KF_MAJOR_VERSION}TextEmoticonsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

#if(BUILD_TESTING)
#    add_subdirectory(autotests)
#    add_subdirectory(tests)
#endif()

#ecm_generate_headers(TextEmoticons_CamelCase_HEADERS
#    HEADER_NAMES
#    #LineEditCatchReturnKey
#    REQUIRED_HEADERS TextEmoticons_HEADERS
#    PREFIX TextEmoticons
#)

install(FILES
    ${TextEmoticons_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/textemoticons_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticons/textemoticons
    COMPONENT Devel
)
install(FILES
    ${TextEmoticons_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticons/TextEmoticons/
    COMPONENT Devel
)
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextEmoticons_QCH
        FILE KF${KF_MAJOR_VERSION}TextEmoticonsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextEmoticonsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextEmoticonsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEmoticonsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEmoticonsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextEmoticonsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF${KF_MAJOR_VERSION}TextEmoticonsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextEmoticonsTargets.cmake
    NAMESPACE KF${KF_MAJOR_VERSION}::
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textemoticons_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticons
    COMPONENT Devel
)


ecm_generate_pri_file(BASE_NAME textemoticons LIB_NAME TextEmoticons DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR
    ${KDE_INSTALL_INCLUDEDIR_KF}/TextEmoticons/)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

# Reactivate when we have headers
if (0)
if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextEmoticons_QCH
        NAME KF${KF_MAJOR_VERSION}TextEmoticons
        BASE_NAME KF${KF_MAJOR_VERSION}TextEmoticons
        VERSION ${TEXTEMOTICONS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextEmoticons_HEADERS}
        LINK_QCHS
        Qt${QT_MAJOR_VERSION}Core_QCH
        Qt${QT_MAJOR_VERSION}Gui_QCH
        Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTEMOTICONS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
endif()
