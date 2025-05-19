/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratemenutextinfo.h"

#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuModel;
class TextAutoGenerateMenuListView : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuListView(QWidget *parent = nullptr);
    ~TextAutoGenerateMenuListView() override;

    void setAiTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos);
    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> aiTextInfos() const;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TextAutoGenerateMenuModel *const mModel;
};
}
