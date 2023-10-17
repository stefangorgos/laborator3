
// lab1View.cpp : implementation of the Clab1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab1.h"
#endif

#include "lab1Doc.h"
#include "lab1View.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab1View

IMPLEMENT_DYNCREATE(Clab1View, CView)

BEGIN_MESSAGE_MAP(Clab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Clab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Clab1View construction/destruction

Clab1View::Clab1View() noexcept
{
	// TODO: add construction code here

}

Clab1View::~Clab1View()
{
}

BOOL Clab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

double myFunction(double x, double eps) {
	double result = x;
	double t = x;
	double k = 1;
	while (fabs(t) >= eps) {
		k++;
		t *= x * x * (2*k-3)/(2*k-1);
		result += t;
	}
	return 2 * result;
}

// Clab1View drawing

void Clab1View::OnDraw(CDC* pDC)
{
	Clab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	double a = -0.99, b = 0.99;
	double precizia = 0.0001;
	int nseg = 130;
	double step = (b - a) / nseg;
	double scalex = 100.0;
	double scaley = 60.0;
	double x, y;
	
	CPen penAxa(PS_SOLID, 2, RGB(0, 0, 255));
	CPen penCos(PS_SOLID, 1, RGB(255, 0, 0));
	CPen pengrad(PS_SOLID, 1, RGB(190, 190, 190));
	CPen* pOLDPen = NULL;
	CRect rcClient;	
	GetClientRect(&rcClient);
	CPoint centerx = rcClient.CenterPoint().x;
	CPoint centery = rcClient.CenterPoint().y;
	pOLDPen = pDC->SelectObject(&penAxa);

	//Trasam axele
	pDC->SelectObject(&penAxa);
	pDC->MoveTo(0, rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 1, rcClient.CenterPoint().y);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height() - 1);


	//Graficul functiei Standarte
	step = 0.015;
	for (x = a; x <= b; x+=step)
	{
		y = log(1 + x) - log(1 - x);
		pDC->SetPixel(rcClient.CenterPoint().x + (int)(x * scalex), rcClient.CenterPoint().y - (int)(y * scaley), RGB(0, 255, 0));
	}
	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->SetTextAlign(TA_TOP + TA_LEFT);
	pDC->TextOutW(0, 0, L"log(1 + x) - log(1 - x)");

	//Graficul functiei Proprii
	pDC->SelectObject(&penCos);
	x = a;
	y = myFunction(x, precizia);
	pDC->MoveTo(rcClient.CenterPoint().x + (int)(x * scalex), rcClient.CenterPoint().y - (int)(y * scaley));
	for (int i = 1; i <= nseg; i++)
	{
		x += step;
		y = myFunction(x, precizia);
		pDC->LineTo(rcClient.CenterPoint().x + (int)(x * scalex), rcClient.CenterPoint().y - (int)(y * scaley));
	}
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetTextAlign(TA_TOP + TA_RIGHT);
	pDC->TextOutW(rcClient.Width() - 1, 0, L"y=myFunction(x,eps)");
}


// Clab1View printing


void Clab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Clab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Clab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Clab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Clab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Clab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Clab1View diagnostics

#ifdef _DEBUG
void Clab1View::AssertValid() const
{
	CView::AssertValid();
}

void Clab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab1Doc* Clab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab1Doc)));
	return (Clab1Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab1View message handlers
