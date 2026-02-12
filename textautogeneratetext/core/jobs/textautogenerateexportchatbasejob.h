/*
 * SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateExportChatBaseJob
 * \brief The TextAutoGenerateExportChatBaseJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateExportChatBaseJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateExportChatBaseJob : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT ExportChatInfo {
        QString filename;
        QString chatTitle;
        QList<TextAutoGenerateText::TextAutoGenerateMessage> listMessages;
        [[nodiscard]] bool isValid() const;
    };

    /*!
     */
    explicit TextAutoGenerateExportChatBaseJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateExportChatBaseJob() override;

    /*!
     */
    [[nodiscard]] ExportChatInfo info() const;
    /*!
     */
    void setInfo(const ExportChatInfo &newInfo);

    /*!
     */
    [[nodiscard]] bool canStart() const;
    /*!
     */
    void start();

    /*!
     */
    [[nodiscard]] virtual QString filter() const;

Q_SIGNALS:
    /*!
     */
    void exportDone();

protected:
    /*!
     */
    virtual void exportChat() = 0;
    ExportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo &t);
