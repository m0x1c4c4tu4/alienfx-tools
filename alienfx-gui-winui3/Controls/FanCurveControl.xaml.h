#pragma once
#include "FanCurveControl.g.h"
#include <vector>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace winrt::AlienFX::Controls::implementation
{
    struct FanCurveControl : FanCurveControlT<FanCurveControl>
    {
        FanCurveControl();

        void DrawCurve();
        void AddPoint(int32_t temp, int32_t speed);
        void ClearPoints();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Point> Points();
        void OnPointerPressed(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void OnPointerMoved(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
        void OnPointerReleased(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);

        event<winrt::Windows::Foundation::TypedEventHandler<Controls::FanCurveControl, winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Point>>> CurveChanged;

    private:
        void RenderCurve();
        void DrawGridLines();
        void DrawCurveLine();
        void DrawControlPoints();

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Point> m_points{ nullptr };
        int32_t m_draggingPoint{ -1 };
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<Controls::FanCurveControl, winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Point>>> m_curveChanged;
    };
}

namespace winrt::AlienFX::Controls::factory_implementation
{
    struct FanCurveControl : FanCurveControlT<FanCurveControl, implementation::FanCurveControl> {};
}
