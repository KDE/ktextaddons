/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QJsonObject>
#include <QWidget>
class QTextEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateToolPluginShowMetaDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginShowMetaDataWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginShowMetaDataWidget() override;

    void setMetaData(const QJsonObject &obj);

private:
    QTextEdit *const mTextEdit;
};
}
