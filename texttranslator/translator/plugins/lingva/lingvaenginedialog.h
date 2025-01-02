/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class LingvaEngineWidget;
class LingvaEngineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LingvaEngineDialog(QWidget *parent = nullptr);
    ~LingvaEngineDialog() override;

    [[nodiscard]] QString serverUrl() const;

    void setServerUrl(const QString &serverUrl);

private:
    LingvaEngineWidget *const mConfigureWidget;
};
