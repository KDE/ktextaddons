/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateImportChatBaseJob : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT ImportChatInfo {
        QString filename;
        QString chatTitle;
        [[nodiscard]] bool isValid() const;
    };

    explicit TextAutoGenerateImportChatBaseJob(QObject *parent = nullptr);
    ~TextAutoGenerateImportChatBaseJob() override;

    [[nodiscard]] ImportChatInfo info() const;
    void setInfo(const ImportChatInfo &newInfo);

    [[nodiscard]] bool canStart() const;
    void start();

Q_SIGNALS:
    void importDone();

protected:
    virtual void exportChat() = 0;
    ImportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo &t);
