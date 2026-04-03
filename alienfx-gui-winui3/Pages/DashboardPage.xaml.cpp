#include "pch.h"
#include "DashboardPage.xaml.h"

namespace winrt::AlienFX::implementation
{
    DashboardPage::DashboardPage()
    {
        InitializeComponent();
        m_viewModel = this->DataContext().as<winrt::AlienFX::ViewModel::MainViewModel>();
        m_sensors = single_threaded_observable_vector<Model::SensorItem>();
    }

    void DashboardPage::ToggleLightsBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().ToggleLights();
    }

    void DashboardPage::ToggleDimmedBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().ToggleDimmed();
    }

    void DashboardPage::ToggleEffectsBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ViewModel().ToggleEffects();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<Model::SensorItem> DashboardPage::Sensors()
    {
        m_sensors.Clear();
        try
        {
            auto rawSensors = Helpers::HardwareBridge::Instance().GetSensors();
            for (auto const& s : rawSensors)
            {
                Model::SensorItem item;
                item.Name = s.Name;
                item.Value = s.Value;
                item.Unit = s.Unit;
                item.Type = 0;
                m_sensors.Append(item);
            }
        }
        catch (...)
        {
            // Sensors may not be available; return empty list
        }
        return m_sensors;
    }

    int32_t DashboardPage::DeviceCount()
    {
        auto devices = ViewModel().Devices();
        return devices ? static_cast<int32_t>(devices.Size()) : 0;
    }

    hstring DashboardPage::SensorSummary()
    {
        auto sensors = Sensors();
        if (sensors.Size() == 0)
        {
            return L"No sensors available";
        }

        hstring summary;
        uint32_t count = 0;
        for (auto const& s : sensors)
        {
            if (count > 0) summary = summary + L"  |  ";
            summary = summary + s.Name + L": " + to_hstring(static_cast<int32_t>(s.Value)) + s.Unit;
            count++;
            if (count >= 4) break; // Show first 4 sensors
        }
        return summary;
    }
}
