# SPDX-FileCopyrightText: 2024 Joshua Goins <josh@redstrate.com>
# SPDX-License-Identifier: BSD-3-Clause

ecm_add_qml_module(ktextaddonsquickplugin URI "org.kde.textaddons.emoticons" VERSION 1.0 GENERATE_PLUGIN_SOURCE)

target_sources(ktextaddonsquickplugin PRIVATE types.h)

target_link_libraries(
    ktextaddonsquickplugin
    PRIVATE
        Qt::Qml
        KF6::TextEmoticonsCore
)

ecm_finalize_qml_module(ktextaddonsquickplugin)
