/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QMenu;
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuTextManager;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMenuWidget : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuWidget(QObject *parent = nullptr);
    ~TextAutoGenerateMenuWidget() override;

    [[nodiscard]] QMenu *menu() const;

    [[nodiscard]] QString selectedText() const;
    void setSelectedText(const QString &newSelectedText);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializeMenu();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    QString mSelectedText;
    QMenu *const mTextMenu;
    TextAutoGenerateMenuTextManager *const mMenuTextManager;
};
}
