/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QStyledItemDelegate>
namespace TextEmoticonsWidgets
{
class EmoticonItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EmoticonItemDelegate(QObject *parent = nullptr);
    ~EmoticonItemDelegate() override;
};
}
