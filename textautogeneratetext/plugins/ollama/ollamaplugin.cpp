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
    for (const auto &connection : std::as_const(mConnections)) {
        disconnect(connection);
    }
    mConnections.clear();
    // TODO clear all thread
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
    clear();
}

void OllamaPlugin::sendToLLM(const QString &message, const QByteArray &uuid)
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

    mConnections.insert(reply, connect(reply, &OllamaReply::contentAdded, this, [reply, uuid]() {
                            TextAutogenerateText::TextAutogenerateManager::self()->textAutoGenerateChatModel()->replaceContent(uuid, reply->readResponse());
                        }));
    mConnections.insert(reply, connect(reply, &OllamaReply::finished, this, [reply, uuid, this] {
                            TextAutogenerateText::TextAutogenerateManager::self()->textAutoGenerateChatModel()->changeInProgress(uuid, false);
                            mConnections.remove(reply);
                            reply->deleteLater();
#if 0
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
                            // Q_EMIT finished(message); // TODO add message as argument ???
                        }));
}

#include "moc_ollamaplugin.cpp"
