/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KColorScheme>
#include <QObject>

namespace TextAutoGenerateText
{
class TextAutoGenerateColorsAndMessageViewStyle : public QObject
{
    Q_OBJECT
public:
    static TextAutoGenerateColorsAndMessageViewStyle &self();
    TextAutoGenerateColorsAndMessageViewStyle();

    [[nodiscard]] KColorScheme schemeView() const;

    [[nodiscard]] KColorScheme schemeWindow() const;

Q_SIGNALS:
    void needToUpdateColors();

protected:
    [[nodiscard]] bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void regenerateColorScheme();
    KColorScheme mSchemeView;
    KColorScheme mSchemeWindow;
};
}
