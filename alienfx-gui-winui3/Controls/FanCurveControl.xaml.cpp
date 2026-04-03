#include "pch.h"
#include "FanCurveControl.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Shapes;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Input;
using namespace Windows::Foundation;

namespace winrt::AlienFX::Controls::implementation
{
    FanCurveControl::FanCurveControl()
    {
        InitializeComponent();
        m_points = single_threaded_vector<Point>();
        m_points.Append({ 30.0f, 80.0f });
        m_points.Append({ 50.0f, 60.0f });
        m_points.Append({ 70.0f, 30.0f });
        m_points.Append({ 90.0f, 10.0f });
    }

    IVector<Point> FanCurveControl::Points() { return m_points; }

    void FanCurveControl::DrawCurve() { RenderCurve(); }
    void FanCurveControl::AddPoint(int32_t temp, int32_t speed) { m_points.Append({ (float)temp, (float)speed }); RenderCurve(); }
    void FanCurveControl::ClearPoints() { m_points.Clear(); RenderCurve(); }

    void FanCurveControl::OnPointerPressed(PointerRoutedEventArgs const& args)
    {
        auto pos = args.GetCurrentPoint(nullptr).Position();
        for (uint32_t i = 0; i < m_points.Size(); ++i) {
            auto pt = m_points.GetAt(i);
            if (abs(pos.X - pt.X) < 10 && abs(pos.Y - pt.Y) < 10) {
                m_draggingPoint = i;
                break;
            }
        }
    }

    void FanCurveControl::OnPointerMoved(PointerRoutedEventArgs const& args)
    {
        if (m_draggingPoint >= 0) {
            auto pos = args.GetCurrentPoint(nullptr).Position();
            m_points.SetAt(m_draggingPoint, { (float)pos.X, (float)pos.Y });
            RenderCurve();
        }
    }

    void FanCurveControl::OnPointerReleased(PointerRoutedEventArgs const&)
    {
        m_draggingPoint = -1;
        m_curveChanged(*this, m_points);
    }

    void FanCurveControl::RenderCurve()
    {
        DrawGridLines();
        DrawCurveLine();
        DrawControlPoints();
    }

    void FanCurveControl::DrawGridLines()
    {
        if (auto canvas = FindName(L"CurveCanvas").try_as<Shapes::Canvas>()) {
            canvas.Children().Clear();
            for (int i = 0; i <= 10; ++i) {
                Line hLine; hLine.X1(0); hLine.X2(canvas.ActualWidth());
                hLine.Y1(i * canvas.ActualHeight() / 10); hLine.Y2(hLine.Y1());
                hLine.Stroke(SolidColorBrush{ Windows::UI::Color{ 0, 51, 51, 51 } });
                hLine.StrokeThickness(1);
                canvas.Children().Append(hLine);

                Line vLine; vLine.X1(i * canvas.ActualWidth() / 10); vLine.X2(vLine.X1());
                vLine.Y1(0); vLine.Y2(canvas.ActualHeight());
                vLine.Stroke(SolidColorBrush{ Windows::UI::Color{ 0, 51, 51, 51 } });
                vLine.StrokeThickness(1);
                canvas.Children().Append(vLine);
            }
        }
    }

    void FanCurveControl::DrawCurveLine()
    {
        if (auto canvas = FindName(L"CurveCanvas").try_as<Shapes::Canvas>()) {
            if (m_points.Size() < 2) return;
            auto w = canvas.ActualWidth();
            auto h = canvas.ActualHeight();
            for (uint32_t i = 1; i < m_points.Size(); ++i) {
                auto p1 = m_points.GetAt(i - 1);
                auto p2 = m_points.GetAt(i);
                Line line;
                line.X1(p1.X / 100.0f * w); line.Y1(h - p1.Y / 100.0f * h);
                line.X2(p2.X / 100.0f * w); line.Y2(h - p2.Y / 100.0f * h);
                line.Stroke(SolidColorBrush{ Windows::UI::Color{ 255, 0, 212, 170 } });
                line.StrokeThickness(3);
                canvas.Children().Append(line);
            }
        }
    }

    void FanCurveControl::DrawControlPoints()
    {
        if (auto canvas = FindName(L"CurveCanvas").try_as<Shapes::Canvas>()) {
            auto w = canvas.ActualWidth();
            auto h = canvas.ActualHeight();
            for (uint32_t i = 0; i < m_points.Size(); ++i) {
                auto pt = m_points.GetAt(i);
                Ellipse dot;
                dot.Width(12); dot.Height(12);
                Canvas::SetLeft(dot, pt.X / 100.0f * w - 6);
                Canvas::SetTop(dot, h - pt.Y / 100.0f * h - 6);
                dot.Fill(SolidColorBrush{ Windows::UI::Color{ 255, 0, 212, 170 } });
                dot.Stroke(SolidColorBrush{ Windows::UI::Color{ 255, 255, 255, 255 } });
                dot.StrokeThickness(2);
                canvas.Children().Append(dot);
            }
        }
    }
}
