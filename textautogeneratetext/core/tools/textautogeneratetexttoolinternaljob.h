/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateAttachmentUtils>
#include <TextAutoGenerateText/TextAutoGenerateTextToolBaseJob>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternalProperty>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolBaseJob
 * \brief The TextAutoGenerateTextToolBaseJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolBaseJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalJob : public TextAutoGenerateTextToolBaseJob
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT TextToolPluginInfo {
        QString content;
        QByteArray messageUuid;
        QByteArray chatId;
        QByteArray toolIdentifier;
        QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> attachementInfoList;
    };

    /*!
     */
    explicit TextAutoGenerateTextToolInternalJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToolInternalJob() override;

    /*!
     */
    void start() override;
    /*!
     */
    [[nodiscard]] bool canStart() const override;

    /*!
     */
    [[nodiscard]] bool verifyRequiredArguments() const override;
    /*!
     */
    [[nodiscard]] QStringList requiredArguments() const override;

protected:
    QList<TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty> mProperties;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::TextToolPluginInfo &t);
