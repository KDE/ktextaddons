/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticontexteditselector.h"
using namespace Qt::Literals::StringLiterals;

#include "emoticoncategorybuttons.h"
#include "emoticonlistview.h"
#include "emoticontonecombobox.h"

#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <TextEmoticonsCore/EmojiModel>
#include <TextEmoticonsCore/EmojiModelManager>
#include <TextEmoticonsCore/EmojiSortFilterProxyModel>
#include <TextEmoticonsCore/EmoticonUnicodeUtils>
#include <TextEmoticonsCore/UnicodeEmoticonManager>

using namespace TextEmoticonsWidgets;

class EmoticonTextEditSelector::EmoticonTextEditSelectorPrivate
{
public:
    explicit EmoticonTextEditSelectorPrivate(EmoticonTextEditSelector *q)
        : searchUnicodeLineEdit(new QLineEdit(q))
        , categoryButtons(new EmoticonCategoryButtons(q))
        , emoticonListView(new EmoticonListView(q))
        , emoticonToneComboBox(new EmoticonToneComboBox(q))
        , emojiSortFilterProxyModel(new TextEmoticonsCore::EmojiSortFilterProxyModel(q))
        , qq(q)
    {
    }
    void slotUsedIdentifierChanged(const QStringList &lst)
    {
        emojiSortFilterProxyModel->setRecentEmoticons(lst);
    }
    void slotCategorySelected(const QString &category)
    {
        searchUnicodeLineEdit->setText({});
        emojiSortFilterProxyModel->setCategory(category);
        emoticonListView->setIsRecentView(category == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier());
    }

    void slotSearchUnicode(const QString &str)
    {
        emojiSortFilterProxyModel->setSearchIdentifier(str);
    }

    void slotItemSelected(const QString &str, const QString &identifier)
    {
        TextEmoticonsCore::EmojiModelManager::self()->addIdentifier(identifier);
        Q_EMIT qq->insertEmoji(str);
        Q_EMIT qq->insertEmojiIdentifier(identifier);
        if (qq->isVisible() && qq->parentWidget() && qq->parentWidget()->inherits("QMenu")) {
            qq->parentWidget()->close();
        }
    }

    QLineEdit *const searchUnicodeLineEdit;
    EmoticonCategoryButtons *const categoryButtons;
    EmoticonListView *const emoticonListView;
    EmoticonToneComboBox *const emoticonToneComboBox;
    TextEmoticonsCore::EmojiSortFilterProxyModel *const emojiSortFilterProxyModel;
    bool customEmojiSupport = false;
    EmoticonTextEditSelector *const qq;
};

EmoticonTextEditSelector::EmoticonTextEditSelector(QWidget *parent)
    : QWidget(parent)
    , d(new EmoticonTextEditSelectorPrivate(this))
{
    const int defaultFontSize{22};
    QFont f;
    f.setPointSize(defaultFontSize);
    f.setFamily(TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
    d->emoticonListView->setFontSize(defaultFontSize);
    d->categoryButtons->setFont(f);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins({});

    auto hLayout = new QHBoxLayout;
    hLayout->setContentsMargins({});
    mainLayout->addLayout(hLayout);

    d->searchUnicodeLineEdit->setObjectName(u"mSearchUnicodeLineEdit"_s);
    d->searchUnicodeLineEdit->setClearButtonEnabled(true);
    d->searchUnicodeLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search Emoticon…"));
    hLayout->addWidget(d->searchUnicodeLineEdit);
    d->emoticonToneComboBox->setObjectName(u"emoticonToneComboBox"_s);
    hLayout->addWidget(d->emoticonToneComboBox);
    d->emoticonToneComboBox->setCurrentEmojiTone(TextEmoticonsCore::EmojiModelManager::self()->emojiTone());

    d->categoryButtons->setObjectName(u"mCategoryButtons"_s);
    mainLayout->addWidget(d->categoryButtons);
    d->emoticonListView->setObjectName(u"mEmoticonListView"_s);
    mainLayout->addWidget(d->emoticonListView);

    d->emojiSortFilterProxyModel->setObjectName(u"mEmoticonProxyModel"_s);
    d->emoticonListView->setModel(d->emojiSortFilterProxyModel);
    connect(d->emoticonListView, &EmoticonListView::fontSizeChanged, d->emoticonListView, &EmoticonListView::setFontSize);
    connect(d->emoticonListView, &EmoticonListView::emojiItemSelected, this, [this](const QString &str, const QString &identifier) {
        d->slotItemSelected(str, identifier);
    });
    connect(d->categoryButtons, &EmoticonCategoryButtons::categorySelected, this, [this](const QString &category) {
        d->slotCategorySelected(category);
    });
    connect(d->searchUnicodeLineEdit, &QLineEdit::textChanged, this, [this](const QString &str) {
        d->slotSearchUnicode(str);
    });
    connect(TextEmoticonsCore::EmojiModelManager::self(), &TextEmoticonsCore::EmojiModelManager::usedIdentifierChanged, this, [this](const QStringList &lst) {
        d->slotUsedIdentifierChanged(lst);
    });

    connect(d->emoticonListView, &EmoticonListView::clearHistory, this, []() {
        TextEmoticonsCore::EmojiModelManager::self()->setRecentIdentifier(QStringList());
    });

    connect(d->emoticonToneComboBox, &TextEmoticonsWidgets::EmoticonToneComboBox::currentIndexChanged, this, [this]() {
        TextEmoticonsCore::EmojiModelManager::self()->setEmojiTone(d->emoticonToneComboBox->currentEmojiTone());
    });

    connect(TextEmoticonsCore::EmojiModelManager::self(), &TextEmoticonsCore::EmojiModelManager::emojiToneChanged, this, [this]() {
        d->emojiSortFilterProxyModel->setEmojiTone(TextEmoticonsCore::EmojiModelManager::self()->emojiTone());
    });

    d->emojiSortFilterProxyModel->setEmojiTone(TextEmoticonsCore::EmojiModelManager::self()->emojiTone());
    const QSize popupMenuSize = QSize(400, 250);
    setMinimumSize(popupMenuSize);
}

void EmoticonTextEditSelector::forceLineEditFocus()
{
    d->searchUnicodeLineEdit->setFocus();
}

EmoticonTextEditSelector::~EmoticonTextEditSelector() = default;

void EmoticonTextEditSelector::loadEmoticons()
{
    if (!d->categoryButtons->wasLoaded()) {
        TextEmoticonsCore::UnicodeEmoticonManager *emojiManager = TextEmoticonsCore::UnicodeEmoticonManager::self();
        d->emojiSortFilterProxyModel->setSourceModel(TextEmoticonsCore::EmojiModelManager::self()->emojiModel());
        const QList<TextEmoticonsCore::EmoticonCategory> categories = emojiManager->categories();
        d->categoryButtons->setCategories(categories, d->customEmojiSupport);
        d->emojiSortFilterProxyModel->setRecentEmoticons(TextEmoticonsCore::EmojiModelManager::self()->recentIdentifier());
    }
}

void EmoticonTextEditSelector::setCustomEmojiSupport(bool b)
{
    d->customEmojiSupport = b;
}

bool EmoticonTextEditSelector::customEmojiSupport() const
{
    return d->customEmojiSupport;
}

#include "moc_emoticontexteditselector.cpp"
