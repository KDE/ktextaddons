/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <KService>
#include <QDialog>
class QMenu;
class QToolButton;
class QAction;
namespace TextAutoGenerateText
{
class TextAutoGenerateShowImageWidget;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateShowImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowImageDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateShowImageDialog() override;

    void setImage(const QString &path);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateServiceList();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotOpenWith(QAction *action);
    TextAutoGenerateShowImageWidget *const mShowImageWidget;
    KService::List mServiceList;
    QMenu *const mClipboardMenu;
    QToolButton *const mOpenWithButton;
    QMenu *const mOpenWithMenu;
    QAction *mClipboardImageAction = nullptr;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
