/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservermanager.h"
#include "core/models/textautogeneratetextmcpservermodel.h"
#include "textautogeneratetextcore_debug.h"
#include "textautogeneratetextutils.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextMcpServerManager::TextAutoGenerateTextMcpServerManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateTextMcpServerModel(new TextAutoGenerateTextMcpServerModel(this))
{
}

TextAutoGenerateText::TextAutoGenerateTextMcpServerManager::~TextAutoGenerateTextMcpServerManager() = default;

TextAutoGenerateTextMcpServerModel *TextAutoGenerateTextMcpServerManager::textAutoGenerateTextMcpServerModel() const
{
    return mTextAutoGenerateTextMcpServerModel;
}

void TextAutoGenerateTextMcpServerManager::loadServers()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());
    const QStringList mcpServerList = TextAutoGenerateTextUtils::mcpServerList(config);
    if (mcpServerList.isEmpty()) {
        return; // nothing to be done...
    }

    QList<TextAutoGenerateTextMcpServer> mcpServers;
    for (const auto &group : mcpServerList) {
        const KConfigGroup configGroup(config, group);
        TextAutoGenerateTextMcpServer server;
        server.load(configGroup);
        if (server.isValid()) {
            mcpServers.append(server);
        }
    }
    mTextAutoGenerateTextMcpServerModel->setMcpServers(mcpServers);
}

void TextAutoGenerateTextMcpServerManager::saveServers()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());
    const auto instanceList = TextAutoGenerateTextUtils::mcpServerList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    const QList<TextAutoGenerateTextMcpServer> serverLst = mTextAutoGenerateTextMcpServerModel->mcpServers();
    for (int i = 0; i < serverLst.count(); ++i) {
        auto server = serverLst.at(i);
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(i));
        server.save(group);
    }
    config->sync();
}

#include "moc_textautogeneratetextmcpservermanager.cpp"
