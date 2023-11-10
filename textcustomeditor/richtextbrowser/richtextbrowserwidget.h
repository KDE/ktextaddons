/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"

#include <QWidget>

namespace TextCustomEditor
{
class RichTextBrowser;
class RichTextBrowserWidgetPrivate;
/**
 * @brief The RichTextBrowserWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT RichTextBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RichTextBrowserWidget(QWidget *parent = nullptr);
    explicit RichTextBrowserWidget(RichTextBrowser *customEditor, QWidget *parent = nullptr);
    ~RichTextBrowserWidget() override;

    void clear();

    [[nodiscard]] RichTextBrowser *editor() const;

    void setHtml(const QString &html);
    [[nodiscard]] QString toHtml() const;

    void setPlainText(const QString &text);
    [[nodiscard]] QString toPlainText() const;

    void setAcceptRichText(bool b);
    bool acceptRichText() const;

    [[nodiscard]] bool isEmpty() const;
public Q_SLOTS:
    void slotFindNext();
    void slotFind();

private:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotHideFindBar();
    TEXTCUSTOMEDITOR_NO_EXPORT void init(RichTextBrowser *customEditor = nullptr);
    std::unique_ptr<RichTextBrowserWidgetPrivate> const d;
};
}
