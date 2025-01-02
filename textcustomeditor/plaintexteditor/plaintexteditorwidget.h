/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QWidget>

namespace TextCustomEditor
{
class PlainTextEditor;
class PlainTextEditorWidgetPrivate;
/**
 * @brief The PlainTextEditorWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    explicit PlainTextEditorWidget(QWidget *parent = nullptr);
    explicit PlainTextEditorWidget(PlainTextEditor *customEditor, QWidget *parent = nullptr);
    ~PlainTextEditorWidget() override;

    [[nodiscard]] PlainTextEditor *editor() const;

    void setReadOnly(bool readOnly);
    [[nodiscard]] bool isReadOnly() const;

    void setPlainText(const QString &text);
    [[nodiscard]] QString toPlainText() const;

    void clear();
    void setSpellCheckingConfigFileName(const QString &_fileName);

    [[nodiscard]] bool isEmpty() const;

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotFind();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotReplace();

    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(PlainTextEditor *customEditor = nullptr);
    std::unique_ptr<PlainTextEditorWidgetPrivate> const d;
};
}
