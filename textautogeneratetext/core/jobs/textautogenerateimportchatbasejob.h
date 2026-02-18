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
    /*!
     * \class TextAutoGenerateImportChatBaseJob::ImportChatInfo
     * \brief Structure containing information for importing a chat
     */
    struct TEXTAUTOGENERATETEXT_EXPORT ImportChatInfo {
        QString filename;
        QString chatTitle;
        [[nodiscard]] bool isValid() const;
    };

    /*!
     * \brief Constructs a new TextAutoGenerateImportChatBaseJob
     * \param parent The parent object
     */
    explicit TextAutoGenerateImportChatBaseJob(QObject *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateImportChatBaseJob object
     */
    ~TextAutoGenerateImportChatBaseJob() override;

    /*!
     * \brief Returns the import chat information
     * \return The import chat info
     */
    [[nodiscard]] ImportChatInfo info() const;
    /*!
     * \brief Sets the import chat information
     * \param newInfo The import chat info to set
     */
    void setInfo(const ImportChatInfo &newInfo);

    /*!
     * \brief Returns whether the import job can be started
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;
    /*!
     * \brief Starts the import job
     */
    void start();

Q_SIGNALS:
    /*!
     * \brief Emitted when import is complete
     * \param title The title of the imported chat
     * \param msgs The list of imported messages
     */
    void importDone(const QString &title, const QList<TextAutoGenerateText::TextAutoGenerateMessage> &msgs);

protected:
    /*!
     * \brief Imports the chat in the format-specific way
     * This method is called by start() and should be implemented by subclasses
     */
    virtual void importChat() = 0;
    /*!
     * \brief The import chat information
     */
    ImportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateImportChatBaseJob::ImportChatInfo &t);
