/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once

#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateExportChatBaseJob>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateExportChatAsJsonJob class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateExportChatAsJsonJob : public TextAutoGenerateText::TextAutoGenerateExportChatBaseJob
{
    Q_OBJECT
public:
    explicit TextAutoGenerateExportChatAsJsonJob(QObject *parent = nullptr);
    ~TextAutoGenerateExportChatAsJsonJob() override;

protected:
    void exportChat() override;
};
}
