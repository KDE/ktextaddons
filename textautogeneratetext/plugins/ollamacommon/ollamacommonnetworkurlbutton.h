/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QToolButton>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonNetworkUrlButton : public QToolButton
{
    Q_OBJECT
public:
    explicit OllamaCommonNetworkUrlButton(QWidget *parent = nullptr);
    ~OllamaCommonNetworkUrlButton() override;

    [[nodiscard]] QString url() const;
    void setUrl(const QString &newModelUrl);

private:
    QString mUrl;
};
