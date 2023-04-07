/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonswidgets_private_export.h"
#include <QListView>
namespace TextEmoticonsWidgets
{
class TEXTEMOTICONSWIDGETS_TESTS_EXPORT EmoticonListView : public QListView
{
    Q_OBJECT
public:
    explicit EmoticonListView(QWidget *parent = nullptr);
    ~EmoticonListView() override;
Q_SIGNALS:
    void emojiItemSelected(const QString &str, const QString &identifier);
};
}
