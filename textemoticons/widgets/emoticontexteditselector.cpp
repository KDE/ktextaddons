/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontexteditselector.h"
#include "emoticoncategorybuttons.h"
#include "emoticonlistview.h"
#include "emoticonunicodemodel.h"
#include "emoticonunicodemodelmanager.h"
#include "emoticonunicodeproxymodel.h"

#include <KLocalizedString>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

#include <QLineEdit>
#include <QVBoxLayout>

using namespace TextEmoticonsWidgets;

QString emojiFontName()
{
#ifdef Q_OS_WIN
    return QStringLiteral("Segoe UI Emoji");
#else
    return QStringLiteral("NotoColorEmoji");
#endif
}

EmoticonTextEditSelector::EmoticonTextEditSelector(QWidget *parent)
    : QWidget(parent)
    , mCategoryButtons(new EmoticonCategoryButtons(this))
    , mSearchUnicodeLineEdit(new QLineEdit(this))
    , mEmoticonListView(new EmoticonListView(this))
    , mEmoticonProxyModel(new EmoticonUnicodeProxyModel(this))
{
    QFont f;
    f.setPointSize(22);
    // TODO fix me
    // f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    f.setFamily(emojiFontName());
    mEmoticonListView->setFont(f);
    mCategoryButtons->setFont(f);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins({});
    mSearchUnicodeLineEdit->setObjectName(QStringLiteral("mSearchUnicodeLineEdit"));
    mSearchUnicodeLineEdit->setClearButtonEnabled(true);
    mSearchUnicodeLineEdit->setPlaceholderText(i18n("Search Emoticon..."));
    mainLayout->addWidget(mSearchUnicodeLineEdit);

    mainLayout->addWidget(mCategoryButtons);
    mEmoticonListView->setObjectName(QStringLiteral("mEmoticonListView"));
    mainLayout->addWidget(mEmoticonListView);

    mEmoticonProxyModel->setObjectName(QStringLiteral("mEmoticonProxyModel"));
    mEmoticonListView->setModel(mEmoticonProxyModel);
    connect(mEmoticonListView, &EmoticonListView::emojiItemSelected, this, &EmoticonTextEditSelector::slotItemSelected);
    connect(mCategoryButtons, &EmoticonCategoryButtons::categorySelected, this, &EmoticonTextEditSelector::slotCategorySelected);
    connect(mSearchUnicodeLineEdit, &QLineEdit::textChanged, this, &EmoticonTextEditSelector::slotSearchUnicode);
    setMinimumSize(400, 200);
    loadEmoticons();
}

EmoticonTextEditSelector::~EmoticonTextEditSelector() = default;

void EmoticonTextEditSelector::slotItemSelected(const QString &str, const QString &identifier)
{
    // TODO use identifier
    Q_EMIT itemSelected(str);
    if (isVisible() && parentWidget() && parentWidget()->inherits("QMenu")) {
        parentWidget()->close();
    }
}

void EmoticonTextEditSelector::loadEmoticons()
{
    TextEmoticonsCore::UnicodeEmoticonManager *emojiManager = TextEmoticonsCore::UnicodeEmoticonManager::self();
    mEmoticonProxyModel->setSourceModel(TextEmoticonsWidgets::EmoticonUnicodeModelManager::self()->emoticonUnicodeModel());
    const QList<TextEmoticonsCore::EmoticonCategory> categories = emojiManager->categories();
    mCategoryButtons->setCategories(categories);
}

void EmoticonTextEditSelector::slotSearchUnicode(const QString &str)
{
    // mUnicodeTab->searchUnicode(str);
}

void EmoticonTextEditSelector::slotCategorySelected(const QString &category)
{
    mEmoticonProxyModel->setCategory(category);
}
