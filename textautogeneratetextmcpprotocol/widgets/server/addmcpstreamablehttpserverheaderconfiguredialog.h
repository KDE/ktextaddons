/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

#include "mcpprotocolwidgets_private_export.h"
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpStreamableHttpServerHeaderConfigureWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpStreamableHttpServerHeaderConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddMcpStreamableHttpServerHeaderConfigureDialog(QWidget *parent = nullptr);
    ~AddMcpStreamableHttpServerHeaderConfigureDialog() override;

    void setHeader(const QString &str);
    [[nodiscard]] QString header() const;

private:
    AddMcpStreamableHttpServerHeaderConfigureWidget *const mAddMcpStreamableHttpServerHeaderConfigureWidget;
};
}
