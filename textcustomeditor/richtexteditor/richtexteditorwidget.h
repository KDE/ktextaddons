/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QWidget>

namespace TextCustomEditor
{
class RichTextEditor;
class RichTextEditorWidgetPrivate;
/**
 * @brief The RichTextEditorWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextEditorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    explicit RichTextEditorWidget(QWidget *parent = nullptr);
    explicit RichTextEditorWidget(RichTextEditor *customEditor, QWidget *parent = nullptr);
    ~RichTextEditorWidget() override;

    void clear();

    [[nodiscard]] RichTextEditor *editor() const;

    void setReadOnly(bool readOnly);
    bool isReadOnly() const;

    void setHtml(const QString &html);
    [[nodiscard]] QString toHtml() const;

    void setPlainText(const QString &text);
    [[nodiscard]] QString toPlainText() const;

    void setAcceptRichText(bool b);
    [[nodiscard]] bool acceptRichText() const;

    void setSpellCheckingConfigFileName(const QString &_fileName);

    [[nodiscard]] bool isEmpty() const;
public Q_SLOTS:
    void slotFindNext();
    void slotFind();
    void slotReplace();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(RichTextEditor *customEditor = nullptr);
    std::unique_ptr<RichTextEditorWidgetPrivate> const d;
};
}
