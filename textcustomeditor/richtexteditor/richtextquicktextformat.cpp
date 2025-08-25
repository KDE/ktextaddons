/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextquicktextformat.h"

#include <KLocalizedString>

#include <QEvent>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTimer>
#include <QToolButton>

#include <chrono>
using namespace std::chrono_literals;

using namespace Qt::Literals::StringLiterals;
using namespace TextCustomEditor;
RichTextQuickTextFormat::RichTextQuickTextFormat(QTextEdit *editor, QWidget *parent)
    : QFrame(parent)
    , mEditor(editor)
    , mUpdatePositionTimer(new QTimer(this))
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    setFocusPolicy(Qt::NoFocus);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    auto boldButton = new QToolButton(this);
    boldButton->setFocusPolicy(Qt::NoFocus);
    boldButton->setObjectName(u"boldButton"_s);
    boldButton->setIconSize(QSize(12, 12));
    boldButton->setIcon(QIcon::fromTheme(u"format-text-bold"_s));
    boldButton->setAutoRaise(true);
    boldButton->setToolTip(i18nc("@info:tooltip", "Bold"));
    mainLayout->addWidget(boldButton);
    connect(boldButton, &QToolButton::clicked, this, [this]() {
        Q_EMIT quickTextFormatRequested(TextCustomEditor::RichTextQuickTextFormat::QuickTextFormatType::Bold);
    });
    if (mEditor) {
        connect(mEditor, &QTextEdit::selectionChanged, this, &RichTextQuickTextFormat::updatePosition);
        mUpdatePositionTimer->setInterval(20ms);
        mUpdatePositionTimer->setSingleShot(true);
        connect(mUpdatePositionTimer, &QTimer::timeout, this, &RichTextQuickTextFormat::updatePosition);
        mEditor->viewport()->installEventFilter(this);
    }
}

RichTextQuickTextFormat::~RichTextQuickTextFormat() = default;

void RichTextQuickTextFormat::updatePosition()
{
    if (mEditor->textCursor().hasSelection()) {
        const QRect cursorRect = mEditor->cursorRect();
        const QPoint globalPos = mEditor->viewport()->mapToGlobal(cursorRect.topLeft());
        move(globalPos.x(), globalPos.y() - height());
        show();
    } else {
        hide();
    }
}

bool RichTextQuickTextFormat::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == mEditor->viewport()) {
        if (event->type() == QEvent::Move || event->type() == QEvent::Resize) {
            if (isVisible()) {
                if (mUpdatePositionTimer->isActive()) {
                    mUpdatePositionTimer->stop();
                }
                mUpdatePositionTimer->start();
            }
        }
    }
    return QFrame::eventFilter(watched, event);
}

#include "moc_richtextquicktextformat.cpp"
