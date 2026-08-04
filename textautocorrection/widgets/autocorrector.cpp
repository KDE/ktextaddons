/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Volker Krause <vkrause@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrector.h"

#include <TextAutoCorrectionCore/AutoCorrection>

#include <QKeyEvent>
#include <QPlainTextEdit>
#include <QTextEdit>

using namespace TextAutoCorrectionWidgets;
using namespace Qt::Literals;

static bool isSpecial(const QTextCharFormat &charFormat)
{
    return charFormat.isFrameFormat() || charFormat.isImageFormat() || charFormat.isListFormat() || charFormat.isTableFormat()
        || charFormat.isTableCellFormat();
}

class TextAutoCorrectionWidgets::AutoCorrectorPrivate
{
public:
    ~AutoCorrectorPrivate()
    {
        if (mNeedToDelete) {
            delete mAutoCorrection;
        }
    }

    template<typename T>
    void autocorrect(T *textEdit, bool richText, const QKeyEvent *e)
    {
        if (!textEdit->textCursor().hasSelection()) {
            const QTextCharFormat initialTextFormat = textEdit->textCursor().charFormat();
            int position = textEdit->textCursor().position();
            const bool addSpace = mAutoCorrection->autocorrect(richText, *textEdit->document(), position);
            QTextCursor cur = textEdit->textCursor();
            cur.setPosition(position);
            const bool spacePressed = (e->key() == Qt::Key_Space);
            const QChar insertChar = spacePressed ? u' ' : u'\n';
            if (richText && !isSpecial(initialTextFormat)) {
                if (addSpace || !spacePressed) {
                    cur.insertText(insertChar, initialTextFormat);
                }
            } else {
                if (addSpace || !spacePressed) {
                    cur.insertText(insertChar);
                }
            }
            textEdit->setTextCursor(cur);
        }
    }

    TextAutoCorrectionCore::AutoCorrection *mAutoCorrection = new TextAutoCorrectionCore::AutoCorrection();
    bool mNeedToDelete = true;
};

AutoCorrector::AutoCorrector(QTextEdit *textEdit)
    : QObject(textEdit)
    , d(new AutoCorrectorPrivate)
{
    textEdit->installEventFilter(this);
}

AutoCorrector::AutoCorrector(QPlainTextEdit *textEdit)
    : QObject(textEdit)
    , d(new AutoCorrectorPrivate)
{
    textEdit->installEventFilter(this);
}

AutoCorrector::~AutoCorrector() = default;

void AutoCorrector::setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect)
{
    d->mNeedToDelete = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

TextAutoCorrectionCore::AutoCorrection *AutoCorrector::autocorrection() const
{
    return d->mAutoCorrection;
}

void AutoCorrector::setAutocorrectionLanguage(const QString &language)
{
    TextAutoCorrectionCore::AutoCorrectionSettings *settings = d->mAutoCorrection->autoCorrectionSettings();
    settings->setLanguage(language);
    d->mAutoCorrection->setAutoCorrectionSettings(settings);
}

bool AutoCorrector::eventFilter(QObject *receiver, QEvent *event)
{
    if (receiver == parent() && event->type() == QEvent::KeyPress && d->mAutoCorrection
        && d->mAutoCorrection->autoCorrectionSettings()->isEnabledAutoCorrection()) {
        const auto e = static_cast<QKeyEvent *>(event);
        if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
            if (auto textEdit = qobject_cast<QTextEdit *>(receiver); textEdit) {
                d->autocorrect(textEdit, textEdit->acceptRichText(), e);
                return true;
            } else if (auto plainEdit = qobject_cast<QPlainTextEdit *>(receiver); plainEdit) {
                d->autocorrect(plainEdit, false, e);
                return true;
            }
        }
    }
    return QObject::eventFilter(receiver, event);
}

#include "moc_autocorrector.cpp"
