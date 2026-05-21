/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <KMessageWidget>
#include <QUrl>
class QTimer;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::OpenSavedFileFolderWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/OpenSavedFileFolderWidget
 *
 * \brief The OpenSavedFileFolderWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT OpenSavedFileFolderWidget : public KMessageWidget
{
    Q_OBJECT
public:
    enum class FileType : uint8_t {
        Attachment,
        Pdf,
    };
    Q_ENUM(FileType)

    /*!
     * \brief Constructor for RichTextQuickTextFormat
     * \param editor The text editor to attach to
     * \param parent The parent widget
     */
    explicit OpenSavedFileFolderWidget(QWidget *parent = nullptr);
    /*!
     */
    ~OpenSavedFileFolderWidget() override;

    /*!
     * \brief setUrls
     * \param urls
     * \param fileType
     */
    void setUrls(const QList<QUrl> &urls, TextAddonsWidgets::OpenSavedFileFolderWidget::FileType fileType);

    /*!
     * \brief slotShowWarning
     */
    void slotShowWarning();
    /*!
     * \brief slotHideWarning
     */
    void slotHideWarning();

private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotOpenSavedFileFolder();
    TEXTADDONSWIDGETS_NO_EXPORT void slotTimeOut();
    TEXTADDONSWIDGETS_NO_EXPORT void slotOpenFile();
    TEXTADDONSWIDGETS_NO_EXPORT void slotExplicitlyClosed();
    QList<QUrl> mUrls;
    QTimer *const mTimer;
    QAction *const mShowFolderAction;
    QAction *const mOpenFileAction;
};
}
