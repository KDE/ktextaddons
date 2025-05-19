/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textautogeneratemenutextinfo.h"

#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuConfigureWidget;
class TextAutoGenerateMenuConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuConfigureDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateMenuConfigureDialog() override;

    void setAiTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos);
    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> aiTextInfos() const;

private:
    void readConfig();
    void writeConfig();

    TextAutoGenerateMenuConfigureWidget *const mAiTextMenuConfigureWidget;
};
}
