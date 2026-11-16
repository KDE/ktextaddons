/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <KService>
#include <QObject>
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::OpenFileJob
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/OpenFileJob
 */
class TEXTADDONSWIDGETS_EXPORT OpenFileJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for OpenFileJob
     * \param parent The parent object
     */
    explicit OpenFileJob(QObject *parent = nullptr);
    /*!
     * \brief Destructor for OpenFileJob
     */
    ~OpenFileJob() override;

    /*!
     * \brief Returns the parent widget for file operations
     * \return The parent widget
     */
    [[nodiscard]] QWidget *parentWidget() const;
    /*!
     * \brief Sets the parent widget for file operations
     * \param newParentWidget The widget to set as parent
     */
    void setParentWidget(QWidget *newParentWidget);

    /*!
     * \brief Returns the link to the file or URL
     * \return The link string
     */
    [[nodiscard]] QString link() const;
    /*!
     * \brief Sets the link to the file or URL
     * \param newLink The link to set
     */
    void setLink(const QString &newLink);

    /*!
     * \brief Returns whether the job can start
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;

    /*!
     * \brief Starts the file operation
     */
    void start();

    /*!
     * \brief Download a file from the given URL (pure virtual)
     * \param fileUrl The URL of the file to download
     */
    virtual void downloadFile(const QUrl &fileUrl) = 0;
    /*!
     * \brief Run an application with the given service (pure virtual)
     * \param offer The service to run
     */
    virtual void runApplication(const KService::Ptr &offer) = 0;
    /*!
     * \brief Open a URL (pure virtual)
     */
    virtual void openUrl() = 0;

protected:
    /*!
     * \brief The parent widget for file operations
     */
    QWidget *mParentWidget = nullptr;
    /*!
     * \brief The link to the file or URL
     */
    QString mLink;
};
}
