/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresulttextedit.h"
using namespace Qt::Literals::StringLiterals;

#include "grammarresultutil.h"
#include "textgrammarcheck_debug.h"
#include <KStatefulBrush>

#include <KLocalizedString>
#include <KStandardActions>
#include <QDesktopServices>

#include <KColorScheme>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QPainter>
using namespace TextGrammarCheck;
GrammarResultTextEdit::GrammarResultTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptRichText(false);
    generalPaletteChanged();
}

GrammarResultTextEdit::~GrammarResultTextEdit() = default;

void GrammarResultTextEdit::paintEvent(QPaintEvent *event)
{
    if (document()->isEmpty()) {
        const QString label = i18n("Any text to check.");

        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, label);
    } else {
        QTextEdit::paintEvent(event);
    }
}

bool GrammarResultTextEdit::event(QEvent *ev)
{
    if (ev->type() == QEvent::ApplicationPaletteChange) {
        generalPaletteChanged();
    }
    return QTextEdit::event(ev);
}

void GrammarResultTextEdit::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
    const KStatefulBrush bgBrush = KStatefulBrush(KColorScheme::View, KColorScheme::NegativeText);
    mNegativeTextColor = bgBrush.brush(palette).color();
}

void GrammarResultTextEdit::applyGrammarResult(const QVector<GrammarError> &infos)
{
    GrammarResultUtil::applyGrammarResult(infos, document(), mNegativeTextColor);
}

void GrammarResultTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *popup = createStandardContextMenu();
    if (popup) {
        QTextCursor cursor = cursorForPosition(event->pos());
        if (cursor.charFormat().hasProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo)) {
            const auto act = cursor.charFormat().property(GrammarResultUtil::TextInfo::ReplaceFormatInfo).value<TextGrammarCheck::GrammarAction>();
            const QStringList sugg = act.suggestions();
            if (!sugg.isEmpty()) {
                popup->addSeparator();
                QMenu *popupReplacement = popup->addMenu(i18n("Replacement"));
                for (const QString &str : sugg) {
                    QAction *actReplacement = popupReplacement->addAction(str);
                    connect(actReplacement, &QAction::triggered, this, [this, act, str]() {
                        slotReplaceWord(act, str);
                    });
                }
                const QStringList lst = act.infoUrls();
                if (!lst.isEmpty()) {
                    QMenu *popupUrlInfo = popup->addMenu(i18n("Online Grammar Information"));
                    for (const QString &str : lst) {
                        QAction *actUrlInfo = popupUrlInfo->addAction(str);
                        connect(actUrlInfo, &QAction::triggered, this, [this, str]() {
                            slotOpenGrammarUrlInfo(str);
                        });
                    }
                }
            } else {
                qCDebug(TEXTGRAMMARCHECK_LOG) << " no suggestion " << act;
            }
        }
        popup->addSeparator();
        QAction *checkAgainAct = popup->addAction(QIcon::fromTheme(u"view-refresh"_s), i18n("Check Again"));
        connect(checkAgainAct, &QAction::triggered, this, &GrammarResultTextEdit::checkAgain);
        popup->addSeparator();
        QAction *configureAct = popup->addAction(QIcon::fromTheme(u"settings-configure"_s), i18n("Configure…"));
        connect(configureAct, &QAction::triggered, this, &GrammarResultTextEdit::configure);
        popup->addSeparator();
        QAction *closeAct = KStandardActions::close(this, &GrammarResultTextEdit::closeChecker, this);
        closeAct->setShortcut({});
        popup->addAction(closeAct);
        popup->exec(event->globalPos());
        delete popup;
    }
}

void GrammarResultTextEdit::slotOpenGrammarUrlInfo(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void GrammarResultTextEdit::slotReplaceWord(const TextGrammarCheck::GrammarAction &act, const QString &replacementWord)
{
    TextGrammarCheck::GrammarAction actWithReplacement = act;
    actWithReplacement.setReplacement(replacementWord);
    GrammarResultUtil::replaceWord(actWithReplacement, replacementWord, document());
    Q_EMIT replaceText(actWithReplacement);
}

#include "moc_grammarresulttextedit.cpp"
