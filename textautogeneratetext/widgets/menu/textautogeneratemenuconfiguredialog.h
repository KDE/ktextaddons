/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratemenutextinfo.h"
#include "textautogeneratetext_private_export.h"

#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuConfigureWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMenuConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuConfigureDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateMenuConfigureDialog() override;

    void setAiTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos);
    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> aiTextInfos() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateMenuConfigureWidget *const mTextMenuConfigureWidget;
};
}
