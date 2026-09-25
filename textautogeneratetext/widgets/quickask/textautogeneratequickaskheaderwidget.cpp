/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidget.h"
#include <QLabel>

#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "widgets/common/textautogeneratetextmodelcombobox.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskHeaderWidget::TextAutoGenerateQuickAskHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mModelInstanceLabel(new QLabel(this))
    , mModelComboBox(new TextAutoGenerateText::TextAutoGenerateTextModelComboBox(this))
    , mManager(manager)
    , mSearchButton(new QToolButton(this))
    , mSaveQuickAskButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mModelInstanceLabel->setObjectName(u"mModelInstanceLabel"_s);
    mainLayout->addWidget(mModelInstanceLabel);

    mModelComboBox->setObjectName(u"mModelComboBox"_s);
    mainLayout->addWidget(mModelComboBox, 1);

    mSearchButton->setObjectName("searchButton"_L1);
    mSearchButton->setToolTip(i18nc("@info:tooltip", "Search…"));
    mSearchButton->setAutoRaise(true);
    mSearchButton->setCheckable(true);
    mSearchButton->setIcon(QIcon::fromTheme(u"search"_s));
    mainLayout->addWidget(mSearchButton);
    connect(mSearchButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::searchText);

    auto showInternaltoolsButton = new QToolButton(this);
    showInternaltoolsButton->setAutoRaise(true);
    showInternaltoolsButton->setObjectName(u"showInternaltoolsButton"_s);
    showInternaltoolsButton->setIcon(QIcon::fromTheme(u"documentinfo"_s));
    showInternaltoolsButton->setToolTip(i18nc("@info:tooltip", "Show internal tools…"));
    mainLayout->addWidget(showInternaltoolsButton);

    auto configureButton = new QToolButton(this);
    configureButton->setAutoRaise(true);
    configureButton->setObjectName(u"configureButton"_s);
    configureButton->setIcon(QIcon::fromTheme(u"settings-configure"_s));
    configureButton->setToolTip(i18nc("@info:tooltip", "Configure…"));
    mainLayout->addWidget(configureButton);

    auto clearButton = new QToolButton(this);
    clearButton->setAutoRaise(true);
    clearButton->setObjectName(u"clearButton"_s);
    clearButton->setIcon(QIcon::fromTheme(u"edit-clear-all"_s));
    clearButton->setToolTip(i18nc("@info:tooltip", "Clear"));
    mainLayout->addWidget(clearButton);

    mSaveQuickAskButton->setAutoRaise(true);
    mSaveQuickAskButton->setObjectName(u"saveQuickAskButton"_s);
    mSaveQuickAskButton->setIcon(QIcon::fromTheme(u"document-import"_s));
    mSaveQuickAskButton->setEnabled(false);
    mSaveQuickAskButton->setToolTip(i18nc("@info:tooltip", "Save Discussion in Database"));
    mainLayout->addWidget(mSaveQuickAskButton);

    QFont f = mModelInstanceLabel->font();
    f.setBold(true);
    f.setItalic(true);
    mModelInstanceLabel->setFont(f);

    connect(configureButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::configureRequested);
    if (mManager) {
        connect(clearButton, &QToolButton::clicked, this, [this]() {
            if (!mChatId.isEmpty()) {
                if (auto messageModel = mManager->messagesModelFromChatId(mChatId); messageModel) {
                    messageModel->resetConversation();
                }
            }
        });

        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, [this]() {
            updateEngineModelName(mManager->generateEngineDisplayName());
        });
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::loadEngineDone, this, [this]() {
            updateEngineModelName(mManager->generateEngineDisplayName());
        });
        connect(mModelComboBox, &TextAutoGenerateTextModelComboBox::activated, this, [this]() {
            if (mManager) {
                mManager->textAutoGeneratePlugin()->setCurrentModel(mModelComboBox->currentModel());
            }
        });
        connect(mSaveQuickAskButton, &QToolButton::clicked, this, [this]() {
            mManager->saveCurrentChatInDataBase(mChatId);
        });
        connect(showInternaltoolsButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::showInternalToolsMetaData);
        showInternaltoolsButton->setVisible(mManager->textAutoGenerateTextToolInternalInterface());
    } else {
        showInternaltoolsButton->hide();
    }
}

TextAutoGenerateQuickAskHeaderWidget::~TextAutoGenerateQuickAskHeaderWidget() = default;

void TextAutoGenerateQuickAskHeaderWidget::updateEngineModelName(const QString &str)
{
    mModelInstanceLabel->setText(str);
}

void TextAutoGenerateQuickAskHeaderWidget::setModelList(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst)
{
    mModelComboBox->setModelList(lst);
    // Initialize current Model
    if (mManager) {
        mModelComboBox->setCurrentModel(mManager->textAutoGeneratePlugin()->currentModel());
    }
}

QString TextAutoGenerateQuickAskHeaderWidget::currentModel() const
{
    return mModelComboBox->currentModel();
}

void TextAutoGenerateQuickAskHeaderWidget::setChatId(const QByteArray &chatId)
{
    mChatId = chatId;
    mSaveQuickAskButton->setEnabled(!mChatId.isEmpty());
}

void TextAutoGenerateQuickAskHeaderWidget::slotCloseQuickSearchRequested()
{
    mSearchButton->setChecked(false);
}

#include "moc_textautogeneratequickaskheaderwidget.cpp"
