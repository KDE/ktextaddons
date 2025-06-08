# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
include(ECMAddQtDesignerPlugin)
ecm_qtdesignerplugin_widget(TextTranslator::TranslatorWidget
    INCLUDE_FILE "TextTranslator/TranslatorWidget"
    TOOLTIP "A widget to make translate string"
    WHATSTHIS "A widget to make translate string."
    GROUP "Input (KF6)"
)

ecm_add_qtdesignerplugin(texttranslatorwidgets
	NAME TextTranslatorWidgets
    OUTPUT_NAME texttranslatorwidgets6
    WIDGETS
    TextTranslator::TranslatorWidget
    LINK_LIBRARIES
    KF6::TextTranslator
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
