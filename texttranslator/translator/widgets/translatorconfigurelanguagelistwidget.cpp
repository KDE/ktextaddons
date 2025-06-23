/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurelanguagelistwidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QVBoxLayout>
using namespace TextTranslator;

TranslatorConfigureLanguageListWidget::TranslatorConfigureLanguageListWidget(const QString &labelText, QWidget *parent)
    : QWidget{parent}
    , mLanguageListWidget(new QListView(this))
    , mListSearchLine(new QLineEdit(this))
    , mLabel(new QLabel(labelText, this))
    , mModel(new QStandardItemModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(u"mainLayout"_s);

    mLabel->setObjectName(u"mLabel"_s);
    mainLayout->addWidget(mLabel);

    mModel->setObjectName(u"mModel"_s);

    mListSearchLine->setObjectName(u"mListSearchLine"_s);
    mainLayout->addWidget(mListSearchLine);
    mListSearchLine->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    auto filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    filterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    filterProxyModel->setSourceModel(mModel);
    connect(mListSearchLine, &QLineEdit::textChanged, this, [filterProxyModel](const QString &str) {
        filterProxyModel->setFilterFixedString(str);
    });

    mLanguageListWidget->setObjectName(u"mLanguageListWidget"_s);
    mainLayout->addWidget(mLanguageListWidget);
    mLanguageListWidget->setModel(filterProxyModel);
    KLineEditEventHandler::catchReturnKey(mListSearchLine);
}

TranslatorConfigureLanguageListWidget::~TranslatorConfigureLanguageListWidget() = default;

void TranslatorConfigureLanguageListWidget::clear()
{
    mModel->clear();
}

void TranslatorConfigureLanguageListWidget::addItem(const QString &translatedStr, const QString &languageCode)
{
    QStandardItem *item = new QStandardItem();
    item->setText(translatedStr);
    item->setData(languageCode, LanguageCode);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setEditable(false);
    item->setCheckState(Qt::Unchecked);
    mModel->appendRow(item);
}

QStringList TranslatorConfigureLanguageListWidget::selectedLanguages() const
{
    QStringList langs;
    for (int i = 0; i < mModel->rowCount(); ++i) {
        const auto item = mModel->item(i);
        if (item->checkState() == Qt::Checked) {
            langs.append(item->data(LanguageCode).toString());
        }
    }
    return langs;
}

void TranslatorConfigureLanguageListWidget::setSelectedLanguages(const QStringList &list)
{
    for (int i = 0, total = mModel->rowCount(); i < total; ++i) {
        const auto item = mModel->item(i);
        item->setCheckState(list.contains(item->data(LanguageCode).toString()) ? Qt::Checked : Qt::Unchecked);
    }
}

#include "moc_translatorconfigurelanguagelistwidget.cpp"
