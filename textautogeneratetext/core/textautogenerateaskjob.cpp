/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaskjob.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAskJob::TextAutoGenerateAskJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAskJob::~TextAutoGenerateAskJob() = default;

bool TextAutoGenerateAskJob::canStart() const
{
    if (!mManager) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Manager is null! It's a bug";
        return false;
    }
    if (mText.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Text is empty! It's a bug";
        return false;
    }
    return true;
}

void TextAutoGenerateAskJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, &TextAutoGenerateAskJob::slotInitializeDone);
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateAskJob::slotAutogenerateFailed);
    mManager->loadEngine();
}

void TextAutoGenerateAskJob::slotAutogenerateFailed(const QString &msg)
{
    Q_EMIT errorOccured(msg);
    deleteLater();
}

void TextAutoGenerateAskJob::slotInitializeDone()
{
    connect(mManager->textAutoGeneratePlugin(),
            &TextAutoGenerateText::TextAutoGenerateTextPlugin::askToAssistantDone,
            this,
            &TextAutoGenerateAskJob::slotAskToLlmDone);
    connect(mManager->textAutoGeneratePlugin(),
            &TextAutoGenerateText::TextAutoGenerateTextPlugin::askToAssistant,
            this,
            &TextAutoGenerateAskJob::slotAskToLlmAnswer);

    mManager->askToLLM(mText);
}

void TextAutoGenerateAskJob::slotAskToLlmAnswer(const QString &msg)
{
    Q_EMIT generateTextInProgress(msg);
}

void TextAutoGenerateAskJob::slotAskToLlmDone()
{
    Q_EMIT generateTextDone();
    deleteLater();
}

TextAutoGenerateManager *TextAutoGenerateAskJob::manager() const
{
    return mManager;
}

void TextAutoGenerateAskJob::setManager(TextAutoGenerateManager *newManager)
{
    mManager = newManager;
}

QString TextAutoGenerateAskJob::text() const
{
    return mText;
}

void TextAutoGenerateAskJob::setText(const QString &newText)
{
    mText = newText;
}

#include "moc_textautogenerateaskjob.cpp"
