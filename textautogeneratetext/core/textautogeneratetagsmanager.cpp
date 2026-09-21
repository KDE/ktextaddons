/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetagsmanager.h"
#include "core/models/textautogeneratetagsmodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTagsManager::TextAutoGenerateTagsManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateTagsModel(new TextAutoGenerateTagsModel(this))
{
}

TextAutoGenerateTagsManager::~TextAutoGenerateTagsManager() = default;

void TextAutoGenerateTagsManager::setTags(const QList<TextAutoGenerateTag> &newTags)
{
    mTextAutoGenerateTagsModel->setTags(newTags);
}
#include "moc_textautogeneratetagsmanager.cpp"
