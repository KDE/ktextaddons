/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpSteamableHttpServerHeaderConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpSteamableHttpServerHeaderConfigureWidget(QWidget *parent = nullptr);
    ~AddMcpSteamableHttpServerHeaderConfigureWidget() override;

    void setHeader(const QString &str);
    [[nodiscard]] QString header() const;

Q_SIGNALS:
    void buttonOkEnabled(bool state);

private:
    QLineEdit *const mHeaderLineEdit;
};
}
