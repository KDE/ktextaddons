# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
include(ECMAddTests)

ecm_add_test(slidecontainertest.cpp slidecontainertest.h
    TEST_NAME slidecontainertest
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}TextAddonsWidgets Qt::Widgets 
    )
