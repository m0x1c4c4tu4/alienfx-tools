#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <string>

namespace winrt::AlienFX::ViewModel::implementation
{
    struct ViewModelBase : implements<ViewModelBase,
        Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    {
    public:
        event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

        winrt::event_token PropertyChanged(
            Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }

    protected:
        void OnPropertyChanged(std::wstring_view propertyName)
        {
            m_propertyChanged(*this,
                Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{
                    winrt::hstring{propertyName} });
        }

        template<typename T>
        bool SetAndNotify(T& field, T&& value, std::wstring_view propertyName)
        {
            if (field != value)
            {
                field = std::forward<T>(value);
                OnPropertyChanged(propertyName);
                return true;
            }
            return false;
        }
    };
}
