//Exemplo com a api Win32


#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#define BOTAO_ENTENDIDO 9990

// Nome da classe Main (janela) 
static TCHAR szWindowClass[] = _T("win32Main");

// Titulo da janela 
static TCHAR szTitle[] = _T("Win32 Exemplo Basico");

HINSTANCE hInst;

// Função que trata os eventos da janela.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain é a função main para aplicações Win32
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("A criação falhou"),
			_T(""),
			NULL);

		return 1;
	}

	hInst = hInstance; // Gerenciador de instância

	HWND hWnd = CreateWindow(
		szWindowClass, // szWindowClass: Nome da aplicação  
		szTitle, //  titulo da janela 
		WS_OVERLAPPEDWINDOW, // tipo de janela
		CW_USEDEFAULT, CW_USEDEFAULT, // posição inicial (horizontal, vertical)
		800, 600,  //  tamanho inicial 800x600 
		NULL, // pai da janela (não tem, é a raíz)
		NULL, // menu (não tem)
		hInstance,  
		NULL // dados adicionais 
	);

	HWND hwndButton = CreateWindow(
		L"BUTTON",  // Classe predefinida
		L"Entendido",      // Texto do botão
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		375,         // horizontal 
		450,         // vertical 
		100,50,    // Tamanho 100x50
		hWnd,       // Janela pai
		(HMENU)BOTAO_ENTENDIDO,       
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), // Quem vai tratar esse evento é a janela pai
		NULL);      // Dados adicionais(não tem)

	// Criação falhou
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Falha ao criar janela"),
			_T(""),
			NULL);

		return 1;
	}

	// É preciso tornar a janela visivel  
	ShowWindow(
		hWnd, // : valor retornado pela função de criação da janela 
		nCmdShow
	);
	// Atualiza a janela
	UpdateWindow(hWnd);

	// Loop de mensagens  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  Função que processa os eventos
//  WM_PAINT    Desenha a janela
//  WM_DESTROY Destroi a janela 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR mensagem[] = _T("Bem vindo a um exemplo de janela com C++ e a Win32 API");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
  
		TextOut(hdc,
			5, 5,
			mensagem, _tcslen(mensagem)); 

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BOTAO_ENTENDIDO:
		{
			MessageBox(NULL,
				_T("Você clicou no botão"),
				_T("Olha só:"),
				NULL);
		}
		break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}