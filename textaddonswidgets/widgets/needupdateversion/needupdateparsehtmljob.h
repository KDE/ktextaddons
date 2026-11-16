/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QObject>
#include <QUrl>
namespace KIO
{
class Job;
}
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::NeedUpdateParseHtmlJob
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/NeedUpdateParseHtmlJob
 */
class TEXTADDONSWIDGETS_EXPORT NeedUpdateParseHtmlJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for NeedUpdateParseHtmlJob
     * \param parent The parent object
     */
    explicit NeedUpdateParseHtmlJob(QObject *parent = nullptr);
    /*!
     * \brief Destructor for NeedUpdateParseHtmlJob
     */
    ~NeedUpdateParseHtmlJob() override;

    /*!
     * \brief Returns whether the job can start
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;

    /*!
     * \brief Returns the URL to parse
     * \return The URL
     */
    [[nodiscard]] QUrl url() const;
    /*!
     * \brief Sets the URL to parse
     * \param newUrl The URL to set
     */
    void setUrl(const QUrl &newUrl);

    /*!
     * \brief Starts the HTML parsing job
     */
    void start();

Q_SIGNALS:
    /*!
     * \brief Emitted when the HTML download and parsing is complete
     * \param data The parsed HTML data
     */
    void downLoadDone(const QString &data);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotHttpDataFile(KIO::Job *job, const QByteArray &data);
    QUrl mUrl;
    QString mData;
};
}
