/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QByteArray>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextToolBaseJob>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolPluginJob
 * \brief The TextAutoGenerateTextToolPluginJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolPluginJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginJob : public TextAutoGenerateTextToolBaseJob
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolPluginJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToolPluginJob() override;

    /*!
     */
    void start() override;

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties() const;
    /*!
     */
    void setProperties(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> &newProperties);

    /*!
     */
    [[nodiscard]] bool verifyRequiredArguments() const override;

    /*!
     */
    [[nodiscard]] QStringList requiredArguments() const override;

Q_SIGNALS:
    /*!
     */
    void finished(const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info);
    /*!
     */
    void toolInProgress(const QString &info);
    /*!
     */
    void error(const QString &errorStr);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> mProperties;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginJob &t);
