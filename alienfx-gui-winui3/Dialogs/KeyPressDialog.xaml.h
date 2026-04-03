#pragma once
#include "KeyPressDialog.g.h"
namespace winrt::AlienFX::Dialogs::implementation { struct KeyPressDialog : KeyPressDialogT<KeyPressDialog> { KeyPressDialog(); void KeyCaptureArea_KeyDown(IInspectable const&, Input::KeyRoutedEventArgs const&); }; }
namespace winrt::AlienFX::Dialogs::factory_implementation { struct KeyPressDialog : KeyPressDialogT<KeyPressDialog, implementation::KeyPressDialog> {}; }
