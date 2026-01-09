/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */
#pragma once

#include "textautogenerateimportchatbasejob.h"
namespace TextAutoGenerateText
{
/*!
 * \brief The TextAutoGenerateImportChatAsJsonJob class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateImportChatAsJsonJob : public TextAutoGenerateText::TextAutoGenerateImportChatBaseJob
{
    Q_OBJECT
public:
    explicit TextAutoGenerateImportChatAsJsonJob(QObject *parent = nullptr);
    ~TextAutoGenerateImportChatAsJsonJob() override;

protected:
    void importChat() override;
};
}
