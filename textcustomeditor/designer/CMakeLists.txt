# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include(ECMAddQtDesignerPlugin)
ecm_qtdesignerplugin_widget(TextCustomEditor::RichTextEditorWidget
    INCLUDE_FILE "TextCustomEditor/RichTextEditorWidget"
    TOOLTIP "A RichTextEditor (KDE-PIM)"
    WHATSTHIS "A RichTextEditor."
    GROUP "Input (KDE-PIM)"
)

ecm_qtdesignerplugin_widget(TextCustomEditor::PlainTextEditorWidget
    INCLUDE_FILE "TextCustomEditor/PlainTextEditorWidget"
    TOOLTIP "A PlainTextEditor (KDE-PIM)"
    WHATSTHIS "A PlainTextEditor."
    GROUP "Input (KDE-PIM)"
)

ecm_add_qtdesignerplugin(textcustomeditor
    NAME TextCustomEditor
    OUTPUT_NAME textcustomeditor
    WIDGETS
    TextCustomEditor::RichTextEditorWidget
    TextCustomEditor::PlainTextEditorWidget
    LINK_LIBRARIES
    KF6::TextCustomEditor
    Qt::Widgets
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
