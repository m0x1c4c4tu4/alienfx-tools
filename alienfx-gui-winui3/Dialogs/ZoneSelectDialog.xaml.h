#pragma once
#include "ZoneSelectDialog.g.h"
namespace winrt::AlienFX::Dialogs::implementation { struct ZoneSelectDialog : ZoneSelectDialogT<ZoneSelectDialog> { ZoneSelectDialog(); }; }
namespace winrt::AlienFX::Dialogs::factory_implementation { struct ZoneSelectDialog : ZoneSelectDialogT<ZoneSelectDialog, implementation::ZoneSelectDialog> {}; }
