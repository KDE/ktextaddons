/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QWidget>

namespace TextCustomEditor
{
class RichTextEditor;
class RichTextBrowserWidgetPrivate;
/**
 * @brief The RichTextBrowserWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextBrowserWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    explicit RichTextBrowserWidget(QWidget *parent = nullptr);
    explicit RichTextBrowserWidget(RichTextEditor *customEditor, QWidget *parent = nullptr);
    ~RichTextBrowserWidget() override;

    void clear();

    Q_REQUIRED_RESULT RichTextEditor *editor() const;

    void setReadOnly(bool readOnly);
    bool isReadOnly() const;

    void setHtml(const QString &html);
    Q_REQUIRED_RESULT QString toHtml() const;

    void setPlainText(const QString &text);
    Q_REQUIRED_RESULT QString toPlainText() const;

    void setAcceptRichText(bool b);
    bool acceptRichText() const;

    void setSpellCheckingConfigFileName(const QString &_fileName);

    Q_REQUIRED_RESULT bool isEmpty() const;
public Q_SLOTS:
    void slotFindNext();
    void slotFind();
    void slotReplace();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(RichTextEditor *customEditor = nullptr);
    std::unique_ptr<RichTextBrowserWidgetPrivate> const d;
};
}
