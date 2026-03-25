/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternal>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolInternalJob;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalInterface : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolInternalInterface(QObject *parent = nullptr);
    /*!
     */
    virtual ~TextAutoGenerateTextToolInternalInterface();

    /*!
     */
    virtual void executeTool(const QByteArray &toolName) = 0;

    /*!
     */
    void loadInternalTools(const QString &filename);

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> tools() const;
    /*!
     */
    void setTools(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &newTools);

    /*!
     */
    [[nodiscard]] bool contains(const QByteArray &toolName) const;

    /*!
     */
    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateTextToolInternalJob *callTool() = 0;

protected:
    QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> mTools;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotToolsLoaded(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &list);
};
}
