/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolsLoadingJob
 * \brief The TextAutoGenerateTextToolsLoadingJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolsLoadingJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolsLoadingJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolsLoadingJob(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolsLoadingJob() override;

    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void properties(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> &list);
};
}
