# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>


add_library(autogeneratetext_ollama MODULE)

kconfig_add_kcfg_files(autogeneratetext_ollama GENERATE_MOC ollamasettings.kcfgc)

ecm_qt_declare_logging_category(autogeneratetext_ollama
    HEADER autogeneratetext_ollama_debug.h
    IDENTIFIER AUTOGENERATETEXT_OLLAMA_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.ollama
    DESCRIPTION "autogenerate text ollama"
    EXPORT KTEXTADDONS
)
target_sources(autogeneratetext_ollama PRIVATE
    ollamaclient.h
    ollamaclient.cpp
    ollamaplugin.h
    ollamaplugin.cpp

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

    modelsmanager/ollamamodelinfo.cpp
    modelsmanager/ollamamodelinfo.h

    modelsmanager/ollamamodelsinfos.h
    modelsmanager/ollamamodelsinfos.cpp

    modelsmanager/ollamamodelwidget.h
    modelsmanager/ollamamodelwidget.cpp

    modelsmanager/ollamamodeldialog.h
    modelsmanager/ollamamodeldialog.cpp

    modelsmanager/ollamamodelsearchwidget.h
    modelsmanager/ollamamodelsearchwidget.cpp

    modelsmanager/ollamamodelinfowidget.h
    modelsmanager/ollamamodelinfowidget.cpp
    modelsmanager/ollamamodelinfosmodel.h
    modelsmanager/ollamamodelinfosmodel.cpp
    modelsmanager/ollamamodelinfossortproxymodel.h
    modelsmanager/ollamamodelinfossortproxymodel.cpp

    modelsmanager/ollamamodelinfosdelegate.h
    modelsmanager/ollamamodelinfosdelegate.cpp
)

target_link_libraries(autogeneratetext_ollama PRIVATE KF6::TextAutoGenerateText KF6::I18n KF6::ConfigGui KF6::CoreAddons KF6::WidgetsAddons)

install(TARGETS autogeneratetext_ollama  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
