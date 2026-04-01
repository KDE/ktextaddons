/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
class QJsonArray;
namespace TextAutoGenerateText
{
class TextAutoGenerateToolShowMetaDataWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateToolShowMetaDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolShowMetaDataDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateToolShowMetaDataDialog() override;

    void setMetaData(const QJsonObject &obj);
    void setMetaData(const QJsonArray &array);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateToolShowMetaDataWidget *const mTextAutoGenerateToolPluginShowMetaDataWidget;
};
}
