/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextMcpServerModel;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextMcpServerManager
 * \brief The TextAutoGenerateTextMcpServerManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextMcpServerManager
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextMcpServerManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TextAutoGenerateTextMcpServerManager
     * \param parent
     */
    explicit TextAutoGenerateTextMcpServerManager(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextMcpServerManager() override;

    /*!
     * \brief textAutoGenerateTextMcpServerModel
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpServerModel *textAutoGenerateTextMcpServerModel() const;

    /*!
     * \brief loadServers
     */
    void loadServers();

    /*!
     * \brief saveServers
     */
    void saveServers();

private:
    TextAutoGenerateTextMcpServerModel *const mTextAutoGenerateTextMcpServerModel;
};
}
