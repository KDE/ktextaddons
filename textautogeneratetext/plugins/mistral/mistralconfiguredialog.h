/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratemistral_export.h"
#include <QDialog>
class MistralConfigureWidget;
class TEXTAUTOGENERATEMISTRAL_EXPORT MistralConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MistralConfigureDialog(QWidget *parent = nullptr);
    ~MistralConfigureDialog() override;

    void setApiKey(const QString &key);
    [[nodiscard]] QString apiKey() const;

private:
    TEXTAUTOGENERATEMISTRAL_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEMISTRAL_NO_EXPORT void writeConfig();
    MistralConfigureWidget *const mMistralConfigureWidget;
};
