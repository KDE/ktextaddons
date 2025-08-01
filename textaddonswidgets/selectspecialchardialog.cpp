/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "selectspecialchardialog.h"
using namespace Qt::Literals::StringLiterals;

#include <KCharSelect>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char mySelectSpecialCharDialogConfigGroupName[] = "SelectSpecialCharDialog";
}

namespace TextAddonsWidgets
{
class SelectSpecialCharDialogPrivate
{
public:
    explicit SelectSpecialCharDialogPrivate(SelectSpecialCharDialog *qq)
        : q(qq)
        , mCharSelect(new KCharSelect(q, nullptr, KCharSelect::CharacterTable | KCharSelect::BlockCombos))
        , mButtonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, q))
    {
        q->setWindowTitle(i18nc("@title:window", "Select Special Characters"));

        auto lay = new QVBoxLayout(q);

        q->connect(mCharSelect, &KCharSelect::charSelected, q, &SelectSpecialCharDialog::charSelected);
        lay->addWidget(mCharSelect);

        QPushButton *okButton = mButtonBox->button(QDialogButtonBox::Ok);
        okButton->setText(i18nc("@action:button", "Insert"));
        okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
        lay->addWidget(mButtonBox);
        q->connect(mButtonBox, &QDialogButtonBox::accepted, q, &QDialog::accept);
        q->connect(mButtonBox, &QDialogButtonBox::rejected, q, &QDialog::reject);

        q->connect(okButton, &QPushButton::clicked, q, [this]() {
            _k_slotInsertChar();
        });
    }

    void addSelectButton()
    {
        mSelectButton = new QPushButton(i18nc("@action:button", "Select"), q);
        mButtonBox->addButton(mSelectButton, QDialogButtonBox::ActionRole);
        q->connect(mSelectButton, &QPushButton::clicked, q, [this]() {
            _k_slotInsertChar();
        });
    }

    void _k_slotInsertChar();
    void readConfig();
    void writeConfig();

    SelectSpecialCharDialog *const q;
    KCharSelect *const mCharSelect;
    QDialogButtonBox *const mButtonBox;
    QPushButton *mSelectButton = nullptr;
};

void SelectSpecialCharDialogPrivate::readConfig()
{
    q->create(); // ensure a window is created
    q->windowHandle()->resize(QSize(300, 200));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(mySelectSpecialCharDialogConfigGroupName));
    KWindowConfig::restoreWindowSize(q->windowHandle(), group);
    q->resize(q->windowHandle()->size()); // workaround for QTBUG-40584
}

void SelectSpecialCharDialogPrivate::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(mySelectSpecialCharDialogConfigGroupName));
    KWindowConfig::saveWindowSize(q->windowHandle(), group);
}

void SelectSpecialCharDialogPrivate::_k_slotInsertChar()
{
    Q_EMIT q->charSelected(mCharSelect->currentChar());
}

SelectSpecialCharDialog::SelectSpecialCharDialog(QWidget *parent)
    : QDialog(parent)
    , d(new SelectSpecialCharDialogPrivate(this))
{
    d->readConfig();
}

SelectSpecialCharDialog::~SelectSpecialCharDialog()
{
    d->writeConfig();
}

void SelectSpecialCharDialog::showSelectButton(bool show)
{
    if (show) {
        d->addSelectButton();
    } else {
        d->mButtonBox->removeButton(d->mSelectButton);
    }
}

void SelectSpecialCharDialog::setCurrentChar(QChar c)
{
    d->mCharSelect->setCurrentChar(c);
}

QChar SelectSpecialCharDialog::currentChar() const
{
    return d->mCharSelect->currentChar();
}

void SelectSpecialCharDialog::autoInsertChar()
{
    connect(d->mCharSelect, &KCharSelect::charSelected, this, &SelectSpecialCharDialog::accept);
}

void SelectSpecialCharDialog::setOkButtonText(const QString &text)
{
    d->mButtonBox->button(QDialogButtonBox::Ok)->setText(text);
}
}

#include "moc_selectspecialchardialog.cpp"
