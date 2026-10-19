/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguretokenwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureTokenWidget::McpProtocolServerConfigureTokenWidget(QWidget *parent)
    : QWidget{parent}
    , mResultToken(new QLabel(this))
    , mRegenerateTokenButton(new QPushButton(this))
    , mCopyTokenButton(new QPushButton(QIcon::fromTheme(u"edit-copy"_s), i18nc("@action:button", "Copy"), this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Token:"), this);
    label->setObjectName(u"label"_s);
    mainLayout->addWidget(label);

    mResultToken->setObjectName(u"resultToken"_s);
    mResultToken->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    mainLayout->addWidget(mResultToken, 1);

    mRegenerateTokenButton->setObjectName(u"regenerateTokenButton"_s);
    connect(mRegenerateTokenButton, &QPushButton::clicked, this, &McpProtocolServerConfigureTokenWidget::slotRegenerateToken);
    mainLayout->addWidget(mRegenerateTokenButton);

    mCopyTokenButton->setObjectName(u"copyTokenButton"_s);
    mCopyTokenButton->setToolTip(i18nc("@info:tooltip", "Copy token to clipboard"));
    connect(mCopyTokenButton, &QPushButton::clicked, this, [this]() {
        QGuiApplication::clipboard()->setText(QString::fromLatin1(mAuthToken));
    });
    mainLayout->addWidget(mCopyTokenButton);

    updateButtons();
}

McpProtocolServerConfigureTokenWidget::~McpProtocolServerConfigureTokenWidget() = default;

void McpProtocolServerConfigureTokenWidget::setAuthToken(const QByteArray &token)
{
    if (mAuthToken != token) {
        mAuthToken = token;
        mResultToken->setText(QString::fromLatin1(mAuthToken));
        updateButtons();
        Q_EMIT authTokenChanged();
    }
}

QByteArray McpProtocolServerConfigureTokenWidget::authToken() const
{
    return mAuthToken;
}

void McpProtocolServerConfigureTokenWidget::slotRegenerateToken()
{
    if (!mAuthToken.isEmpty()
        && KMessageBox::warningContinueCancel(this,
                                              i18n("Clients which use the current token will not be able to connect until they are updated with the new one."),
                                              i18nc("@title:window", "Regenerate Token"),
                                              KGuiItem(i18nc("@action:button", "Regenerate")))
            != KMessageBox::Continue) {
        return;
    }
    setAuthToken(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::generateAuthToken());
}

void McpProtocolServerConfigureTokenWidget::updateButtons()
{
    const bool hasToken = !mAuthToken.isEmpty();
    mRegenerateTokenButton->setText(hasToken ? i18nc("@action:button", "Regenerate") : i18nc("@action:button", "Generate"));
    mCopyTokenButton->setEnabled(hasToken);
}

#include "moc_mcpprotocolserverconfiguretokenwidget.cpp"
