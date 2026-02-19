/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textcustomeditor_export.h"
#include <QRegularExpression>
#include <QWidget>
namespace TextCustomEditor
{
class TextFindWidget;
class TextReplaceWidget;
/*!
 * \class TextCustomEditor::TextEditFindBarBase
 * \inmodule TextCustomEditor
 * \inheaderfile TextCustomEditor/TextEditFindBarBase
 *
 * \brief The TextEditFindBarBase class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTCUSTOMEDITOR_EXPORT TextEditFindBarBase : public QWidget
{
    Q_OBJECT

public:
    enum FindFlag {
        FindBackward = 0x00001,
        FindCaseSensitively = 0x00002,
        FindWholeWords = 0x00004,
        FindRespectDiacritics = 0x00008,
    };
    Q_DECLARE_FLAGS(FindFlags, FindFlag)

    /*!
     */
    explicit TextEditFindBarBase(QWidget *parent = nullptr);
    /*!
     */
    ~TextEditFindBarBase() override;

    /*!
     */
    [[nodiscard]] QString text() const;
    /*!
     */
    void setText(const QString &text);

    /*!
     */
    void focusAndSetCursor();

    /*!
     */
    void showReplace();
    /*!
     */
    void showFind();
    /*!
     */
    void setHideWhenClose(bool hide);

Q_SIGNALS:
    /*! Emitted to display a message to the user. */
    void displayMessageIndicator(const QString &message);
    /*! Emitted when the find bar should be hidden. */
    void hideFindBar();

protected:
    /*! Returns whether the view is read-only. Implemented by subclasses. */
    [[nodiscard]] virtual bool viewIsReadOnly() const = 0;
    /*! Returns whether the document is empty. Implemented by subclasses. */
    [[nodiscard]] virtual bool documentIsEmpty() const = 0;
    /*! Searches for text in the document. Implemented by subclasses. */
    virtual bool searchInDocument(const QString &text, TextEditFindBarBase::FindFlags searchOptions) = 0;
    /*! Searches for text using regex in the document. Implemented by subclasses. */
    virtual bool searchInDocument(const QRegularExpression &regExp, TextEditFindBarBase::FindFlags searchOptions) = 0;
    /*! Moves the cursor after an automatic search. Implemented by subclasses. */
    virtual void autoSearchMoveCursor() = 0;

    /*! Handles events. */
    [[nodiscard]] bool event(QEvent *e) override;
    /*! Clears the current search selections. */
    void clearSelections();
    /*! Searches for text with the given options. */
    bool searchText(bool backward, bool isAutoSearch);

    /*! Updates the visual indication of whether a match was found. */
    void setFoundMatch(bool match);
    /*! Displays a message about the search result. */
    void messageInfo(bool backward, bool isAutoSearch, bool found);

public Q_SLOTS:
    /*! Finds the next occurrence of the search text. */
    void findNext();
    /*! Finds the previous occurrence of the search text. */
    void findPrev();
    /*! Automatically searches for the given text. */
    void autoSearch(const QString &str);
    /*! Searches for text with the given options. Implemented by subclasses. */
    virtual void slotSearchText(bool backward = false, bool isAutoSearch = true) = 0;
    /*! Closes the find bar. */
    void closeBar();

private Q_SLOTS:
    TEXTCUSTOMEDITOR_NO_EXPORT void slotClearSearch();
    TEXTCUSTOMEDITOR_NO_EXPORT void slotUpdateSearchOptions();
    virtual void slotReplaceText() = 0;
    virtual void slotReplaceAllText() = 0;

protected:
    QString mLastSearchStr;
    QRegularExpression mLastSearchRegExp;
    TextFindWidget *const mFindWidget;
    TextReplaceWidget *const mReplaceWidget;
    bool mHideWhenClose = true;
};
}
