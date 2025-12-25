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
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateMenuWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMenuWidget : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuWidget(QObject *parent = nullptr);
    explicit TextAutoGenerateMenuWidget(TextAutoGenerateMenuTextManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateMenuWidget() override;

    [[nodiscard]] QMenu *menu() const;

    [[nodiscard]] QString selectedText() const;
    void setSelectedText(const QString &newSelectedText);

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
    void setManager(TextAutoGenerateText::TextAutoGenerateManager *newManager);

    [[nodiscard]] QWidget *parentWidget() const;
    void setParentWidget(QWidget *newParentWidget);

Q_SIGNALS:
    void refreshMenu();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializeMenu();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    TEXTAUTOGENERATETEXT_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateMenu();
    QString mSelectedText;
    QMenu *const mTextMenu;
    TextAutoGenerateMenuTextManager *const mMenuTextManager;
    TextAutoGenerateText::TextAutoGenerateManager *mManager = nullptr;
    QWidget *mParentWidget = nullptr;
};
}
