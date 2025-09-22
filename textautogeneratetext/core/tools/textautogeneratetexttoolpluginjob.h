/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPluginJob(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPluginJob() override;

    virtual void start();
    [[nodiscard]] bool canStart() const;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> toolArguments() const;
    void setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments);

    [[nodiscard]] QStringList requiredArguments() const;
    void setRequiredArguments(const QStringList &newRequiredArguments);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> mToolArguments;
    QStringList mRequiredArguments;
};
}
