/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <TextCustomEditor/TextEditFindBarBase>

class QPlainTextEdit;
namespace TextCustomEditor
{
class PlainTextEditFindBarPrivate;
/**
 * @brief The PlainTextEditFindBar class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT PlainTextEditFindBar : public TextEditFindBarBase
{
    Q_OBJECT

public:
    explicit PlainTextEditFindBar(QPlainTextEdit *view, QWidget *parent = nullptr);
    ~PlainTextEditFindBar() override;

protected:
    [[nodiscard]] bool viewIsReadOnly() const override;
    [[nodiscard]] bool documentIsEmpty() const override;
    [[nodiscard]] bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) override;
    [[nodiscard]] bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) override;
    void autoSearchMoveCursor() override;

public Q_SLOTS:
    void slotSearchText(bool backward = false, bool isAutoSearch = true) override;

private Q_SLOTS:
    void slotReplaceText() override;
    void slotReplaceAllText() override;

private:
    std::unique_ptr<PlainTextEditFindBarPrivate> const d;
};
}
