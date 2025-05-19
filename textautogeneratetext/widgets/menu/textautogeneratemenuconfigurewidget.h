/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textautogeneratemenutextinfo.h"

#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuListView;
class TextAutoGenerateMenuConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuConfigureWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateMenuConfigureWidget() override;

    void setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos);
    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> textInfos() const;

private:
    TextAutoGenerateMenuListView *const mListView;
};
}
