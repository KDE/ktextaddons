/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translateLocally code
*/

#pragma once
#include "libbergamot_export.h"
#include <QMetaType>
#include <QString>
#include <QVector>
#include <memory>

namespace marian
{
namespace bergamot
{
class Response;
}
}

/**
 * Wrapper around a translation response from the bergamot service. Hides that
 * interface from the rest of the Qt code, and provides utility functions to
 * access alignment information with character offsets instead of byte offsets.
 */
class LIBBERGAMOT_EXPORT Translation
{
public:
    Translation();
    Translation(marian::bergamot::Response &&response);

    /**
     * Bool operator to check whether this is an initialised translation or just
     * an empty object.
     */
    inline operator bool() const
    {
        return !!mResponse;
    }

    /**
     * Translation result
     */
    Q_REQUIRED_RESULT QString translation() const;

private:
    // Note: I would have liked unique_ptr, but that does not go well with
    // passing Translation objects through Qt signals/slots.
    std::shared_ptr<marian::bergamot::Response> mResponse;
};

Q_DECLARE_METATYPE(Translation)
