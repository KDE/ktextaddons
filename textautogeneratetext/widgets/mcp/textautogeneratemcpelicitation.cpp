/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcpelicitation.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "widgets/mcp/textautogenerateelicitationdialog.h"
#include <QDesktopServices>
#include <QPointer>
#include <QUrl>
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>

using namespace TextAutoGenerateText;

void TextAutoGenerateMcpElicitation::installElicitationHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent)
{
    const QPointer<QWidget> parentWidget(parent);
    toolsManager->setElicitationHandler(
        [parentWidget](const TextAutoGenerateMcpToolsManager::ElicitationInfo &info,
                       const std::function<void(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &)> &answer) {
            auto dlg = new TextAutoGenerateElicitationDialog(parentWidget);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->setServerName(info.serverName);
            dlg->setRequest(info.request);
            QObject::connect(dlg, &QDialog::finished, dlg, [dlg, answer, params = info.request.params()]() {
                const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result = dlg->elicitResult();
                // URL mode: user accepted to open URL (authorization, payment…)
                if (const auto urlParams = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams>(&params);
                    urlParams && result.action() == TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept) {
                    if (const QUrl url(urlParams->url()); url.scheme() == u"https" || url.scheme() == u"http") {
                        QDesktopServices::openUrl(url);
                    }
                }
                answer(result);
            });
            dlg->open();
        });
}
