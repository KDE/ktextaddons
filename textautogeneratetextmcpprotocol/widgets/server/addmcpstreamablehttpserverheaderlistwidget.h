/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QListWidget>

#include "textautogeneratetextmcpprotocolwidgets_export.h"
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpStreamableHttpServerHeaderListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AddMcpStreamableHttpServerHeaderListWidget(QWidget *parent = nullptr);
    ~AddMcpStreamableHttpServerHeaderListWidget() override;
    void setHeaders(const QStringList &lst);
    [[nodiscard]] QStringList headers() const;
    void addHeader(const QString &str);

    [[nodiscard]] QString currentText() const;
    void modifyHeader(const QString &str);
};
}
