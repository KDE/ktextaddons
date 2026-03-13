/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservermanager.h"
#include "core/models/textautogeneratetextmcpservermodel.h"
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
    // mTextAutoGenerateTextMcpServerModel->setMcpServers();
    // TODO
}

#include "moc_textautogeneratetextmcpservermanager.cpp"
