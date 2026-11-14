/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "kokoro/texttospeechkokoro.h"
#include "kokoro/texttospeechkokoroengine.h"
#include "kokoro/texttospeechkokoroplugin.h"
#include "kokoroinstall/textedittexttospeech_kokoroinstall_private_export.h"
#include "kokoroinstall/texttospeechkokorocheckjob.h"
#include "kokoroinstall/texttospeechkokorodownloadvoicejob.h"
#include "kokoroinstall/texttospeechkokoroinstalljob.h"
#include "kokoroinstall/texttospeechkokoroinstallmessagewidget.h"
#include "kokoroinstall/texttospeechkokoroinstallpythondialog.h"
#include "kokoroinstall/texttospeechkokoroinstallpythonevenvjob.h"
#include "kokoroinstall/texttospeechkokoroinstallpythonwidget.h"
#include "kokoroinstall/texttospeechkokoroutils.h"
#include "kokoroinstall/texttospeechkokorovoicecombobox.h"
#include "textedittexttospeech_private_export.h"
#include "texttospeech.h"
#include "texttospeechactions.h"
#include "texttospeechconfigdialog.h"
#include "texttospeechconfiginterface.h"
#include "texttospeechconfigwidget.h"
#include "texttospeechcontainerwidget.h"
#include "texttospeechinterface.h"
#include "texttospeechlanguagecombobox.h"
#include "texttospeechsliderwidget.h"
#include "texttospeechutil.h"
#include "texttospeechvoicecombobox.h"
#include "texttospeechwidget.h"
