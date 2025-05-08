# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(autogeneratetext_openai MODULE)

ecm_qt_declare_logging_category(autogeneratetext_openai
    HEADER autogeneratetext_openai_debug.h
    IDENTIFIER AUTOGENERATETEXT_MISTRAL_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.openai
    DESCRIPTION "autogenerate text openai"
    EXPORT KTEXTADDONS
)
target_sources(autogeneratetext_openai PRIVATE
    openaiclient.h
    openaiclient.cpp
    openaiplugin.h
    openaiplugin.cpp

    openaiconfiguredialog.h
    openaiconfiguredialog.cpp
    openaiconfigurewidget.h
    openaiconfigurewidget.cpp
)

target_link_libraries(autogeneratetext_openai PRIVATE KF6::TextAutoGenerateText KF6::I18n KF6::ConfigGui)

install(TARGETS autogeneratetext_openai  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)
