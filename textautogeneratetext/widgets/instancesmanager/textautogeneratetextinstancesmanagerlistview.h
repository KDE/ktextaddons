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
class TextAutoGenerateTextInstanceModel;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextInstancesManagerListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerListView(QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerListView() override;

    void slotSearchChanged(const QString &str);

private:
    TextAutoGenerateTextInstanceModel *const mModel;
    QSortFilterProxyModel *const mSortFilterProxyModel;
};
}
