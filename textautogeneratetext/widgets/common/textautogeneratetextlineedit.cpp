/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineedit.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QAbstractTextDocumentLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateTextLineEdit::TextAutoGenerateTextLineEdit(QWidget *parent)
    : KTextEdit(parent)
{
    setPlaceholderText(i18nc("@info:placeholder", "Enter a message"));
    KLineEditEventHandler::catchReturnKey(this);
    setTabChangesFocus(true);
    setAcceptRichText(false);
    enableFindReplace(false); // not needed here, let's instead make sure the Ctrl+F shortcut will search through channel history
    connect(document()->documentLayout(), &QAbstractTextDocumentLayout::documentSizeChanged, this, &QWidget::updateGeometry);
}

TextAutoGenerateTextLineEdit::~TextAutoGenerateTextLineEdit() = default;

QString TextAutoGenerateTextLineEdit::text() const
{
    return toPlainText();
}

void TextAutoGenerateTextLineEdit::keyPressEvent(QKeyEvent *e)
{
    const int key = e->key();

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        if ((key == Qt::Key_Enter && (e->modifiers() == Qt::KeypadModifier)) || !e->modifiers()) {
            Q_EMIT sendMessage(text());
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
    // Check if the listview or room widget want to handle the key (e.g Esc, PageUp)
    Q_EMIT keyPressed(e);
    if (e->isAccepted()) {
        return;
    }
    // Assign key to KTextEdit first otherwise text() doesn't return correct text
    KTextEdit::keyPressEvent(e);
}

QSize TextAutoGenerateTextLineEdit::sizeHint() const
{
    // The width of the QTextDocument is the current widget width, so this is somewhat circular logic.
    // But I don't really want to redo the layout with a different width like idealWidth(), seems slow.
    const QSize docSize = document()->size().toSize();
    const int margin = int(document()->documentMargin());
    return {docSize.width() + margin, qMin(300, docSize.height()) + margin};
}

QSize TextAutoGenerateTextLineEdit::minimumSizeHint() const
{
    const int margin = int(document()->documentMargin());
    return {300, fontMetrics().height() + margin};
}

#include "moc_textautogeneratetextlineedit.cpp"
