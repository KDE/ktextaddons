/*
SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/textautogeneratechatsmodel.h"
#include "core/textautogeneratemessagesmodel.h"

#include <KConfigGroup>
#include <QRegularExpression>

using namespace TextAutoGenerateText;
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateMessagesModel(new TextAutoGenerateMessagesModel(this))
    , mTextAutoGenerateChatsModel(new TextAutoGenerateChatsModel(this))
    , mDatabaseManager(new TextAutoGenerateLocalDatabaseManager)
{
}

TextAutoGenerateManager::~TextAutoGenerateManager() = default;

TextAutoGenerateManager *TextAutoGenerateManager::self()
{
    static TextAutoGenerateManager s_self;
    return &s_self;
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

TextAutoGenerateMessagesModel *TextAutoGenerateManager::textAutoGenerateMessagesModel() const
{
    return mTextAutoGenerateMessagesModel;
}

TextAutoGenerateChatsModel *TextAutoGenerateManager::textAutoGenerateChatsModel() const
{
    return mTextAutoGenerateChatsModel;
}

bool TextAutoGenerateManager::showArchived() const
{
    return mShowArchived;
}

void TextAutoGenerateManager::setShowArchived(bool newShowArchived)
{
    mShowArchived = newShowArchived;
}

void TextAutoGenerateManager::loadHistory()
{
    // Load chat from database
    const QList<TextAutoGenerateChat> chats = mDatabaseManager->loadChats();
    mTextAutoGenerateChatsModel->setChats(std::move(chats));
}

#include "moc_textautogeneratemanager.cpp"
