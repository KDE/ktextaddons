/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libbergamot_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBBERGAMOT_TESTS_EXPORT
#define LIBBERGAMOT_TESTS_EXPORT LIBBERGAMOT_EXPORT
#endif
#else /* not compiling tests */
#define LIBBERGAMOT_TESTS_EXPORT
#endif
