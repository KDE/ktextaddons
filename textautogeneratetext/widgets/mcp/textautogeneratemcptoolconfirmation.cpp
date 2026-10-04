/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolconfirmation.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QJsonDocument>
#include <QPointer>
#include <QWidget>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;

void TextAutoGenerateMcpToolConfirmation::installConfirmationHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent)
{
    const QPointer<QWidget> parentWidget(parent);
    toolsManager->setConfirmationHandler([parentWidget](const TextAutoGenerateMcpToolsManager::ToolConfirmationInfo &info,
                                                        const std::function<void(TextAutoGenerateMcpToolsManager::ToolConfirmation)> &answer) {
        const QString arguments = QString::fromUtf8(QJsonDocument(info.arguments).toJson(QJsonDocument::Indented));
        const QString text = i18n("The MCP server \"%1\" wants to run the tool \"%2\".", info.serverName, info.tool.name);
        const QString details = info.tool.description + u"\n\n"_s + i18n("Arguments:\n%1", arguments);
        const auto result = KMessageBox::questionTwoActionsCancel(parentWidget,
                                                                  text + u"\n\n"_s + details,
                                                                  i18nc("@title:window", "Run Tool"),
                                                                  KGuiItem(i18nc("@action:button", "Allow"), u"dialog-ok"_s),
                                                                  KGuiItem(i18nc("@action:button", "Always Allow This Server"), u"security-medium"_s),
                                                                  KGuiItem(i18nc("@action:button", "Deny"), u"dialog-cancel"_s));
        switch (result) {
        case KMessageBox::PrimaryAction:
            answer(TextAutoGenerateMcpToolsManager::ToolConfirmation::Allow);
            break;
        case KMessageBox::SecondaryAction:
            answer(TextAutoGenerateMcpToolsManager::ToolConfirmation::AlwaysAllowServer);
            break;
        default:
            answer(TextAutoGenerateMcpToolsManager::ToolConfirmation::Deny);
            break;
        }
    });
}
