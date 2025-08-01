/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textgotolinewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QIcon>
#include <QPushButton>

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QSpinBox>
#include <QToolButton>

using namespace TextCustomEditor;

class Q_DECL_HIDDEN TextCustomEditor::TextGoToLineWidgetPrivate
{
public:
    TextGoToLineWidgetPrivate() = default;

    QSpinBox *mSpinbox = nullptr;
    QPushButton *mGoToLine = nullptr;
};

TextGoToLineWidget::TextGoToLineWidget(QWidget *parent)
    : QWidget(parent)
    , d(new TextCustomEditor::TextGoToLineWidgetPrivate)
{
    auto hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(2, 2, 2, 2);
    auto closeBtn = new QToolButton(this);
    closeBtn->setIcon(QIcon::fromTheme(u"dialog-close"_s));
    closeBtn->setIconSize(QSize(16, 16));
    closeBtn->setToolTip(i18nc("@info:tooltip", "Close"));
    closeBtn->setObjectName(u"closebutton"_s);
#ifndef QT_NO_ACCESSIBILITY
    closeBtn->setAccessibleName(i18n("Close"));
#endif

    closeBtn->setAutoRaise(true);
    connect(closeBtn, &QToolButton::clicked, this, &TextGoToLineWidget::slotCloseBar);
    hbox->addWidget(closeBtn);

    auto lab = new QLabel(i18nc("@label:textbox", "Go to Line:"));
    lab->setTextFormat(Qt::PlainText);
    hbox->addWidget(lab);
    d->mSpinbox = new QSpinBox(this);
    d->mSpinbox->setMinimum(1);
    d->mSpinbox->setObjectName(u"line"_s);
    connect(d->mSpinbox, &QSpinBox::editingFinished, this, &TextGoToLineWidget::slotGoToLine);
    hbox->addWidget(d->mSpinbox);
    d->mGoToLine = new QPushButton(QIcon::fromTheme(u"go-jump"_s), i18n("Go"));
    d->mGoToLine->setFlat(true);
    connect(d->mGoToLine, &QPushButton::clicked, this, &TextGoToLineWidget::slotGoToLine);
    d->mGoToLine->setObjectName(u"gotoline"_s);
    hbox->addWidget(d->mGoToLine);
    hbox->addStretch();
    d->mSpinbox->setFocus();
    d->mSpinbox->installEventFilter(this);
}

TextGoToLineWidget::~TextGoToLineWidget()
{
    // mSpinbox can emit signals from its dtor, which are connected to this object
    // so we need to make sure these connections are removed before we destroy ourselves
    delete d->mSpinbox;
}

bool TextGoToLineWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == d->mSpinbox) {
        if (event->type() == QEvent::KeyPress) {
            auto e = static_cast<QKeyEvent *>(event);
            if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
                slotGoToLine();
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void TextGoToLineWidget::setMaximumLineCount(int max)
{
    d->mSpinbox->setMaximum(max);
}

void TextGoToLineWidget::goToLine()
{
    show();
    d->mSpinbox->setFocus();
    d->mSpinbox->selectAll();
}

void TextGoToLineWidget::slotGoToLine()
{
    Q_EMIT moveToLine(d->mSpinbox->value());
}

void TextGoToLineWidget::showEvent(QShowEvent *e)
{
    if (!e->spontaneous()) {
        d->mSpinbox->setFocus();
    }
    QWidget::showEvent(e);
}

void TextGoToLineWidget::slotBlockCountChanged(int numberBlockCount)
{
    if (!isHidden()) {
        setMaximumLineCount(numberBlockCount);
    }
}

void TextGoToLineWidget::slotCloseBar()
{
    hide();
    Q_EMIT hideGotoLine();
}

bool TextGoToLineWidget::event(QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    const bool shortCutOverride = (e->type() == QEvent::ShortcutOverride);
    if (shortCutOverride || e->type() == QEvent::KeyPress) {
        auto kev = static_cast<QKeyEvent *>(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseBar();
            return true;
        }
    }
    return QWidget::event(e);
}

#include "moc_textgotolinewidget.cpp"
