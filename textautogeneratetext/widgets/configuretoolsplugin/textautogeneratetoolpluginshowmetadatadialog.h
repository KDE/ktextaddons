/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateToolPluginShowMetaDataWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateToolPluginShowMetaDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginShowMetaDataDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginShowMetaDataDialog() override;

    void setMetaData(const QJsonObject &obj);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateToolPluginShowMetaDataWidget *const mTextAutoGenerateToolPluginShowMetaDataWidget;
};
}
