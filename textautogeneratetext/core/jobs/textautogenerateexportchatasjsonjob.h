/*
 * SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once

#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateExportChatBaseJob>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateExportChatAsJsonJob
 * \brief The TextAutoGenerateExportChatAsJsonJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateExportChatAsJsonJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateExportChatAsJsonJob : public TextAutoGenerateText::TextAutoGenerateExportChatBaseJob
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs a new TextAutoGenerateExportChatAsJsonJob
     * \param parent The parent object
     */
    explicit TextAutoGenerateExportChatAsJsonJob(QObject *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateExportChatAsJsonJob object
     */
    ~TextAutoGenerateExportChatAsJsonJob() override;

protected:
    /*!
     * \brief Exports the chat in JSON format
     */
    void exportChat() override;
};
}
