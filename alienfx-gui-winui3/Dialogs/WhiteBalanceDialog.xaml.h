#pragma once
#include "WhiteBalanceDialog.g.h"
namespace winrt::AlienFX::Dialogs::implementation { struct WhiteBalanceDialog : WhiteBalanceDialogT<WhiteBalanceDialog> { WhiteBalanceDialog(); }; }
namespace winrt::AlienFX::Dialogs::factory_implementation { struct WhiteBalanceDialog : WhiteBalanceDialogT<WhiteBalanceDialog, implementation::WhiteBalanceDialog> {}; }
