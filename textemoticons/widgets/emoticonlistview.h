/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] bool isRecentView() const;
    void setIsRecentView(bool newIsRecentView);

Q_SIGNALS:
    void emojiItemSelected(const QString &str, const QString &identifier);
    void fontSizeChanged(int size);
    void clearHistory();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TEXTEMOTICONSWIDGETS_NO_EXPORT void applyFontSize();
    TEXTEMOTICONSWIDGETS_NO_EXPORT void selectEmoji(const QModelIndex &index);
    int mFontSize = 18;
    int mRowSize = 0;
    bool mIsRecentView = false;
};
}
