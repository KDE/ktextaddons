/*
   SPDX-FileCopyrightText: 2020 David Faure <faure@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"

#include <QPersistentModelIndex>
class QMovie;
namespace TextEmoticonsCore
{
struct TEXTEMOTICONSCORE_EXPORT RunningAnimatedImage {
    /*!
     * \brief Constructs a RunningAnimatedImage with the given model index
     * \param idx The model index for the animated image
     */
    explicit RunningAnimatedImage(const QModelIndex &idx);
    /*!
     * \brief Destroys the RunningAnimatedImage and stops the movie
     */
    ~RunningAnimatedImage();
    /*!
     * \brief Copy constructor is deleted
     */
    RunningAnimatedImage(const RunningAnimatedImage &) = delete;
    /*!
     * \brief Move constructor
     * \param other The RunningAnimatedImage to move from
     */
    RunningAnimatedImage(RunningAnimatedImage &&other) noexcept;
    /*!
     * \brief Copy assignment operator is deleted
     */
    RunningAnimatedImage &operator=(const RunningAnimatedImage &) = delete;
    /*!
     * \brief Move assignment operator
     * \param other The RunningAnimatedImage to move from
     * \return A reference to this RunningAnimatedImage
     */
    RunningAnimatedImage &operator=(RunningAnimatedImage &&other);

    QPersistentModelIndex index; /*!< The persistent model index for the animated image */
    QMovie *movie = nullptr; /*!< The QMovie instance for the animation */
};
}
