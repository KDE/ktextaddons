/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPlugin(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPlugin() override;

    [[nodiscard]] virtual QString executeTool() = 0;

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString toolName() const;
    void setToolName(const QString &newToolName);

protected:
    QString mToolName;
    bool mEnabled = true;
};
}
