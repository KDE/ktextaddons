/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateheaderwidget.h"
#include "core/textautogeneratemanager.h"
#include "widgets/textautogeneratetextmodelcombobox.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateHeaderWidget::TextAutoGenerateHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mEngineName(new QLabel(this))
    , mNewChat(new QToolButton(this))
    , mFavorite(new QToolButton(this))
    , mSearch(new QToolButton(this))
    , mModelComboBox(new TextAutoGenerateTextModelComboBox(this))
    , mManager(manager)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mEngineName->setObjectName("mEngineName"_L1);
    mainLayout->addWidget(mEngineName);
    QFont f = mEngineName->font();
    f.setBold(true);
    f.setItalic(true);
    mEngineName->setFont(f);

    mainLayout->addWidget(mModelComboBox, 1);

    mSearch->setObjectName("mSearch"_L1);
    mSearch->setToolTip(i18nc("@info:tooltip", "Search…"));
    mSearch->setAutoRaise(true);
    mSearch->setIcon(QIcon::fromTheme(QStringLiteral("search")));
    mainLayout->addWidget(mSearch);
    connect(mSearch, &QToolButton::clicked, this, &TextAutoGenerateHeaderWidget::searchText);

    mNewChat->setObjectName("mNewChat"_L1);
    mNewChat->setToolTip(i18nc("@info:tooltip", "New Chat"));
    mNewChat->setAutoRaise(true);
    mNewChat->setIcon(QIcon::fromTheme(QStringLiteral("document-new")));
    mainLayout->addWidget(mNewChat);
    connect(mNewChat, &QToolButton::clicked, this, &TextAutoGenerateHeaderWidget::addNewChat);

    mFavorite->setObjectName("mFavorite"_L1);
    mFavorite->setToolTip(i18nc("@info:tooltip", "Favorite"));
    mFavorite->setAutoRaise(true);
    mFavorite->setCheckable(true);
    mFavorite->setIcon(QIcon::fromTheme(QStringLiteral("favorite")));
    mFavorite->setEnabled(false);
    mFavorite->setChecked(false);
    mainLayout->addWidget(mFavorite);
    connect(mFavorite, &QToolButton::clicked, this, [this](bool checked) {
        Q_EMIT changeFavoriteRequested(checked);
    });
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, &TextAutoGenerateHeaderWidget::slotCurrentChatIdChanged);
    }
}

TextAutoGenerateHeaderWidget::~TextAutoGenerateHeaderWidget() = default;

void TextAutoGenerateHeaderWidget::slotCurrentChatIdChanged()
{
    mFavorite->setEnabled(!mManager->currentChatId().isEmpty());
    mFavorite->setChecked(mManager->chatIsFavorite(mManager->currentChatId()));
}

void TextAutoGenerateHeaderWidget::updateEngineName(const QString &engineName)
{
    mEngineName->setText(engineName);
}

#include "moc_textautogenerateheaderwidget.cpp"
