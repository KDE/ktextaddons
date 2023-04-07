/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QHBoxLayout;
namespace TextEmoticonsWidgets
{
class EmoticonCategoryButtons : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonCategoryButtons(QWidget *parent = nullptr);
    ~EmoticonCategoryButtons() override;

Q_SIGNALS:
    void categorySelected(const QString &category);

private:
    void setCategories(const QStringList &categories);
    QHBoxLayout *mMainLayout = nullptr;
};
}
