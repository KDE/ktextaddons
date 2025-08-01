# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(grammarcommon)

target_sources(
    grammarcommon
    PRIVATE
        grammarerror.cpp
        grammarresulttextedit.cpp
        grammarresultwidget.cpp
        grammarerror.h
        grammarresulttextedit.h
        grammarresultwidget.h
        grammarresultutil.h
        grammarresultutil.cpp
)

ecm_qt_declare_logging_category(grammarcommon HEADER grammarcommon_debug.h IDENTIFIER LIBGRAMMARCOMMON_LOG CATEGORY_NAME org.kde.kf6.libgrammarcommon
    DESCRIPTION "KF6 (libgramalecte common)"
    EXPORT KTEXTADDONS
)

generate_export_header(grammarcommon BASE_NAME grammarcommon)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        grammarcommon
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()

target_link_libraries(grammarcommon KF6::I18n)

set_target_properties(
    grammarcommon
    PROPERTIES
        OUTPUT_NAME
            grammarcommon
        VERSION
            ${KDEPIMADDONS_LIB_VERSION}
        SOVERSION
            ${KDEPIMADDONS_LIB_SOVERSION}
)

install(
    TARGETS
        grammarcommon
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
