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

void TextAutoGenerateTagsManager::addTag(const TextAutoGenerateTag &newTag)
{
    mTextAutoGenerateTagsModel->addTag(newTag);
}

void TextAutoGenerateTagsManager::removeTag(const QByteArray &identifier)
{
    mTextAutoGenerateTagsModel->removeTag(identifier);
}

void TextAutoGenerateTagsManager::updateTag(const TextAutoGenerateTag &tag)
{
    mTextAutoGenerateTagsModel->updateTag(tag);
}

QList<TextAutoGenerateTag> TextAutoGenerateTagsManager::tags() const
{
    return mTextAutoGenerateTagsModel->tags();
}

TextAutoGenerateTagsModel *TextAutoGenerateTagsManager::textAutoGenerateTagsModel() const
{
    return mTextAutoGenerateTagsModel;
}

QList<QColor> TextAutoGenerateTagsManager::colors(const QList<QByteArray> &identifiers) const
{
    return mTextAutoGenerateTagsModel->colors(identifiers);
}

#include "moc_textautogeneratetagsmanager.cpp"
