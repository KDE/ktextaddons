/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_private_export.h"
#include <QToolButton>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaNetworkUrlButton : public QToolButton
{
    Q_OBJECT
public:
    explicit OllamaNetworkUrlButton(QWidget *parent = nullptr);
    ~OllamaNetworkUrlButton() override;

    [[nodiscard]] QString modelUrl() const;
    void setModelUrl(const QString &newModelUrl);

private:
    QString mModelUrl;
};
