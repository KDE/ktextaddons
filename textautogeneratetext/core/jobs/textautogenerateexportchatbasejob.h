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

    /*! Constructs a new TextAutoGenerateExportChatBaseJob with the given @p parent. */
    explicit TextAutoGenerateExportChatBaseJob(QObject *parent = nullptr);
    /*! Destroys the TextAutoGenerateExportChatBaseJob object. */
    ~TextAutoGenerateExportChatBaseJob() override;

    /*! Returns the export chat information. */
    [[nodiscard]] ExportChatInfo info() const;
    /*! Sets the export chat information to @p newInfo. */
    void setInfo(const ExportChatInfo &newInfo);

    /*! Returns whether the export job can be started. */
    [[nodiscard]] bool canStart() const;
    /*! Starts the export job. */
    void start();

    /*! Returns the file filter for export dialogs. */
    [[nodiscard]] virtual QString filter() const;

Q_SIGNALS:
    /*! Emitted when export is complete. */
    void exportDone();

protected:
    /*! Exports the chat in the format-specific way. This is called by start(). */
    virtual void exportChat() = 0;
    ExportChatInfo mInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateExportChatBaseJob::ExportChatInfo &t);
