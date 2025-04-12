/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_debug.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

OllamaPlugin::OllamaPlugin(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextPlugin{parent}
{
    if (!loadSettings()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to load settings";
        return;
    }

    connect(OllamaManager::self(), &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT errorOccurred(modelinfo.errorOccured);
        } else {
            setReady(true);
        }
    });
    OllamaManager::self()->loadModels();
}

OllamaPlugin::~OllamaPlugin() = default;

bool OllamaPlugin::loadSettings()
{
    setCurrentModel(OllamaSettings::model());
    // TODO verify that server is ok.
    return true;
}

void OllamaPlugin::clear()
{
    // TODO clear all thread
}

QString OllamaPlugin::result()
{
    // TODO
    return {};
}

void OllamaPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString OllamaPlugin::currentModel() const
{
    return mCurrentModel;
}

void OllamaPlugin::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

void OllamaPlugin::stop()
{
    // TODO
}

void OllamaPlugin::sendToLLM(const QString &message)
{
    OllamaRequest req;
    req.setMessage(message);
    req.setModel(mCurrentModel);
    /*
    for (const auto &msg : m_messages | std::views::reverse) {
        if (msg.sender == Sender::LLM) {
            req.setContext(message.context);
            break;
        }
    }
    */
    auto reply = OllamaManager::self()->getCompletion(req);

    mConnections.insert(reply, connect(reply, &OllamaReply::contentAdded, this, [reply]() {
                            auto message = TextAutogenerateText::TextAutogenerateManager::self()->textAutoGenerateChatModel()->lastMessage();
                            message.setContent(reply->readResponse());
                            TextAutogenerateText::TextAutogenerateManager::self()->textAutoGenerateChatModel()->replaceLastMessage(message);
                        }));
#if 0
    mConnections.insert(reply, connect(reply, &OllamaReply::finished, this, [this, i = m_messages.size() - 1] {
                            auto &message = m_messages[i];
                            mConnections.remove(message.llmReply);
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
                            message.llmReply->deleteLater();
                            message.llmReply = nullptr;
                            message.inProgress = false;
                            Q_EMIT dataChanged(index(i),
                                               index(i),
                                               {Roles::FinishedRole, Roles::TokensPerSecondRole, Roles::TokenCountRole, Roles::DurationRole});
                            Q_EMIT replyInProgressChanged();
                        }));
#endif
}

#include "moc_ollamaplugin.cpp"
