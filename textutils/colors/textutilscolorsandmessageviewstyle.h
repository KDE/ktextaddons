/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textutils_export.h"
#include <KColorScheme>
#include <QObject>

namespace TextUtils
{
/**
 * @brief The TextUtilsColorsAndMessageViewStyle class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTUTILS_EXPORT TextUtilsColorsAndMessageViewStyle : public QObject
{
    Q_OBJECT
public:
    static TextUtilsColorsAndMessageViewStyle &self();
    TextUtilsColorsAndMessageViewStyle();

    [[nodiscard]] KColorScheme schemeView() const;

    [[nodiscard]] KColorScheme schemeWindow() const;

Q_SIGNALS:
    void needToUpdateColors();
    void needUpdateMessageStyle();
    void needUpdateFontSize();

protected:
    [[nodiscard]] bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void regenerateColorScheme();
    KColorScheme mSchemeView;
    KColorScheme mSchemeWindow;
};
}
