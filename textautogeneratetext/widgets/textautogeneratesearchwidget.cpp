/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchwidget.h"
#include "core/textautogeneratesearchjob.h"
#include "textautogeneratesearchlineedit.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateSearchWidget::TextAutoGenerateSearchWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateSearchListView(new TextAutoGenerateSearchListView(manager, this))
    , mSearchLineEdit(new TextAutoGenerateSearchLineEdit(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->addAction(QIcon::fromTheme(QStringLiteral("view-filter")), QLineEdit::LeadingPosition);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);

    mTextAutoGenerateSearchListView->setObjectName(QStringLiteral("mTextAutoGenerateSearchListView"));
    mainLayout->addWidget(mTextAutoGenerateSearchListView);

    connect(mSearchLineEdit, &TextAutoGenerateSearchLineEdit::searchText, this, &TextAutoGenerateSearchWidget::slotSearchTextChanged);
}

TextAutoGenerateSearchWidget::~TextAutoGenerateSearchWidget() = default;

void TextAutoGenerateSearchWidget::slotSearchTextChanged(const QString &str)
{
    TextAutoGenerateSearchJob *job = new TextAutoGenerateSearchJob(mManager, this);
    job->setSearchText(str);
    connect(job, &TextAutoGenerateSearchJob::searchDone, this, &TextAutoGenerateSearchWidget::slotSearchDone);
    job->start();
    qDebug() << " Str " << str;
}

void TextAutoGenerateSearchWidget::slotSearchDone(const QList<TextAutoGenerateSearchMessage> &msgs)
{
    mTextAutoGenerateSearchListView->setSearchMessages(msgs);
}

#include "moc_textautogeneratesearchwidget.cpp"
