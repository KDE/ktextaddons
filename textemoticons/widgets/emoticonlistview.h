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

    void setFontSize(int newFontSize);

Q_SIGNALS:
    void emojiItemSelected(const QString &str, const QString &identifier);
    void fontSizeChanged(int size);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    void applyFontSize();
    int mFontSize = 18;
    int mRowSize = 0;
};
}
