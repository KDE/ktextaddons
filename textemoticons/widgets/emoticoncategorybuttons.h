/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QHBoxLayout;
class QButtonGroup;
namespace TextEmoticonsCore
{
class EmoticonCategory;
}
namespace TextEmoticonsWidgets
{
class EmoticonCategoryButtons : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonCategoryButtons(QWidget *parent = nullptr);
    ~EmoticonCategoryButtons() override;

    void setCategories(const QList<TextEmoticonsCore::EmoticonCategory> &categories);

Q_SIGNALS:
    void categorySelected(const QString &category);

private:
    QHBoxLayout *mMainLayout = nullptr;
    QButtonGroup *const mButtonGroup;
};
}
