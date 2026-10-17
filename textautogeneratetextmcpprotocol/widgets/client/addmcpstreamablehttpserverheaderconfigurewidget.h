/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpStreamableHttpServerHeaderConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpStreamableHttpServerHeaderConfigureWidget(QWidget *parent = nullptr);
    ~AddMcpStreamableHttpServerHeaderConfigureWidget() override;

    void setHeader(const QString &str);
    [[nodiscard]] QString header() const;

Q_SIGNALS:
    void buttonOkEnabled(bool state);

private:
    QLineEdit *const mHeaderLineEdit;
};
}
