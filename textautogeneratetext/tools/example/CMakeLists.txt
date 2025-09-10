# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(textautogeneratetext_exampletoolplugin INSTALL_NAMESPACE autogeneratetext/toolplugins)

target_sources(
    textautogeneratetext_exampletoolplugin
    PRIVATE
        exampletexttoolplugin.h
        exampletexttoolplugin.cpp
)
target_link_libraries(textautogeneratetext_exampletoolplugin KF6::TextAutoGenerateText)
