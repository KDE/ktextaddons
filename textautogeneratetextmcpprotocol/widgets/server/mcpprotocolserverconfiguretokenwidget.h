/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QWidget>
class QLabel;
class QPushButton;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpProtocolServerConfigureTokenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit McpProtocolServerConfigureTokenWidget(QWidget *parent = nullptr);
    ~McpProtocolServerConfigureTokenWidget() override;

    void setAuthToken(const QByteArray &token);
    [[nodiscard]] QByteArray authToken() const;

Q_SIGNALS:
    void authTokenChanged();

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRegenerateToken();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void updateButtons();
    QByteArray mAuthToken;
    QLabel *const mResultToken;
    QPushButton *const mRegenerateTokenButton;
    QPushButton *const mCopyTokenButton;
};
}
