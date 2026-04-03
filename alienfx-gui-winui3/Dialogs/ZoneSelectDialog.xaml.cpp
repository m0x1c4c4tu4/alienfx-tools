#include "pch.h"
#include "ZoneSelectDialog.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml::Controls;
namespace winrt::AlienFX::Dialogs::implementation
{
    ZoneSelectDialog::ZoneSelectDialog() { InitializeComponent(); }
    winrt::Windows::Foundation::Collections::IVector<hstring> ZoneSelectDialog::GetSelectedZones()
    {
        return m_selectedZones;
    }
    void ZoneSelectDialog::AddZone(hstring const& name)
    {
        m_selectedZones.Append(name);
    }
}
