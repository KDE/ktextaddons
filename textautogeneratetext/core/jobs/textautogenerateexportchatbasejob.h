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
    /*!
     * \class TextAutoGenerateExportChatBaseJob::ExportChatInfo
     * \brief Structure containing information for exporting a chat
     */
    struct TEXTAUTOGENERATETEXT_EXPORT ExportChatInfo {
        QString filename;
        QString chatTitle;
        QList<TextAutoGenerateText::TextAutoGenerateMessage> listMessages;
        [[nodiscard]] bool isValid() const;
    };

    /*!
     * \brief Constructs a new TextAutoGenerateExportChatBaseJob
     * \param parent The parent object
     */
    explicit TextAutoGenerateExportChatBaseJob(QObject *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateExportChatBaseJob object
     */
    ~TextAutoGenerateExportChatBaseJob() override;

    /*!
     * \brief Returns the export chat information
     * \return The export chat info
     */
    [[nodiscard]] ExportChatInfo info() const;
    /*!
     * \brief Sets the export chat information
     * \param newInfo The export chat info to set
     */
    void setInfo(const ExportChatInfo &newInfo);

    /*!
     * \brief Returns whether the export job can be started
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;
    /*!
     * \brief Starts the export job
     */
    void start();

    /*!
     * \brief Returns the file filter for export dialogs
     * \return The file filter string
     */
    [[nodiscard]] virtual QString filter() const;

Q_SIGNALS:
    /*!
     * \brief Emitted when export is complete
     */
    void exportDone();

protected:
    /*!
     * \brief Exports the chat in the format-specific way
     * This method is called by start() and should be implemented by subclasses
     */
    virtual void exportChat() = 0;
    /*!
     * \brief The export chat information
     */
    ExportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo &t);
