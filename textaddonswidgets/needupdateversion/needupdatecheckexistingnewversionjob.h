/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QDate>
#include <QObject>
#include <QUrl>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::NeedUpdateCheckExistingNewVersionJob
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/NeedUpdateCheckExistingNewVersionJob
 */
class TEXTADDONSWIDGETS_EXPORT NeedUpdateCheckExistingNewVersionJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for NeedUpdateCheckExistingNewVersionJob
     * \param parent The parent object
     */
    explicit NeedUpdateCheckExistingNewVersionJob(QObject *parent = nullptr);
    /*!
     * \brief Destructor for NeedUpdateCheckExistingNewVersionJob
     */
    ~NeedUpdateCheckExistingNewVersionJob() override;

    /*!
     * \brief Starts the version check job
     */
    void start();

    /*!
     * \brief Returns the URL to check for new version
     * \return The URL
     */
    [[nodiscard]] QUrl url() const;
    /*!
     * \brief Sets the URL to check for new version
     * \param newUrl The URL to set
     */
    void setUrl(const QUrl &newUrl);

    /*!
     * \brief Returns whether the job can start
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;

    /*!
     * \brief Returns the compile date
     * \return The compile date
     */
    [[nodiscard]] QDate compileDate() const;
    /*!
     * \brief Sets the compile date
     * \param newCompileDate The compile date to set
     */
    void setCompileDate(const QDate &newCompileDate);

Q_SIGNALS:
    /*!
     * \brief Emitted when new version checking is complete
     * \param state True if a new version was found, false otherwise
     */
    void foundNewVersion(bool state);

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotDownloadDone(const QString &str);
    QUrl mUrl;
    QDate mCompileDate;
};
}
