/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextcore_export.h"
#include <QList>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternal>
class QJsonArray;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolsLoadingJob
 * \brief The TextAutoGenerateTextToolsLoadingJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolsLoadingJob
 */
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGenerateTextToolsLoadingJob : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolsLoadingJob(QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextToolsLoadingJob() override;

    /*!
     */
    void start();

    /*!
     */
    [[nodiscard]] bool canStart() const;

    /*!
     */
    [[nodiscard]] QString fileName() const;
    /*!
     */
    void setFileName(const QString &newFileName);

Q_SIGNALS:
    /*!
     */
    void tools(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &list);

private:
    TEXTAUTOGENERATETEXTCORE_NO_EXPORT void parseJsonTools(const QJsonArray &array);
    TEXTAUTOGENERATETEXTCORE_NO_EXPORT void loadTools();
    QString mFileName;
};
}
