/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mModelInstanceLabel->setObjectName(u"mModelInstanceLabel"_s);
    mainLayout->addWidget(mModelInstanceLabel);

    mModelComboBox->setObjectName(u"mModelComboBox"_s);
    mainLayout->addWidget(mModelComboBox, 1);

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

    auto saveQuickAskButton = new QToolButton(this);
    saveQuickAskButton->setAutoRaise(true);
    saveQuickAskButton->setObjectName(u"saveQuickAskButton"_s);
    saveQuickAskButton->setIcon(QIcon::fromTheme(u"document-import"_s));
    saveQuickAskButton->setToolTip(i18nc("@info:tooltip", "Save Quick Ask in Database"));
    mainLayout->addWidget(saveQuickAskButton);

    QFont f = mModelInstanceLabel->font();
    f.setBold(true);
    f.setItalic(true);
    mModelInstanceLabel->setFont(f);

    connect(clearButton, &QToolButton::clicked, this, [this]() {
        if (!mManager->currentChatId().isEmpty()) {
            if (auto messageModel = mManager->messagesModelFromChatId(mManager->currentChatId()); messageModel) {
                messageModel->resetConversation();
            }
        }
    });

    connect(configureButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::configureRequested);
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::loadEngineDone, this, [this]() {
        updateEngineModelName(mManager->generateEngineDisplayName());
    });
    connect(mModelComboBox, &TextAutoGenerateTextModelComboBox::activated, this, [this]() {
        mManager->textAutoGeneratePlugin()->setCurrentModel(mModelComboBox->currentModel());
    });
    connect(saveQuickAskButton, &QToolButton::clicked, this, [this]() {
        mManager->saveCurrentChatInDataBase(mManager->currentChatId());
    });
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
    mModelComboBox->setCurrentModel(mManager->textAutoGeneratePlugin()->currentModel());
}

QString TextAutoGenerateQuickAskHeaderWidget::currentModel() const
{
    return mModelComboBox->currentModel();
}

#include "moc_textautogeneratequickaskheaderwidget.cpp"
