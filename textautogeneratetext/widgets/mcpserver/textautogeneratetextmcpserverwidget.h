/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextMcpServerListView;
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesMcpServerWidget
 * \brief The TextAutoGenerateTextInstancesMcpServerWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesMcpServerWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextMcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief TextAutoGenerateTextMcpServerWidget
     * \param manager
     * \param parent
     */
    explicit TextAutoGenerateTextMcpServerWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextMcpServerWidget() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddServer();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveServer(const QByteArray &identifier);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditServer(const QByteArray &identifier);
    QLineEdit *const mSearchLineEdit;
    TextAutoGenerateTextMcpServerListView *const mMcpServerListView;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
