/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosdelegate.h"
#include "ollamamodelinfosmodel.h"
OllamaModelInfosDelegate::OllamaModelInfosDelegate(QListView *view)
    : TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate(view)
{
}

OllamaModelInfosDelegate::~OllamaModelInfosDelegate() = default;

QTextDocument *OllamaModelInfosDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    Q_ASSERT(index.isValid());
    const QByteArray uuid = index.data(OllamaModelInfosModel::ModelName).toByteArray();
    Q_ASSERT(!uuid.isEmpty());
    auto it = mDocumentCache.find(uuid);
    if (it != mDocumentCache.end()) {
        auto ret = it->value.get();
        if (width != -1 && !qFuzzyCompare(ret->textWidth(), width)) {
            ret->setTextWidth(width);
        }
        return ret;
    }
    const QString text = index.data(OllamaModelInfosModel::Description).toString();
    if (text.isEmpty()) {
        return nullptr;
    }
    auto doc = createTextDocument(text, width);
    auto ret = doc.get();
    mDocumentCache.insert(uuid, std::move(doc));
    return ret;
}

#include "moc_ollamamodelinfosdelegate.cpp"
