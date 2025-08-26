/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QFrame>
class QTimer;
class QTextEdit;
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT RichTextQuickTextFormat : public QFrame
{
    Q_OBJECT
public:
    enum class QuickTextFormatType : uint8_t {
        Bold,
        Italic,
        StrikeThrough,
        CodeBlock,
        BlockQuote,
        InsertLink,
    };
    Q_ENUM(QuickTextFormatType);

    explicit RichTextQuickTextFormat(QTextEdit *editor, QWidget *parent = nullptr);
    ~RichTextQuickTextFormat() override;

Q_SIGNALS:
    void quickTextFormatRequested(TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType type);

protected:
    [[nodiscard]] bool eventFilter(QObject *watched, QEvent *event) override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void updatePosition();
    QTextEdit *const mEditor;
    QTimer *const mUpdatePositionTimer;
};
}
