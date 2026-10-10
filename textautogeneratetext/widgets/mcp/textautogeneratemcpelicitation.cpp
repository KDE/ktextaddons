/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcpelicitation.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "widgets/mcp/textautogenerateelicitationdialog.h"
#include <QPointer>
#include <QWidget>

using namespace TextAutoGenerateText;

void TextAutoGenerateMcpElicitation::installElicitationHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent)
{
    const QPointer<QWidget> parentWidget(parent);
    toolsManager->setElicitationHandler(
        [parentWidget](const TextAutoGenerateMcpToolsManager::ElicitationInfo &info,
                       const std::function<void(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &)> &answer) {
            // TODO use info.request for creating form
            auto dlg = new TextAutoGenerateElicitationDialog(parentWidget);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->setServerName(info.serverName);
            QObject::connect(dlg, &QDialog::finished, dlg, [dlg, answer]() {
                answer(dlg->elicitResult());
            });
            dlg->open();
        });
}
