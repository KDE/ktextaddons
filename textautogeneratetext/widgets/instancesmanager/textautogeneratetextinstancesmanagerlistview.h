/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QListView>
class QSortFilterProxyModel;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextInstancesManagerListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerListView() override;

    void slotSearchChanged(const QString &str);

private:
    QSortFilterProxyModel *const mSortFilterProxyModel;
    TextAutoGenerateManager *const mTextAutoGenerateManager;
};
}
