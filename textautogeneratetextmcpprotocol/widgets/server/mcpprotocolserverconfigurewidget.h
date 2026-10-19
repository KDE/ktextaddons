/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
class QLineEdit;
class QCheckBox;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpProtocolServerConfigureTokenWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT McpProtocolServerConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit McpProtocolServerConfigureWidget(QWidget *parent = nullptr);
    ~McpProtocolServerConfigureWidget() override;

    void setSettings(const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings);
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings() const;

    [[nodiscard]] bool isValid() const;

Q_SIGNALS:
    void settingsChanged();

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRequireAuthenticationToggled(bool checked);
    QLineEdit *const mServerUrlLineEdit;
    QCheckBox *const mRequireAuthenticationCheckBox;
    McpProtocolServerConfigureTokenWidget *const mTokenWidget;
};
}
