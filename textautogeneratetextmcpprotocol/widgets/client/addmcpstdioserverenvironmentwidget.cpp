/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverenvironmentwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStdioServerEnvironmentWidget::AddMcpStdioServerEnvironmentWidget(QWidget *parent)
    : QWidget{parent}
    , mTableWidget(new QTableWidget(0, 2, this))
    , mRemoveButton(new QPushButton(i18nc("@action:button", "Remove"), this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mTableWidget->setObjectName(u"mTableWidget"_s);
    mTableWidget->setHorizontalHeaderLabels({i18nc("@title:column", "Name"), i18nc("@title:column", "Value")});
    mTableWidget->horizontalHeader()->setStretchLastSection(true);
    mTableWidget->verticalHeader()->setVisible(false);
    mTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mTableWidget->setToolTip(i18nc("@info:tooltip", "An empty value keeps the variable from the user environment."));
    mainLayout->addWidget(mTableWidget);

    auto buttonsLayout = new QVBoxLayout;
    buttonsLayout->setObjectName(u"buttonsLayout"_s);
    buttonsLayout->setContentsMargins(QMargins{});

    auto addButton = new QPushButton(i18nc("@action:button", "Add"), this);
    addButton->setObjectName(u"addButton"_s);
    buttonsLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &AddMcpStdioServerEnvironmentWidget::slotAddEnvironment);

    mRemoveButton->setObjectName(u"mRemoveButton"_s);
    buttonsLayout->addWidget(mRemoveButton);
    buttonsLayout->addStretch(1);
    connect(mRemoveButton, &QPushButton::clicked, this, &AddMcpStdioServerEnvironmentWidget::slotRemoveEnvironment);
    mainLayout->addLayout(buttonsLayout);

    connect(mTableWidget, &QTableWidget::itemSelectionChanged, this, &AddMcpStdioServerEnvironmentWidget::updateButtons);
    updateButtons();
}

AddMcpStdioServerEnvironmentWidget::~AddMcpStdioServerEnvironmentWidget() = default;

void AddMcpStdioServerEnvironmentWidget::updateButtons()
{
    mRemoveButton->setEnabled(!mTableWidget->selectedItems().isEmpty());
}

void AddMcpStdioServerEnvironmentWidget::addRow(const QString &name, const QString &value)
{
    const int row = mTableWidget->rowCount();
    mTableWidget->insertRow(row);
    mTableWidget->setItem(row, 0, new QTableWidgetItem(name));
    mTableWidget->setItem(row, 1, new QTableWidgetItem(value));
}

void AddMcpStdioServerEnvironmentWidget::slotAddEnvironment()
{
    addRow({}, {});
    const int row = mTableWidget->rowCount() - 1;
    mTableWidget->setCurrentCell(row, 0);
    mTableWidget->editItem(mTableWidget->item(row, 0));
}

void AddMcpStdioServerEnvironmentWidget::slotRemoveEnvironment()
{
    const int row = mTableWidget->currentRow();
    if (row < 0) {
        return;
    }
    mTableWidget->removeRow(row);
    updateButtons();
}

QMap<QString, QString> AddMcpStdioServerEnvironmentWidget::environments() const
{
    QMap<QString, QString> envs;
    for (int row = 0; row < mTableWidget->rowCount(); ++row) {
        const QTableWidgetItem *nameItem = mTableWidget->item(row, 0);
        // '=' is the separator used to store environment in config
        const QString name = nameItem ? nameItem->text().trimmed() : QString();
        if (name.isEmpty() || name.contains(u'=')) {
            continue;
        }
        const QTableWidgetItem *valueItem = mTableWidget->item(row, 1);
        envs.insert(name, valueItem ? valueItem->text() : QString());
    }
    return envs;
}

void AddMcpStdioServerEnvironmentWidget::setEnvironments(const QMap<QString, QString> &environments)
{
    mTableWidget->setRowCount(0);
    for (auto it = environments.cbegin(); it != environments.cend(); ++it) {
        addRow(it.key(), it.value());
    }
    updateButtons();
}

#include "moc_addmcpstdioserverenvironmentwidget.cpp"
