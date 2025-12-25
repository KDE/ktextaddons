/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
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
/**
 * @brief The TextAutoGenerateExportChatBaseJob class
 * @author Laurent Montel <montel@kde.org>
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

    explicit TextAutoGenerateExportChatBaseJob(QObject *parent = nullptr);
    ~TextAutoGenerateExportChatBaseJob() override;

    [[nodiscard]] ExportChatInfo info() const;
    void setInfo(const ExportChatInfo &newInfo);

    [[nodiscard]] bool canStart() const;
    void start();

Q_SIGNALS:
    void exportDone();

protected:
    virtual void exportChat() = 0;
    ExportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo &t);
