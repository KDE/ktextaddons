/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGeneratePurgeExpiredChatsJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePurgeExpiredChatsJob(QObject *parent = nullptr);
    ~TextAutoGeneratePurgeExpiredChatsJob() override;
};
}
