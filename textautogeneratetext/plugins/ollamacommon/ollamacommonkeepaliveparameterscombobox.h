/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonkeepaliveparameterswidget.h"
#include "ollamacommonsettings.h"
#include "textautogenerateollamacommon_export.h"
#include <QComboBox>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonKeepAliveParametersComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaCommonKeepAliveParametersComboBox(QWidget *parent = nullptr);
    ~OllamaCommonKeepAliveParametersComboBox() override;

    [[nodiscard]] OllamaCommonSettings::KeepAliveType keepAliveType() const;
    void setKeepAliveType(OllamaCommonSettings::KeepAliveType type);

private:
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void fill();
};
