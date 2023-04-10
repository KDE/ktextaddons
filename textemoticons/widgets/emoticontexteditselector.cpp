/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontexteditselector.h"
#include "emoticoncategorybuttons.h"
#include "emoticonlistview.h"

#include <KLocalizedString>
#include <QLineEdit>
#include <QScreen>
#include <QVBoxLayout>
#include <TextEmoticonsCore/EmoticonUnicodeModel>
#include <TextEmoticonsCore/EmoticonUnicodeModelManager>
#include <TextEmoticonsCore/EmoticonUnicodeProxyModel>
#include <TextEmoticonsCore/EmoticonUnicodeUtils>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

using namespace TextEmoticonsWidgets;

EmoticonTextEditSelector::EmoticonTextEditSelector(QWidget *parent)
    : QWidget(parent)
    , mCategoryButtons(new EmoticonCategoryButtons(this))
    , mSearchUnicodeLineEdit(new QLineEdit(this))
    , mEmoticonListView(new EmoticonListView(this))
    , mEmoticonProxyModel(new TextEmoticonsCore::EmoticonUnicodeProxyModel(this))
{
    const int defaultFontSize{22};
    QFont f;
    f.setPointSize(defaultFontSize);
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    mEmoticonListView->setFontSize(defaultFontSize);
    mCategoryButtons->setFont(f);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins({});
    mSearchUnicodeLineEdit->setObjectName(QStringLiteral("mSearchUnicodeLineEdit"));
    mSearchUnicodeLineEdit->setClearButtonEnabled(true);
    mSearchUnicodeLineEdit->setPlaceholderText(i18n("Search Emoticon..."));
    mainLayout->addWidget(mSearchUnicodeLineEdit);

    mCategoryButtons->setObjectName(QStringLiteral("mCategoryButtons"));
    mainLayout->addWidget(mCategoryButtons);
    mEmoticonListView->setObjectName(QStringLiteral("mEmoticonListView"));
    mainLayout->addWidget(mEmoticonListView);

    mEmoticonProxyModel->setObjectName(QStringLiteral("mEmoticonProxyModel"));
    mEmoticonListView->setModel(mEmoticonProxyModel);
    connect(mEmoticonListView, &EmoticonListView::fontSizeChanged, mEmoticonListView, &EmoticonListView::setFontSize);
    connect(mEmoticonListView, &EmoticonListView::emojiItemSelected, this, &EmoticonTextEditSelector::slotItemSelected);
    connect(mCategoryButtons, &EmoticonCategoryButtons::categorySelected, this, &EmoticonTextEditSelector::slotCategorySelected);
    connect(mSearchUnicodeLineEdit, &QLineEdit::textChanged, this, &EmoticonTextEditSelector::slotSearchUnicode);
    connect(TextEmoticonsCore::EmoticonUnicodeModelManager::self(),
            &TextEmoticonsCore::EmoticonUnicodeModelManager::usedIdentifierChanged,
            this,
            &EmoticonTextEditSelector::slotUsedIdentifierChanged);

    connect(mEmoticonListView, &EmoticonListView::clearRecents, this, []() {
        TextEmoticonsCore::EmoticonUnicodeModelManager::self()->setRecentIdentifier(QStringList());
    });

    const QSize popupMenuSize = QSize(400, 250) * screen()->devicePixelRatio();
    setMinimumSize(popupMenuSize);
}

EmoticonTextEditSelector::~EmoticonTextEditSelector() = default;

void EmoticonTextEditSelector::slotItemSelected(const QString &str, const QString &identifier)
{
    TextEmoticonsCore::EmoticonUnicodeModelManager::self()->addIdentifier(identifier);
    Q_EMIT itemSelected(str);
    if (isVisible() && parentWidget() && parentWidget()->inherits("QMenu")) {
        parentWidget()->close();
    }
}

void EmoticonTextEditSelector::loadEmoticons()
{
    if (!mCategoryButtons->wasLoaded()) {
        TextEmoticonsCore::UnicodeEmoticonManager *emojiManager = TextEmoticonsCore::UnicodeEmoticonManager::self();
        mEmoticonProxyModel->setSourceModel(TextEmoticonsCore::EmoticonUnicodeModelManager::self()->emoticonUnicodeModel());
        const QList<TextEmoticonsCore::EmoticonCategory> categories = emojiManager->categories();
        mCategoryButtons->setCategories(categories);
        mEmoticonProxyModel->setRecentEmoticons(TextEmoticonsCore::EmoticonUnicodeModelManager::self()->recentIdentifier());
    }
}

void EmoticonTextEditSelector::slotSearchUnicode(const QString &str)
{
    mEmoticonProxyModel->setSearchIdentifier(str);
}

void EmoticonTextEditSelector::slotUsedIdentifierChanged(const QStringList &lst)
{
    mEmoticonProxyModel->setRecentEmoticons(lst);
}

void EmoticonTextEditSelector::slotCategorySelected(const QString &category)
{
    mSearchUnicodeLineEdit->setText({});
    mEmoticonProxyModel->setCategory(category);
    mEmoticonListView->setIsRecentView(category == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier());
}
