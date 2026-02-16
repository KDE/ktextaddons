/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "ollamacommonsettings.h"

#include <QComboBox>

class OllamaCommonShareNameComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaCommonShareNameComboBox(QWidget *parent = nullptr);
    ~OllamaCommonShareNameComboBox() override;

    [[nodiscard]] OllamaCommonSettings::ShareNameType shareNameType() const;
    void setShareNameType(OllamaCommonSettings::ShareNameType type);

private:
    void fill();
};
