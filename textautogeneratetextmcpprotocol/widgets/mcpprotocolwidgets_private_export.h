/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocolwidgets_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT
#define TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT
#endif
#else /* not compiling tests */
#define TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT
#endif
