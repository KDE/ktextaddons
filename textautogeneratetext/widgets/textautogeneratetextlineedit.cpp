/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineedit.h"
#include <KLineEditEventHandler>
#include <QAbstractTextDocumentLayout>

using namespace TextAutogenerateText;
TextAutogenerateTextLineEdit::TextAutogenerateTextLineEdit(QWidget *parent)
    : KTextEdit(parent)
{
    KLineEditEventHandler::catchReturnKey(this);
    setTabChangesFocus(true);
    setAcceptRichText(false);
    enableFindReplace(false); // not needed here, let's instead make sure the Ctrl+F shortcut will search through channel history
    connect(document()->documentLayout(), &QAbstractTextDocumentLayout::documentSizeChanged, this, &QWidget::updateGeometry);
}

TextAutogenerateTextLineEdit::~TextAutogenerateTextLineEdit() = default;

QString TextAutogenerateTextLineEdit::text() const
{
    return toPlainText();
}

void TextAutogenerateTextLineEdit::keyPressEvent(QKeyEvent *e)
{
    const int key = e->key();

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        if ((key == Qt::Key_Enter && (e->modifiers() == Qt::KeypadModifier)) || !e->modifiers()) {
            Q_EMIT sendMessage(text());
            clear();
        } else {
            textCursor().insertBlock();
            ensureCursorVisible();
        }
        e->accept();
        return;
    } else if (key == Qt::Key_Up || key == Qt::Key_Down) {
        if (!(e->modifiers() & Qt::AltModifier)) {
            // document()->lineCount() is > 1 if the user used Shift+Enter
            // firstBlockLayout->lineCount() is > 1 if a single long line wrapped around
            const QTextLayout *firstBlockLayout = document()->firstBlock().layout();
            if (document()->lineCount() > 1 || firstBlockLayout->lineCount() > 1) {
                KTextEdit::keyPressEvent(e);
                return;
            }
        }
    }
    e->ignore();
    // Assign key to KTextEdit first otherwise text() doesn't return correct text
    KTextEdit::keyPressEvent(e);
}

QSize TextAutogenerateTextLineEdit::sizeHint() const
{
    // The width of the QTextDocument is the current widget width, so this is somewhat circular logic.
    // But I don't really want to redo the layout with a different width like idealWidth(), seems slow.
    const QSize docSize = document()->size().toSize();
    const int margin = int(document()->documentMargin());
    return {docSize.width() + margin, qMin(300, docSize.height()) + margin};
}

QSize TextAutogenerateTextLineEdit::minimumSizeHint() const
{
    const int margin = int(document()->documentMargin());
    return {300, fontMetrics().height() + margin};
}

#include "moc_textautogeneratetextlineedit.cpp"
