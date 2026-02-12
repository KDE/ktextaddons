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
 * \class TextAutoGenerateText::TextAutoGenerateImportChatBaseJob
 * \brief The TextAutoGenerateImportChatBaseJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateImportChatBaseJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateImportChatBaseJob : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT ImportChatInfo {
        QString filename;
        QString chatTitle;
        [[nodiscard]] bool isValid() const;
    };

    /*! Constructs a new TextAutoGenerateImportChatBaseJob with the given @p parent. */
    explicit TextAutoGenerateImportChatBaseJob(QObject *parent = nullptr);
    /*! Destroys the TextAutoGenerateImportChatBaseJob object. */
    ~TextAutoGenerateImportChatBaseJob() override;

    /*! Returns the import chat information. */
    [[nodiscard]] ImportChatInfo info() const;
    /*! Sets the import chat information to @p newInfo. */
    void setInfo(const ImportChatInfo &newInfo);

    /*! Returns whether the import job can be started. */
    [[nodiscard]] bool canStart() const;
    /*! Starts the import job. */
    void start();

Q_SIGNALS:
    /*! Emitted when import is complete with the chat @p title and list of imported @p msgs. */
    void importDone(const QString &title, const QList<TextAutoGenerateText::TextAutoGenerateMessage> &msgs);

protected:
    /*! Imports the chat in the format-specific way. This is called by start(). */
    virtual void importChat() = 0;
    ImportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo &t);
