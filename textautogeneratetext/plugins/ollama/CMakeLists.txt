# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(textautogenerateollama)
kconfig_add_kcfg_files(textautogenerateollama GENERATE_MOC ollamasettings.kcfgc)
ecm_qt_declare_logging_category(textautogenerateollama
    HEADER autogeneratetext_ollama_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMA_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollama
    DESCRIPTION "autogenerate text ollama (lib)"
    EXPORT KTEXTADDONS
)

target_sources(textautogenerateollama PRIVATE
    ollamaconfigurewidget.h
    ollamaconfigurewidget.cpp

    ollamaconfiguredialog.h
    ollamaconfiguredialog.cpp

    ollamautils.h
    ollamautils.cpp

    ollamamanager.h
    ollamamanager.cpp
    ollamacomboboxwidget.h
    ollamacomboboxwidget.cpp

    ollamareply.h
    ollamareply.cpp

    textautogenerateollama_private_export.h

    modelsmanager/ollamamodelavailableinfo.cpp
    modelsmanager/ollamamodelavailableinfo.h

    modelsmanager/ollamamodelsavalableinfos.h
    modelsmanager/ollamamodelsavalableinfos.cpp

    modelsmanager/ollamamodelavailablewidget.h
    modelsmanager/ollamamodelavailablewidget.cpp

    modelsmanager/ollamamodelavailabledialog.h
    modelsmanager/ollamamodelavailabledialog.cpp

    modelsmanager/ollamamodelavailablesearchwidget.h
    modelsmanager/ollamamodelavailablesearchwidget.cpp

    modelsmanager/ollamamodelavailableinfowidget.h
    modelsmanager/ollamamodelavailableinfowidget.cpp
    modelsmanager/ollamamodelavailableinfosmodel.h
    modelsmanager/ollamamodelavailableinfosmodel.cpp
    modelsmanager/ollamamodelavailableinfossortproxymodel.h
    modelsmanager/ollamamodelavailableinfossortproxymodel.cpp

    modelsmanager/ollamamodelavailableinfosdelegate.h
    modelsmanager/ollamamodelavailableinfosdelegate.cpp

    modelsmanager/ollamamodelavailableinfosmanager.h
    modelsmanager/ollamamodelavailableinfosmanager.cpp

    modelsmanager/ollamamodelavailablelistview.h
    modelsmanager/ollamamodelavailablelistview.cpp

    modelsmanager/ollamamodelsmanager.qrc

    modelsmanager/ollamamodelutils.h
    modelsmanager/ollamamodelutils.cpp

    modelsmanager/ollamamodelinfosdelegateutils.h
    modelsmanager/ollamamodelinfosdelegateutils.cpp

    modelsmanager/ollamamodelsinfoscategoriescombobox.h
    modelsmanager/ollamamodelsinfoscategoriescombobox.cpp

    modelsmanager/ollamamodeldownloadwidget.h
    modelsmanager/ollamamodeldownloadwidget.cpp

    modelsmanager/ollamamodeldownloadprogresswidget.h
    modelsmanager/ollamamodeldownloadprogresswidget.cpp

    modelsmanager/ollamamodelcategoriesmodel.cpp
    modelsmanager/ollamamodelcategoriesmodel.h

    modelsmanager/ollamamodelinstalledinfo.h
    modelsmanager/ollamamodelinstalledinfo.cpp

    modelsmanager/ollamamodelinstalledinfosmodel.cpp
    modelsmanager/ollamamodelinstalledinfosmodel.h

    modelsmanager/ollamamodelinstalledlistview.cpp
    modelsmanager/ollamamodelinstalledlistview.h

    modelsmanager/ollamamodelinstalledwidget.h
    modelsmanager/ollamamodelinstalledwidget.cpp

    modelsmanager/ollamamodelinstalledinfosdelegate.cpp
    modelsmanager/ollamamodelinstalledinfosdelegate.h

    modelsmanager/ollamamodelsearchlineedit.h
    modelsmanager/ollamamodelsearchlineedit.cpp

    modelsmanager/ollamamodeldownloadfromnamedialog.h
    modelsmanager/ollamamodeldownloadfromnamedialog.cpp

    modelsmanager/ollamamodeldownloadfromnamewidget.h
    modelsmanager/ollamamodeldownloadfromnamewidget.cpp

    modelsmanager/ollamamodelinstalledinfowidget.h
    modelsmanager/ollamamodelinstalledinfowidget.cpp

    modelsmanager/ollamamodelflowlayout.h
    modelsmanager/ollamamodelflowlayout.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(textautogenerateollama PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(textautogenerateollama BASE_NAME textautogenerateollama)

target_link_libraries(textautogenerateollama
    PUBLIC
    KF6::TextAutoGenerateText
    PRIVATE
    KF6::I18n
    KF6::ConfigGui
    KF6::CoreAddons
    KF6::WidgetsAddons
)
target_link_libraries(textautogenerateollama PRIVATE Qt6::Widgets)
set_target_properties(textautogenerateollama PROPERTIES
    VERSION ${TEXTAUTOGENERATETEXT_VERSION}
    SOVERSION ${TEXTAUTOGENERATETEXT_SOVERSION}
    EXPORT_NAME TextAutoGenerateText
)


install(TARGETS textautogenerateollama ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

#####

add_library(autogeneratetext_ollama MODULE)

ecm_qt_declare_logging_category(autogeneratetext_ollama
    HEADER autogeneratetext_ollama_plugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMA_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollama_plugin
    DESCRIPTION "autogenerate text ollama (plugin)"
    EXPORT KTEXTADDONS
)

target_sources(autogeneratetext_ollama PRIVATE
    ollamaclient.h
    ollamaclient.cpp
    ollamaplugin.h
    ollamaplugin.cpp

)

target_link_libraries(autogeneratetext_ollama
    PRIVATE
    textautogenerateollama
    KF6::ConfigGui
    KF6::CoreAddons
    KF6::I18n
    KF6::WidgetsAddons
)
install(TARGETS autogeneratetext_ollama  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
