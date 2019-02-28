#include <Windows.h>

#include "menu_impl.h"
#include "webview_impl.h"
#include "./BrowserWindow_impl.h"

namespace {
	const wchar_t* const BrowserWindowWndClassName = L"DeskGapBrowserWindow";
}

namespace DeskGap {
    BrowserWindow::BrowserWindow(const WebView& webView, EventCallbacks&& callbacks): impl_(std::make_unique<Impl>()) {
        static bool isClassRegistered = false;
        if (!isClassRegistered) {
            isClassRegistered = true;
            WNDCLASSEXW wndClass { };
            wndClass.cbSize = sizeof(WNDCLASSEXW);
            wndClass.hInstance = GetModuleHandleW(nullptr);
            wndClass.lpszClassName = BrowserWindowWndClassName;
            wndClass.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) -> LRESULT {
                BrowserWindow* browserWindow = reinterpret_cast<BrowserWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
                if (browserWindow != nullptr) {
                    switch (msg)
                    {
                        case WM_CLOSE: {
                            browserWindow->impl_->callbacks.onClose();
                            return 0;
                        }
                        case WM_SIZE: {
                            RECT rect { };
                            GetClientRect(hwnd, &rect);
                            LONG width = rect.right - rect.left;
                            LONG height = rect.bottom - rect.top;
                            SetWindowPos(
                                browserWindow->impl_->webViewControlWnd, nullptr,
                                0, 0, width, height,
                                SWP_NOZORDER
                            );
                            browserWindow->impl_->callbacks.onResize();
                            return 0;
                        }
                    }
                }
                return DefWindowProcW(hwnd, msg, wp, lp);
            };
            wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            RegisterClassExW(&wndClass);
        }
        impl_->callbacks = std::move(callbacks);
        impl_->windowWnd = CreateWindowW(
            BrowserWindowWndClassName,
            L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
            CW_USEDEFAULT, 640, 480,
            nullptr, nullptr,
            GetModuleHandleW(nullptr),
            nullptr
        );
        SetWindowLongPtrW(impl_->windowWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        
        webView.impl_->InitControl(impl_->windowWnd);
        impl_->webViewControlWnd = webView.impl_->controlWnd;
    }

    void BrowserWindow::Show() {
        ShowWindow(impl_->windowWnd, SW_SHOW);
        UpdateWindow(impl_->windowWnd);

        ShowWindow(impl_->webViewControlWnd, SW_SHOW);
        UpdateWindow(impl_->webViewControlWnd);

        SetFocus(impl_->windowWnd);
    }

    void BrowserWindow::SetMaximizable(bool maximizable) {
        
    }
    void BrowserWindow::SetMinimizable(bool minimizable) {

    }
    void BrowserWindow::SetResizable(bool resizable) {
        
    }
    void BrowserWindow::SetHasFrame(bool hasFrame) {
        
    }

    void BrowserWindow::SetTitle(const std::string& utf8title) {
        
    }

    void BrowserWindow::SetClosable(bool closable) {
        
    }

    void BrowserWindow::SetSize(int width, int height, bool animate) {
        
    }

    void BrowserWindow::SetMaximumSize(int width, int height) {
        
    }
    void BrowserWindow::SetMinimumSize(int width, int height) {
        
    }

    void BrowserWindow::SetPosition(int x, int y, bool animate) {
        
    }

    std::array<int, 2> BrowserWindow::GetSize() {
        return { 0, 0 };
    }

    std::array<int, 2> BrowserWindow::GetPosition() {
        return { 0, 0 };
    }

    void BrowserWindow::Minimize() {

    }

    void BrowserWindow::Center() {
        
    }

    void BrowserWindow::SetMenu(const Menu* menu) {
        
    }

    void BrowserWindow::SetIcon(const std::optional<std::string>& iconPath) {
        
    }


    void BrowserWindow::Destroy() {
        SetWindowLongPtrW(impl_->windowWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
        DestroyWindow(impl_->windowWnd);
    }
    void BrowserWindow::Close() {

    }

    void BrowserWindow::PopupMenu(const Menu& menu, const std::array<int, 2>* location, int positioningItem) {
        
    }

    BrowserWindow::~BrowserWindow() = default;
}
