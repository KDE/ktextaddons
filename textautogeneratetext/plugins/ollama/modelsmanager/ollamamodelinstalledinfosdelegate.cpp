/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfosdelegate.h"
#include "ollamamodelinstalledinfosmodel.h"

#include "widgets/view/textautogeneratelistviewtextselection.h"
#include <QAbstractTextDocumentLayout>
#include <QDesktopServices>
#include <QPainter>

using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledInfosDelegate::OllamaModelInstalledInfosDelegate(QListView *view)
    : PluginCommonModelInstalledInfosDelegate(view)
{
}

OllamaModelInstalledInfosDelegate::~OllamaModelInstalledInfosDelegate() = default;

QTextDocument *OllamaModelInstalledInfosDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    Q_ASSERT(index.isValid());
    const QByteArray modelName = index.data(OllamaModelInstalledInfosModel::ModelGeneratedName).toByteArray();
    Q_ASSERT(!modelName.isEmpty());
    auto it = mDocumentCache.find(modelName);
    if (it != mDocumentCache.end()) {
        auto ret = it->value.get();
        if (width != -1 && !qFuzzyCompare(ret->textWidth(), width)) {
            ret->setTextWidth(width);
        }
        return ret;
    }
    const QString text = index.data(OllamaModelInstalledInfosModel::ModelGeneratedName).toString();
    if (text.isEmpty()) {
        return nullptr;
    }
    const QString name = index.data(OllamaModelInstalledInfosModel::Name).toString();
    auto doc = createTextDocument(u"<b>%1</b><br/>"_s.arg(QString::fromLatin1(modelName)) + name, width);
    auto ret = doc.get();
    mDocumentCache.insert(modelName, std::move(doc));
    return ret;
}

#include "moc_ollamamodelinstalledinfosdelegate.cpp"
