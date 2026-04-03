#include "pch.h"
#include "DevicesPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::AlienFX::implementation
{
    DevicesPage::DevicesPage()
    {
        InitializeComponent();
        m_viewModel = make<ViewModel::implementation::DevicesViewModel>();
        DataContext(m_viewModel);
    }

    ViewModel::DevicesViewModel DevicesPage::ViewModel()
    {
        return m_viewModel;
    }

    void DevicesPage::OnDetect(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.Detect();
    }

    void DevicesPage::OnLoadMap(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.LoadMap();
    }

    void DevicesPage::OnSaveMap(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.SaveMap();
    }

    void DevicesPage::OnAddZone(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.AddZone();
    }

    void DevicesPage::OnDeleteZone(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.DeleteZone();
    }

    void DevicesPage::OnSelectFromList(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.SelectFromList();
    }

    void DevicesPage::OnWhiteBalance(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.WhiteBalance();
    }

    void DevicesPage::OnClearLight(IInspectable const&, RoutedEventArgs const&)
    {
        m_viewModel.ClearLight();
    }
}
