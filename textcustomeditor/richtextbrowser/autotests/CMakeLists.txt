# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(richtextbrowsertest.cpp richtextbrowsertest.h TEST_NAME richtextbrowsertest
    LINK_LIBRARIES KF6::TextCustomEditor Qt::Test Qt::Widgets
)

ecm_add_test(richtextbrowserfindbartest.cpp richtextbrowserfindbartest.h TEST_NAME richtextbrowserfindbartest
    LINK_LIBRARIES KF6::TextCustomEditor Qt::Test Qt::Widgets
)
