/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcpsampling.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "widgets/mcp/textautogeneratesamplingdialog.h"
#include <QPointer>
#include <QWidget>

using namespace TextAutoGenerateText;

void TextAutoGenerateMcpSampling::installSamplingHandler(TextAutoGenerateMcpToolsManager *toolsManager, QWidget *parent)
{
    const QPointer<QWidget> parentWidget(parent);
    toolsManager->setSamplingHandler(
        [parentWidget](const TextAutoGenerateMcpToolsManager::SamplingInfo &info, const std::function<void(bool accepted)> &answer) {
            auto dlg = new TextAutoGenerateSamplingDialog(parentWidget);
            dlg->setAttribute(Qt::WA_DeleteOnClose);
            dlg->setServerName(info.serverName);
            dlg->setRequest(info.request);
            QObject::connect(dlg, &QDialog::finished, dlg, [answer](int result) {
                answer(result == QDialog::Accepted);
            });
            dlg->open();
        });
}
