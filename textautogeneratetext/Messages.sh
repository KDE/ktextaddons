#! /bin/sh
# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
$EXTRACTRC `find . -name '*.kcfg' -or -name '*.kcfg.in'` >> rc.cpp || exit 11
$XGETTEXT `find . -name '*.cpp' -o -name '*.h' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/libtextautogeneratetext.pot
