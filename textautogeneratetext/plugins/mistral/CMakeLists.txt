# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_library(autogeneratetext_mistral MODULE)

ecm_qt_declare_logging_category(autogeneratetext_mistral
    HEADER autogeneratetext_mistral_debug.h
    IDENTIFIER AUTOGENERATETEXT_MISTRAL_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mistral
    DESCRIPTION "autogenerate text mistral"
    EXPORT KTEXTADDONS
)
target_sources(autogeneratetext_mistral PRIVATE
    mistralclient.h
    mistralclient.cpp
    mistralplugin.h
    mistralplugin.cpp

    mistralconfiguredialog.h
    mistralconfiguredialog.cpp
    mistralconfigurewidget.h
    mistralconfigurewidget.cpp
)

target_link_libraries(autogeneratetext_mistral
    PRIVATE
    KF6::TextAutoGenerateText
    KF6::I18n
    KF6::ConfigGui
    KF6::WidgetsAddons
    qt6keychain
)

install(TARGETS autogeneratetext_mistral  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/)
