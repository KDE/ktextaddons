# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
add_library(textautogenerateollamacommon)
ecm_qt_declare_logging_category(textautogenerateollamacommon
    HEADER autogeneratetext_ollamacommon_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMACOMMON_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollamacommon
    DESCRIPTION "autogenerate text ollamacommon (lib)"
    EXPORT KTEXTADDONS
)

target_sources(
    textautogenerateollamacommon
    PRIVATE
        ollamacommonutils.h
        ollamacommonutils.cpp
        ollamacommonreply.h
        ollamacommonreply.cpp
        ollamacommoncomboboxwidget.cpp
        ollamacommoncomboboxwidget.h
        ollamacommonshowmodelinfobutton.cpp
        ollamacommonshowmodelinfobutton.h
        ollamacommonmodelavailableinfosmanager.h
        ollamacommonmodelavailableinfosmanager.cpp
        ollamacommonmodelavailableinfo.cpp
        ollamacommonmodelavailableinfo.h
        ollamacommonmodelutils.h
        ollamacommonmodelutils.cpp
        ollamacommonmodelsavalableinfos.cpp
        ollamacommonmodelsavalableinfos.h
        ollamacommonmodelavailablewidget.h
        ollamacommonmodelavailablewidget.cpp
        ollamacommonmodelsinfoscategoriescombobox.cpp
        ollamacommonmodelsinfoscategoriescombobox.h
        ollamacommonmodelcategoriesmodel.cpp
        ollamacommonmodelcategoriesmodel.h
        ollamacommonmodelavailableinfossortproxymodel.cpp
        ollamacommonmodelavailableinfossortproxymodel.h
        ollamacommonmodelavailableinfosmodel.h
        ollamacommonmodelavailableinfosmodel.cpp
        ollamacommonmodelavailableinfosdelegate.h
        ollamacommonmodelavailableinfosdelegate.cpp
        ollamacommonmodelinfosdelegateutils.cpp
        ollamacommonmodelinfosdelegateutils.h
        ollamacommonoverrideparameterswidget.h
        ollamacommonoverrideparameterswidget.cpp
        ollamacommonsettings.cpp
        ollamacommonsettings.h
        ollamacommonkeepaliveparameterswidget.h
        ollamacommonkeepaliveparameterswidget.cpp
        ollamacommonkeepaliveparameterscombobox.h
        ollamacommonkeepaliveparameterscombobox.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        textautogenerateollamacommon
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(textautogenerateollamacommon BASE_NAME textautogenerateollamacommon)

target_link_libraries(textautogenerateollamacommon PUBLIC KF6::TextAutoGenerateText)

set_target_properties(
    textautogenerateollamacommon
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXT_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXT_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateText
)

install(
    TARGETS
        textautogenerateollamacommon
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
