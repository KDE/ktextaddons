/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateListViewBaseDelegate;
class TextAutoGeneratePluginTextInterface;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateBaseListView
 * \brief The TextAutoGenerateBaseListView class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateBaseListView
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateBaseListView : public QListView
{
    Q_OBJECT
public:
    enum class Mode : uint8_t {
        Editing = 0,
        Viewing,
        Searching,
    };

    /*!
     * \brief TextAutoGenerateBaseListView
     * \param manager
     * \param parent
     */
    explicit TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateBaseListView() override;

    /*!
     */
    void slotSelectAll(const QModelIndex &index);
    /*!
     */
    void clearDocumentCache();

    /*!
     */
    [[nodiscard]] Mode mode() const;
    /*!
     */
    void setMode(Mode newMode);

protected:
    /*!
     */
    void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    /*!
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    /*!
     */
    void mousePressEvent(QMouseEvent *event) override;
    /*!
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /*!
     */
    [[nodiscard]] virtual QString originalMessage(const QModelIndex &index) const = 0;
    /*!
     */
    [[nodiscard]] QString selectedText(const QModelIndex &index) const;
    /*!
     */
    virtual void handleMouseEvent(QMouseEvent *event);

    /*!
     */
    void resizeEvent(QResizeEvent *ev) override;
    /*!
     */
    void slotCopyMessage(const QModelIndex &index);
    /*!
     */
    void slotTextToSpeechRequested(const QModelIndex &index);
    /*!
     */
    void slotStopTextToSpeechRequested(const QModelIndex &index);
    /*!
     */
    [[nodiscard]] QStyleOptionViewItem listViewOptions() const;
    /*!
     */
    void checkIfAtBottom();
    /*!
     */
    void maybeScrollToBottom();
    /*!
     */
    void updateVerticalPageStep();
    /*!
     */
    virtual bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    /*!
     */
    virtual bool mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    TextAutoGenerateListViewBaseDelegate *mDelegate = nullptr;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QPoint mPressedPosition;
    QPersistentModelIndex mCurrentIndex;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotDebugGeneratedTextMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotDebugMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotFontChanged();
    bool mAtBottom = true;
    Mode mMode = Mode::Editing;
    QList<TextAutoGeneratePluginTextInterface *> mPluginTextInterface;
};
}
