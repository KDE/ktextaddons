/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosdelegate.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamodelinfosdelegateutils.h"
#include "ollamamodelinfosmodel.h"
#include <QPainter>

OllamaModelInfosDelegate::OllamaModelInfosDelegate(QListView *view)
    : TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate(view)
{
}

OllamaModelInfosDelegate::~OllamaModelInfosDelegate() = default;

void OllamaModelInfosDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    drawBackground(painter, option, index);
    painter->restore();

    const int margin = OllamaModelInfosDelegateUtils::basicMargin();
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red); // TODO
    // painter->setBrush(ColorsAndMessageViewStyle::self().schemeView().background(KColorScheme::AlternateBackground).color());
    const int offset = static_cast<int>(static_cast<double>(margin) / 2.0);
    painter->drawRoundedRect(option.rect.adjusted(offset, offset, -offset, 0), 5, 5);
    painter->restore();
}

bool OllamaModelInfosDelegate::mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return true;
}

bool OllamaModelInfosDelegate::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return true;
}

bool OllamaModelInfosDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return true;
}

OllamaModelInfosDelegate::ModelInfoLayout OllamaModelInfosDelegate::doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    OllamaModelInfosDelegate::ModelInfoLayout layout;
    QRect usableRect = option.rect;
    layout.textRect = usableRect;
    return layout;
}

QSize OllamaModelInfosDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QByteArray modelName = index.data(OllamaModelInfosModel::ModelName).toByteArray();
    auto it = mSizeHintCache.find(modelName);
    if (it != mSizeHintCache.end()) {
        const QSize result = it->value;
        qCDebug(AUTOGENERATETEXT_OLLAMA_LOG) << "ApplicationsSettingsDelegate: SizeHint found in cache: " << result;
        return result;
    }

    // Note: option.rect in this method is huge (as big as the viewport)
    const OllamaModelInfosDelegate::ModelInfoLayout layout = doLayout(option, index);
    const QSize size = {option.rect.width(), layout.textRect.height() + static_cast<int>(OllamaModelInfosDelegateUtils::basicMargin())};
    if (!size.isEmpty()) {
        mSizeHintCache.insert(modelName, size);
    }
    return size;
}

QTextDocument *OllamaModelInfosDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    Q_ASSERT(index.isValid());
    const QByteArray modelName = index.data(OllamaModelInfosModel::ModelName).toByteArray();
    Q_ASSERT(!modelName.isEmpty());
    auto it = mDocumentCache.find(modelName);
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
    mDocumentCache.insert(modelName, std::move(doc));
    return ret;
}

#include "moc_ollamamodelinfosdelegate.cpp"
