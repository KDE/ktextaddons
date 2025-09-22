/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
class ExampleTextToolPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit ExampleTextToolPluginJob(QObject *parent = nullptr);
    ~ExampleTextToolPluginJob() override;

    const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &toolArguments() const;
    void setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments);

    [[nodiscard]] bool canStart() const;

    void start();

private:
    QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> mToolArguments;
};
