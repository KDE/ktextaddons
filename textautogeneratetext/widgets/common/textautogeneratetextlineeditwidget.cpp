/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"

#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextplugin.h"
#include "widgets/common/textautogeneratetextlineedit.h"
#include "widgets/toolswidget/textautogeneratetoolswidget.h"
#include <KLocalizedString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMimeDatabase>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextLineEditWidget::TextAutoGenerateTextLineEditWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateTextLineEdit(new TextAutoGenerateTextLineEdit(this))
    , mTextAutoGenerateToolsWidget(new TextAutoGenerateToolsWidget(this))
    , mSendMessage(new QToolButton(this))
    , mAttachFile(new QToolButton(this))
    , mConfigureTools(new QToolButton(this))
    , mManager(manager)
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setObjectName(u"topLayout"_s);
    topLayout->setContentsMargins(QMargins{});
    topLayout->setSpacing(0);

    mTextAutoGenerateToolsWidget->setObjectName(u"mTextAutoGenerateToolsWidget"_s);
    topLayout->addWidget(mTextAutoGenerateToolsWidget);
    mTextAutoGenerateToolsWidget->setVisible(false);

    auto mainLayout = new QHBoxLayout;
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);
    topLayout->addLayout(mainLayout);

    mAttachFile->setObjectName(u"mAttachFile"_s);
    mAttachFile->setToolTip(i18nc("@info:tooltip", "Attach File"));
    mainLayout->addWidget(mAttachFile, 0, Qt::AlignTop);
    mAttachFile->setIcon(QIcon::fromTheme(u"mail-attachment-symbolic"_s));
    mAttachFile->setAutoRaise(true);
    // mAttachFile->setEnabled(false);

    connect(mAttachFile, &QToolButton::clicked, this, [this]() {
        const QString fileName = QFileDialog::getOpenFileName(this, i18nc("@title:window", "Select File"));
        if (!fileName.isEmpty()) {
            const QMimeDatabase db;
            const QMimeType mimeType = db.mimeTypeForFile(fileName);
            const QString mimeTypeName = mimeType.name();

            // TODO
        }
    });

    mTextAutoGenerateTextLineEdit->setObjectName(u"mTextAutoGenerateTextLineEdit"_s);
    mainLayout->addWidget(mTextAutoGenerateTextLineEdit, 0, Qt::AlignTop);
    mTextAutoGenerateTextLineEdit->setProperty("_breeze_borders_sides", QVariant::fromValue(QFlags{Qt::TopEdge}));

    mSendMessage->setObjectName(u"mSendMessage"_s);
    mainLayout->addWidget(mSendMessage, 0, Qt::AlignTop);
    mSendMessage->setToolTip(i18nc("@info:tooltip", "Send"));
    mSendMessage->setIcon(QIcon::fromTheme(u"document-send"_s));
    mSendMessage->setAutoRaise(true);

    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::sendMessage, this, [this](const QString &msg) {
        const QString str = msg.trimmed();
        mSendMessage->setEnabled(!str.isEmpty());
        if (!str.isEmpty()) {
            Q_EMIT editingFinished(str, mUuid, mTextAutoGenerateToolsWidget->generateListOfActiveTools());
            clearLineEdit();
        }
    });
    mSendMessage->setEnabled(false);

    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::textChanged, this, [this]() {
        mSendMessage->setEnabled(!mTextAutoGenerateTextLineEdit->document()->isEmpty());
    });

    connect(mSendMessage, &QToolButton::clicked, this, [this]() {
        Q_EMIT editingFinished(mTextAutoGenerateTextLineEdit->text(), mUuid, mTextAutoGenerateToolsWidget->generateListOfActiveTools());
        clearLineEdit();
    });
    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::keyPressed, this, &TextAutoGenerateTextLineEditWidget::keyPressed);
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::showArchiveChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::chatInProgressChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
        connect(mManager,
                &TextAutoGenerateText::TextAutoGenerateManager::currentModelChanged,
                this,
                &TextAutoGenerateTextLineEditWidget::slotCurrentModelChanged);
    }

    mConfigureTools->setObjectName(u"mConfigureTools"_s);
    mConfigureTools->setToolTip(i18nc("@info:tooltip", "Allow to select tools"));
    mainLayout->addWidget(mConfigureTools, 0, Qt::AlignTop);
    mConfigureTools->setIcon(QIcon::fromTheme(u"settings-configure"_s));
    mConfigureTools->setAutoRaise(true);
    mConfigureTools->setCheckable(true);
    connect(mConfigureTools, &QToolButton::clicked, this, [this]() {
        mTextAutoGenerateToolsWidget->setVisible(mConfigureTools->isChecked());
    });
}

TextAutoGenerateTextLineEditWidget::~TextAutoGenerateTextLineEditWidget() = default;

void TextAutoGenerateTextLineEditWidget::updateAttachmentButton(bool state)
{
    mAttachFile->setEnabled(state);
}

void TextAutoGenerateTextLineEditWidget::updateEnableState()
{
    setEnabled(!mManager->showArchived() && !mManager->chatInProgress(mManager->currentChatId()));
}

void TextAutoGenerateTextLineEditWidget::clearLineEdit()
{
    mTextAutoGenerateTextLineEdit->clear();
    mUuid.clear();
}

QString TextAutoGenerateTextLineEditWidget::text() const
{
    return mTextAutoGenerateTextLineEdit->text();
}

void TextAutoGenerateTextLineEditWidget::setText(const QString &str)
{
    mTextAutoGenerateTextLineEdit->setText(str);
}

QByteArray TextAutoGenerateTextLineEditWidget::uuid() const
{
    return mUuid;
}

void TextAutoGenerateTextLineEditWidget::setUuid(const QByteArray &newUuid)
{
    mUuid = newUuid;
}

void TextAutoGenerateTextLineEditWidget::setActivatedTools(const QList<QByteArray> &lst)
{
    mTextAutoGenerateToolsWidget->setActivatedTools(lst);
}

void TextAutoGenerateTextLineEditWidget::slotCurrentModelChanged()
{
    const bool hasToolsSupport = mManager->textAutoGeneratePlugin()->hasToolsSupport();
    mConfigureTools->setEnabled(hasToolsSupport);
    if (!hasToolsSupport) {
        mConfigureTools->setChecked(false);
        mTextAutoGenerateToolsWidget->setHidden(true);
    }
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
