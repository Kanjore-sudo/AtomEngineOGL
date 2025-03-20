#include "AtomEngine.hpp"
#include <DirectXMath.h>


using namespace AtomEngine;


LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}




Window::Window(std::wstring className, std::wstring title, int w, int h)
{

	this->className = className;
	this->title = title;
	this->width = w;
	this->height = h;
	this->hInstance = GetModuleHandle(NULL);
	this->hWnd = NULL;
}


Window::~Window() {}


bool Window::Create()
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->className.data();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBoxW(NULL, L"Error al registrar la ventana", L"AtomEngine-ERROR", MB_ICONERROR);
		return false;
	}

	this->hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		this->className.data(),
		this->title.data(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		this->width,
		this->height,
		NULL, NULL,
		this->hInstance,
		this
	);

	if (this->hWnd == NULL)
	{
		MessageBox(NULL, L"Error al crear la ventana", L"AtomEngine-ERROR", MB_ICONERROR);
		return false;
	}
	this->InitDirect2D();
	return true;
}


void Window::showWindow()
{
	AtomError(L"show window");
	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);
}

HRESULT Window::InitDirect2D()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->pFactory);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error al iniciar Direct2D", L"AtomEngine-ERROR", MB_ICONERROR);
		return hr;
	}

	D2D1_SIZE_U size = D2D1::SizeU(1080, 720);
	hr = this->pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(this->hWnd, size),
		&this->pRenderTarget
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error al crear el render target", L"AtomEngine-ERROR", MB_ICONERROR);
		return hr;
	}

}

HRESULT Window::AtomLoadImage(ID2D1HwndRenderTarget* renderTarget, const wchar_t* ruta, ID2D1Bitmap** ppBitmap)
{
	AtomError(L"Entra al load image");
	HRESULT hr = S_OK;

	IWICImagingFactory* pWICFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	AtomError(L"se crean las variables del loadImg");
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));

	if (FAILED(hr))
	{
		AtomError(L"No se puedo crear el WICFactory");
		return hr;
	}

	hr = pWICFactory->CreateDecoderFromFilename(ruta, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);

	if (FAILED(hr))
	{
		AtomError(L"No se puedo crear el Decoder");
		return hr;
	}

	hr = pDecoder->GetFrame(0, &pFrame);

	if (FAILED(hr))
	{
		AtomError(L"No se puedo crear el Frame");
		return hr;
	}

	hr = pWICFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hr))
	{
		AtomError(L"No se puedo crear el Converter");
		return hr;
	}

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut);

	if (FAILED(hr))
	{
		AtomError(L"No se puedo Inicializar la conversion");
		return hr;
	}

	hr = this->pRenderTarget->CreateBitmapFromWicBitmap(pConverter, ppBitmap);

	if (pConverter) pConverter->Release();
	if (pFrame) pFrame->Release();
	if (pDecoder) pDecoder->Release();
	if (pWICFactory) pWICFactory->Release();

	AtomError(L"Sale del load image");

	if (hr = S_OK)
	{
		AtomError(L"Devuelve S_OK");
	}
	return hr;
}


//bucle

int Window::ProcesInit(AtomEngine::GameObject* scene)
{
	AtomError(L"Iniciando proces");
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{

			this->pRenderTarget->BeginDraw();

			this->pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 1.0f));
			scene->Process(this);
			
			this->pRenderTarget->EndDraw();
		}
	}

	if (this->pFactory) this->pFactory->Release();
	if (this->pRenderTarget) this->pRenderTarget->Release();

	return (int)msg.wParam;
}
