/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectiontextedit.h"
#include <TextAutoCorrectionCore/AutoCorrection>

#include <QKeyEvent>

using namespace TextAutoCorrectionWidgets;

class TextAutoCorrectionWidgets::AutoCorrectionTextEditPrivate
{
public:
    AutoCorrectionTextEditPrivate()
        : mAutoCorrection(new TextAutoCorrectionCore::AutoCorrection())
    {
    }

    ~AutoCorrectionTextEditPrivate()
    {
        if (mNeedToDelete) {
            delete mAutoCorrection;
        }
    }

    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = nullptr;
    bool mNeedToDelete = true;
};

AutoCorrectionTextEdit::AutoCorrectionTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , d(new TextAutoCorrectionWidgets::AutoCorrectionTextEditPrivate)
{
}

AutoCorrectionTextEdit::~AutoCorrectionTextEdit() = default;

void AutoCorrectionTextEdit::setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect)
{
    d->mNeedToDelete = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

TextAutoCorrectionCore::AutoCorrection *AutoCorrectionTextEdit::autocorrection() const
{
    return d->mAutoCorrection;
}

void AutoCorrectionTextEdit::setAutocorrectionLanguage(const QString &language)
{
    TextAutoCorrectionCore::AutoCorrectionSettings *settings = d->mAutoCorrection->autoCorrectionSettings();
    settings->setLanguage(language);
    d->mAutoCorrection->setAutoCorrectionSettings(settings);
}

static bool isSpecial(const QTextCharFormat &charFormat)
{
    return charFormat.isFrameFormat() || charFormat.isImageFormat() || charFormat.isListFormat() || charFormat.isTableFormat()
        || charFormat.isTableCellFormat();
}

void AutoCorrectionTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (d->mAutoCorrection && d->mAutoCorrection->autoCorrectionSettings()->isEnabledAutoCorrection()) {
        if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
            if (!textCursor().hasSelection()) {
                const QTextCharFormat initialTextFormat = textCursor().charFormat();
                const bool richText = acceptRichText();
                int position = textCursor().position();
                const bool addSpace = d->mAutoCorrection->autocorrect(richText, *document(), position);
                QTextCursor cur = textCursor();
                cur.setPosition(position);
                const bool spacePressed = (e->key() == Qt::Key_Space);
                const QChar insertChar = spacePressed ? QLatin1Char(' ') : QLatin1Char('\n');
                if (richText && !isSpecial(initialTextFormat)) {
                    if (addSpace || !spacePressed) {
                        cur.insertText(insertChar, initialTextFormat);
                    }
                } else {
                    if (addSpace || !spacePressed) {
                        cur.insertText(insertChar);
                    }
                }
                setTextCursor(cur);
                return;
            }
        }
    }
    QTextEdit::keyPressEvent(e);
}

#include "moc_autocorrectiontextedit.cpp"
