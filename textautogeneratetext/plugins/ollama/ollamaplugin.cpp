/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessagesmodel.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

using namespace Qt::Literals::StringLiterals;
OllamaPlugin::OllamaPlugin(QObject *parent)
    : TextAutogenerateText::TextAutoGenerateTextPlugin{parent}
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

QString OllamaPlugin::name()
{
    return "ollama"_L1;
}

bool OllamaPlugin::loadSettings()
{
    setCurrentModel(OllamaSettings::model());
    // TODO verify that server is ok.
    return true;
}

void OllamaPlugin::clear()
{
    for (const auto &connection : std::as_const(mConnections)) {
        disconnect(connection.second);
    }
    mConnections.clear();
    // TODO clear all thread
}

void OllamaPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString OllamaPlugin::engineName() const
{
    return name();
}

void OllamaPlugin::cancelRequest(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        clear();
    } else {
        for (const auto &connection : std::as_const(mConnections)) {
            if (connection.first == uuid) {
                disconnect(connection.second);
                // mConnections.take(connection.);
            }
        }
    }
}

void OllamaPlugin::sendToLLM(const QString &message, const QByteArray &uuid)
{
    OllamaRequest req;
    req.setMessage(message);
    req.setModel(currentModel());
    /*
    for (const auto &msg : m_messages | std::views::reverse) {
        if (msg.sender == Sender::LLM) {
            req.setContext(message.context);
            break;
        }
    }
    */
    auto reply = OllamaManager::self()->getCompletion(req);

    mConnections.insert(reply,
                        QPair<QByteArray, QMetaObject::Connection>(
                            uuid,
                            connect(reply, &OllamaReply::contentAdded, this, [reply, uuid]() {
                                TextAutogenerateText::TextAutoGenerateManager::self()->textAutoGenerateChatModel()->replaceContent(uuid, reply->readResponse());
                            })));
    mConnections.insert(reply,
                        QPair<QByteArray, QMetaObject::Connection>(
                            uuid,
                            connect(reply, &OllamaReply::finished, this, [reply, uuid, this] {
                                TextAutogenerateText::TextAutoGenerateManager::self()->textAutoGenerateChatModel()->changeInProgress(uuid, false);
                                mConnections.remove(reply);
                                reply->deleteLater();
#if 0
                                // TODO add context + info
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
                                // Q_EMIT finished(message); // TODO add message as argument ???
                            })));
}

#include "moc_ollamaplugin.cpp"
