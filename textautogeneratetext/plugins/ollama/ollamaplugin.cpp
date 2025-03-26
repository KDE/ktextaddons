/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamanager.h"
#include "ollamasettings.h"

OllamaPlugin::OllamaPlugin(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextPlugin{parent}
{
    if (!loadSettings()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to load settings";
    }

      connect(OllamaManager::self(), &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
          if (modelinfo.hasError) {
              mReady = false;
              Q_EMIT errorOccurred(modelinfo.errorOccured);
          } else {
              mReady = true;
          }
      });
      OllamaManager::self()->loadModels();
}

OllamaPlugin::~OllamaPlugin() = default;

bool OllamaPlugin::loadSettings()
{
    setCurrentModel(OllamaSettings::model());
    // TODO verify that server is ok.
    return false;
}

void OllamaPlugin::clear()
{
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

bool OllamaPlugin::ready() const
{
    return mReady;
}

void OllamaPlugin::setReady(bool newReady)
{
    mReady = newReady;
}

QString OllamaPlugin::currentModel() const
{
    return mCurrentModel;
}

void OllamaPlugin::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

#include "moc_ollamaplugin.cpp"
