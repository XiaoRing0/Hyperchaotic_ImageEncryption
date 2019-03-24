
// Encryption_MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Encryption_MFC.h"
#include "Encryption_MFCDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include<vector>
#include <cmath>
#include<algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef PI
#define PI 3.141592658
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//?
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEncryptionMFCDlg 对话框



CEncryptionMFCDlg::CEncryptionMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENCRYPTION_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncryptionMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EN_PROGRESS, EnProgress);
	DDX_Control(pDX, IDC_DE_PROGRESS, DeProgress);
}

BEGIN_MESSAGE_MAP(CEncryptionMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHOOSE_IMG, &CEncryptionMFCDlg::OnBnClickedChooseImg)
	ON_BN_CLICKED(IDC_ENCRYPTING, &CEncryptionMFCDlg::OnBnClickedEncrypting)
	ON_BN_CLICKED(IDC_DECRYPTING, &CEncryptionMFCDlg::OnBnClickedDecrypting)
	ON_BN_CLICKED(IDC_SAVE_ENCRYPTING, &CEncryptionMFCDlg::OnBnClickedSaveEncrypting)
	ON_BN_CLICKED(IDC_SAVE_DECRYPTING, &CEncryptionMFCDlg::OnBnClickedSaveDecrypting)
	ON_BN_CLICKED(IDC_LOADENCRYPTION2EN_WINDOW, &CEncryptionMFCDlg::OnBnClickedLoadencryption2enWindow)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_UNCHANGED_CHOOSE_IMG, &CEncryptionMFCDlg::OnBnClickedUnchangedChooseImg)
END_MESSAGE_MAP()


// CEncryptionMFCDlg 消息处理程序

BOOL CEncryptionMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		
	//设置进度条En颜色
	::SendMessageA(EnProgress.GetSafeHwnd(),PBM_SETBARCOLOR,0,RGB(255, 250, 250));
	EnProgress.SetBarColor(RGB(67, 205, 128));
	//设置进度条De颜色
	::SendMessageA(DeProgress.GetSafeHwnd(), PBM_SETBARCOLOR, 0, RGB(255, 250, 250));
	DeProgress.SetBarColor(RGB(67, 205, 128));

	//获取所有窗口位置大小
	CRect rect;
	GetWindowRect(&rect);
	m_listRect.AddTail(rect);//对话框的区域
	CWnd* pWnd = GetWindow(GW_CHILD);//获取子窗体
	while (pWnd)
	{
		pWnd->GetWindowRect(rect);//子窗体的区域
		m_listRect.AddTail(rect);           //CList<CRect,CRect> m_listRect成员变量
		pWnd = pWnd->GetNextWindow();//取下一个子窗体
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncryptionMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEncryptionMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDialog::UpdateWindow();
	}
}

HCURSOR CEncryptionMFCDlg::OnQueryDragIcon()
{
	return HCURSOR();
}




//选择图片控件响应函数
void CEncryptionMFCDlg::OnBnClickedChooseImg()
{
	CString picPath;   //定义图片路径变量  
	//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
		//OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  
	CFileDialog dlg(true, _T("*.tiff;*.bmp; *.tif;*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.tiff;*.bmp ;*.jpg;)|*.tiff;*.bmp; *.jpg |ALL Files (*.*) |*.*||"), NULL);


	//打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径  
	}
	//CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
	std::string picpath = picPath.GetBuffer(0);
	lena = cv::imread(picpath, cv::IMREAD_COLOR);
	if (lena.empty())
	{
		MessageBox(_T("读取文件为空，请选择一张图像文件"));
		return;
	}
	else if (lena.rows*lena.cols < 1024 * 1024)
	{
		;
	}
	else if (lena.rows*lena.cols < 2048 * 2048)
	{
		lena = cv::imread(picpath, cv::IMREAD_REDUCED_COLOR_2);
	}
	else if (lena.rows*lena.cols < 4096 * 4096)
	{
		lena = cv::imread(picpath, cv::IMREAD_REDUCED_COLOR_4);
	}
	else
	{
		lena = cv::imread(picpath, cv::IMREAD_REDUCED_COLOR_8);
	}

	SetDlgItemText(IDC_ImagePath, picPath);
	DrawMat(lena, IDC_ORIGINAL1);
	AfxMessageBox("图像读取完成");

	// TODO: 在此添加控件通知处理程序代码
}
void CEncryptionMFCDlg::OnBnClickedUnchangedChooseImg()
{
	CString picPath;   //定义图片路径变量  
//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
	//OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  
	CFileDialog dlg(true, _T("*.tiff;*.bmp; *.tif;*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.tiff;*.bmp ;*.jpg;)|*.tiff;*.bmp; *.jpg |ALL Files (*.*) |*.*||"), NULL);


	//打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径  
	}
	//CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
	std::string picpath = picPath.GetBuffer(0);
	lena = cv::imread(picpath, cv::IMREAD_COLOR);
	if (lena.empty())
	{
		MessageBox(_T("读取文件为空，请选择一张图像文件"));
		return;
	}
	SetDlgItemText(IDC_ImagePath, picPath);
	DrawMat(lena, IDC_ORIGINAL1);
	AfxMessageBox("图像读取完成");
	// TODO: 在此添加控件通知处理程序代码
}







//加密控件响应函数
void CEncryptionMFCDlg::OnBnClickedEncrypting()
{
	CString str_encryp_password;
	//从输入密码控件获取密码，存入str_encryp_passward
	GetDlgItem(IDC_ENCRYPTION_PASSWORD)->GetWindowText(str_encryp_password);
	if (lena.empty())
	{
		AfxMessageBox("未载入图像，请先载入一张原始图像！");
		return;
	}
	else if (str_encryp_password.IsEmpty())
	{
		AfxMessageBox("密码为空，请重新输入8位密码！");
		return;
	}
	else if (str_encryp_password.GetLength()!=8)
	{
		AfxMessageBox("密码长度错误，请重新输入8位密码！");
		return;
	}
	for(int i=0;i< str_encryp_password.GetLength();++i)
	{
		if (str_encryp_password[i]<'0' || str_encryp_password[i]>'9')
		{
			AfxMessageBox("密码数据类型错误，请输入范围在0-9之间的数字！");
			return;
		}
	}
	//动态申请混沌数组内存
	double *x_chaos = new double[lena.rows * lena.cols * lena.channels()];
	double *y_chaos = new double[lena.rows * lena.cols * lena.channels()];
	//结合图像特征信息初始化初值
	double tempx_last = 0.1*(str_encryp_password[0]-'0')+ 0.01*(str_encryp_password[1] - '0');
	double tempy_last = 0.1*(str_encryp_password[2] - '0') + 0.01*(str_encryp_password[3] - '0');
	double tempz_last = 0.1*(str_encryp_password[4] - '0') + 0.01*(str_encryp_password[5] - '0');
	double tempw_last = 0.1*(str_encryp_password[6] - '0') + 0.01*(str_encryp_password[7] - '0');
	double tempx_new, tempy_new, tempz_new, tempw_new;
	//离散采样时间
	double tt0 = 0.001;
	//需舍去的元素个数
	int num_ignore = 100000;
	//迭代混沌序列
	for (int i = 0; i < lena.rows * lena.cols * lena.channels() + num_ignore; ++i)
	{
		tempx_new = tempx_last + tt0 * (24 * (tempy_last - tempx_last) + 4 * (1 + 0.02 * tempw_last * tempw_last) * tempy_last);
		tempy_new = tempy_last + tt0 * (19 * tempx_last - tempx_last * tempz_last);
		tempz_new = tempz_last + tt0 * (tempx_last * tempx_last - 9 * tempz_last);
		tempw_new = tempw_last + tt0 * tempy_last;
		//舍去前10000次迭代结果即忽略瞬态行为
		if (i >= num_ignore)
		{
			*(x_chaos + i - num_ignore) = tempx_new;
			*(y_chaos + i - num_ignore) = tempy_new;
		}
		tempx_last = tempx_new;
		tempy_last = tempy_new;
		tempz_last = tempz_new;
		tempw_last = tempw_new;
	}
	//对混沌序列进行处理
	double x_max = *std::max_element(x_chaos, x_chaos + lena.rows * lena.cols * lena.channels() - 1);
	double x_min = *std::min_element(x_chaos, x_chaos + lena.rows * lena.cols * lena.channels() - 1);
	double y_max = *std::max_element(y_chaos, y_chaos + lena.rows * lena.cols * lena.channels() - 1);
	double y_min = *std::min_element(y_chaos, y_chaos + lena.rows * lena.cols * lena.channels() - 1);
	for (int i = 0; i < lena.rows * lena.cols * lena.channels(); ++i)
	{
		//x归一化,三角变换，取模
		*(x_chaos + i) = (*(x_chaos + i) - x_min) / (x_max - x_min);
		*(x_chaos + i) = 1.0 / PI * asin(sqrt(*(x_chaos + i)));
		*(x_chaos + i) = int(floor(pow(10, 8)*(*(x_chaos + i)))) % 256;
		*(y_chaos + i) = (*(y_chaos + i) - y_min) / (y_max - y_min);
		*(y_chaos + i) = 1.0 / PI * asin(sqrt(*(y_chaos + i)));
		*(y_chaos + i) = int(floor(pow(10, 8)*(*(y_chaos + i)))) % 256;
	}

	//初始化加密标号
	count_n = 0;
	count_m = 0;
	//设置进度条范围、步长
	EnProgress.SetRange32(0, lena.rows * lena.cols * lena.channels() - 1);
	int nFirstStep = EnProgress.SetStep(1);
	//调用加密函数对图像进行加密
	EncrytingMat(lena, x_chaos, y_chaos);
	//绘制图形
	DrawMat(encryption_lena, IDC_ENCRYPTION1);
	AfxMessageBox("图像加密完成");

	//释放空间防止内存泄漏
    //置空指针
	delete[]x_chaos;
	delete[]y_chaos;
	x_chaos = nullptr;
	y_chaos = nullptr;
	// TODO: 在此添加控件通知处理程序代码
}
//解密控件相应函数
void CEncryptionMFCDlg::OnBnClickedDecrypting()
{

	CString str_decryp_password;
	//从输入密码控件获取密码，存入str_encryp_passward
	GetDlgItem(IDC_DECRYPTION_PASSWORD)->GetWindowText(str_decryp_password);
	if (encryption_lena.empty())
	{
		AfxMessageBox("未载入加密图像，请先对原始图像进行加密！");
		return;
	}
	else if (str_decryp_password.IsEmpty())
	{
		AfxMessageBox("密码为空，请重新输入8位密码！");
		return;
	}
	else if (str_decryp_password.GetLength() != 8)
	{
		AfxMessageBox("密码长度错误，请重新输入8位密码！");
		return;
	}
	for (int i = 0; i < str_decryp_password.GetLength(); ++i)
	{
		if (str_decryp_password[i]<'0' || str_decryp_password[i]>'9')
		{
			AfxMessageBox("密码数据类型错误，请输入范围在0-9之间的数字！");
			return;
		}
	}
	//动态申请混沌数组内存
	double *x_chaos = new double[encryption_lena.rows * encryption_lena.cols * encryption_lena.channels()];
	double *y_chaos = new double[encryption_lena.rows * encryption_lena.cols * encryption_lena.channels()];
	//结合图像特征信息初始化初值
	double tempx_last = 0.1*(str_decryp_password[0] - '0') + 0.01*(str_decryp_password[1] - '0');
	double tempy_last = 0.1*(str_decryp_password[2] - '0') + 0.01*(str_decryp_password[3] - '0');
	double tempz_last = 0.1*(str_decryp_password[4] - '0') + 0.01*(str_decryp_password[5] - '0');
	double tempw_last = 0.1*(str_decryp_password[6] - '0') + 0.01*(str_decryp_password[7] - '0');
	double tempx_new, tempy_new, tempz_new, tempw_new;
	//离散采样时间
	double tt0 = 0.001;
	//需舍去的元素个数
	int num_ignore = 100000;
	//迭代混沌序列
	for (int i = 0; i < encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() + num_ignore; ++i)
	{
		tempx_new = tempx_last + tt0 * (24 * (tempy_last - tempx_last) + 4 * (1 + 0.02 * tempw_last * tempw_last) * tempy_last);
		tempy_new = tempy_last + tt0 * (19 * tempx_last - tempx_last * tempz_last);
		tempz_new = tempz_last + tt0 * (tempx_last * tempx_last - 9 * tempz_last);
		tempw_new = tempw_last + tt0 * tempy_last;
		//舍去前10000次迭代结果即忽略瞬态行为
		if (i >= num_ignore)
		{
			*(x_chaos + i - num_ignore) = tempx_new;
			*(y_chaos + i - num_ignore) = tempy_new;
		}
		tempx_last = tempx_new;
		tempy_last = tempy_new;
		tempz_last = tempz_new;
		tempw_last = tempw_new;
	}
	//对混沌序列进行处理
	double x_max = *std::max_element(x_chaos, x_chaos + encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() - 1);
	double x_min = *std::min_element(x_chaos, x_chaos + encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() - 1);
	double y_max = *std::max_element(y_chaos, y_chaos + encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() - 1);
	double y_min = *std::min_element(y_chaos, y_chaos + encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() - 1);
	for (int i = 0; i < encryption_lena.rows * encryption_lena.cols * encryption_lena.channels(); ++i)
	{
		//x归一化,三角变换，取模
		*(x_chaos + i) = (*(x_chaos + i) - x_min) / (x_max - x_min);
		*(x_chaos + i) = 1.0 / PI * asin(sqrt(*(x_chaos + i)));
		*(x_chaos + i) = int(floor(pow(10, 8)*(*(x_chaos + i)))) % 256;
		*(y_chaos + i) = (*(y_chaos + i) - y_min) / (y_max - y_min);
		*(y_chaos + i) = 1.0 / PI * asin(sqrt(*(y_chaos + i)));
		*(y_chaos + i) = int(floor(pow(10, 8)*(*(y_chaos + i)))) % 256;
	}

	//设置进度条范围、步长
	DeProgress.SetRange32(0, encryption_lena.rows * encryption_lena.cols * encryption_lena.channels() - 1);
	int nFirstStep = DeProgress.SetStep(1);
	//调用解密函数对图像进行解密
	DecrytingMat(encryption_lena, x_chaos, y_chaos);
	//绘制图形
	DrawMat(decryption_lena, IDC_DECRYPTION1);
	AfxMessageBox("图像解密完成");

	//释放空间防止内存泄漏
    //置空指针
	delete[]x_chaos;
	delete[]y_chaos;
	x_chaos = nullptr;
	y_chaos = nullptr;
	// TODO: 在此添加控件通知处理程序代码
}

//保存加密控件响应函数
void CEncryptionMFCDlg::OnBnClickedSaveEncrypting()
{
	if (encryption_lena.empty())
	{
		AfxMessageBox("未检测到加密图像，请先进行加密");
		return;
	}
	CString picPath;   //定义图片路径变量  
	CString FileName;   //定义图片路径变量 
//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
	//OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("image files (*.tiff;*.bmp ;*.jpg;)|*.tiff;*.bmp; *.jpg |ALL Files (*.*) |*.*||"), AfxGetMainWnd());


	//打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("保存加密图片");
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径
		FileName = dlg.GetFileName(); //获取文件名
		picPath += _T(".bmp");
		USES_CONVERSION;
		if(!picPath.IsEmpty())
		{
			//CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
			std::string picpath = picPath.GetBuffer(0);
			cv::imwrite(picpath, encryption_lena);
			AfxMessageBox("加密图像保存成功");
			//保存操作
		}
	}
	
	// TODO: 在此添加控件通知处理程序代码
}

//保存解密控件响应函数
void CEncryptionMFCDlg::OnBnClickedSaveDecrypting()
{
	if (decryption_lena.empty())
	{
		AfxMessageBox("未检测到加密图像，请先进行加密");
		return;
	}
	CString picPath;   //定义图片路径变量  
	CString FileName;   //定义图片路径变量 
//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
	//OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("image files (*.tiff;*.bmp ;*.jpg;)|*.tiff;*.bmp; *.jpg |ALL Files (*.*) |*.*||"), AfxGetMainWnd());


	//打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("保存解密图片");
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径
		FileName = dlg.GetFileName(); //获取文件名
		picPath += _T(".bmp");
		USES_CONVERSION;
		if (!picPath.IsEmpty())
		{
			//CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
			std::string picpath = picPath.GetBuffer(0);
			cv::imwrite(picpath, decryption_lena);
			AfxMessageBox("解密图像保存成功");
			//保存操作
		}
	}

	// TODO: 在此添加控件通知处理程序代码
}

//载入密图至加密窗口控件响应函数
void CEncryptionMFCDlg::OnBnClickedLoadencryption2enWindow()
{
	CString picPath;   //定义图片路径变量  
//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
	//OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);   //选择文件对话框  
	CFileDialog dlg(true, _T("*.tiff;*.bmp; *.tif;*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.tiff;*.bmp ;*.jpg;)|*.tiff;*.bmp; *.jpg |ALL Files (*.*) |*.*||"), NULL);


	//打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();  //获取图片路径  
	}
	//CString to string  使用这个方法记得字符集选用“使用多字节字符”，不然会报错  
	std::string picpath = picPath.GetBuffer(0);
	encryption_lena = cv::imread(picpath, cv::IMREAD_COLOR);
	if (encryption_lena.empty())
	{
		MessageBox(_T("读取文件为空，请选择一张图像文件"));
		return;
	}
	SetDlgItemText(IDC_ImagePath, picPath);
	DrawMat(encryption_lena, IDC_ENCRYPTION1);
	if (!encryption_lena.empty())
	{
		AfxMessageBox("密文图像读取成功");
	}
	// TODO: 在此添加控件通知处理程序代码
}
//绘图函数
void CEncryptionMFCDlg::DrawMat(cv::Mat & img, UINT nID)
{
	cv::Mat imgTmp;
	CRect rect;
	GetDlgItem(nID)->GetClientRect(&rect);  // 获取控件大小
	cv::resize(img, imgTmp, cv::Size(rect.Width(), rect.Height()));// 缩小或放大Mat并备份

	// 转一下格式 ,这段可以放外面,
	switch (imgTmp.channels())
	{
	case 1:
		cv::cvtColor(imgTmp, imgTmp, CV_GRAY2BGRA); // GRAY单通道
		break;
	case 3:
		cv::cvtColor(imgTmp, imgTmp, CV_BGR2BGRA);  // BGR三通道
		break;
	default:
		break;
	}

	int pixelBytes = imgTmp.channels()*(imgTmp.depth() + 1); // 计算一个像素多少个字节 
	// 制作bitmapinfo(数据头)
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 8 * pixelBytes;
	bitInfo.bmiHeader.biWidth = imgTmp.cols;
	bitInfo.bmiHeader.biHeight = -imgTmp.rows;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;
	// Mat.data + bitmap数据头 -> MFC
	CDC *pDC = GetDlgItem(nID)->GetDC();
	::StretchDIBits(
		pDC->GetSafeHdc(),
		0, 0, rect.Width(), rect.Height(),
		0, 0, rect.Width(), rect.Height(),
		imgTmp.data,
		&bitInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
	ReleaseDC(pDC);
}
//定义图像加密函数
void CEncryptionMFCDlg::EncrytingMat(cv::Mat & Leimg, const double Enx_chaos[], const double Eny_chaos[])
{
	std::vector<int> lenarow(Leimg.cols);
	encryption_lena = Leimg.clone();
	//申明变换位数变量
	int num_shf;

	int tempCount_n = 0;
	int tempCount_m = 0;
	//进行行移位与扩散
	//注意的是行变换使用的是x混沌序列
	for (int k = 0; k < Leimg.channels(); ++k)
	{
		for (int i = 0; i < Leimg.rows; ++i)
		{
			//读取图像矩阵的行数据到lenarow数组
			for (int j = 0; j < Leimg.cols; ++j)
			{
				lenarow[j] = Leimg.at<cv::Vec3b>(i, j)[k];
			}
			//强制类型转换，根据x混沌序列中确定行移位的位数
			num_shf = static_cast<int>(*(Enx_chaos + tempCount_n));
			//调用自定义的数组循环右移函数，对图像矩阵的行进行循环移位
			array_rightshift(lenarow, num_shf);
			//判断若为第一行，则直接与x混沌序列进行异或；不为第一行，则先与图像矩阵前一行异或再与x混沌序列异或
			if (i == 0)
			{
				for (int j = 0; j < Leimg.cols; ++j)
				{
					//给加密像素矩阵赋值
					int temp = lenarow[j] ^ static_cast<int>(*(Enx_chaos + tempCount_n));
					encryption_lena.at<cv::Vec3b>(i, j)[k] = temp;
					++tempCount_n;
				}
			}
			else
			{
				for (int j = 0; j < Leimg.cols; j++)
				{
					//给加密像素矩阵赋值
					int temp = lenarow[j] ^ static_cast<int>(encryption_lena.at<cv::Vec3b>(i - 1, j)[k]);
					temp = temp ^ static_cast<int>(*(Enx_chaos + tempCount_n));
					encryption_lena.at<cv::Vec3b>(i, j)[k] = temp;
					++tempCount_n;
				}
			}
		}
	}

	std::vector<int> lenacols(Leimg.rows);
	//进行列移位与扩散
	//注意的是列变换使用的是y混沌序列
	for (int k = 0; k < Leimg.channels(); ++k)
	{
		for (int j = 0; j < Leimg.cols; ++j)
		{
			//读取图像矩阵的行数据到lenacols数组
			for (int i = 0; i < Leimg.rows; ++i)
			{
				lenacols[i] = encryption_lena.at<cv::Vec3b>(i, j)[k];
			}
			//强制类型转换，根据y混沌序列中确定列移位的位数
			num_shf = static_cast<int>(*(Eny_chaos + tempCount_m));
			//调用自定义的数组循环右移函数，对图像矩阵的列进行循环移位
			array_rightshift(lenacols, num_shf);
			//判断若为第一列，则直接与y混沌序列进行异或；不为第一列，则先与图像矩阵前一列异或再与y混沌序列异或
			if (j == 0)
			{
				for (int i = 0; i < Leimg.rows; ++i)
				{
					//给加密像素矩阵赋值
					int temp = lenacols[i] ^ static_cast<int>(*(Eny_chaos + tempCount_m));
					encryption_lena.at<cv::Vec3b>(i, j)[k] = temp;
					++tempCount_m;
				}
			}
			else
			{
				for (int i = 0; i < Leimg.rows; ++i)
				{
					//给加密像素矩阵赋值
					int temp = lenacols[i] ^ encryption_lena.at<cv::Vec3b>(i, j - 1)[k];
					temp = temp ^ static_cast<int>(*(Eny_chaos + tempCount_m));
					encryption_lena.at<cv::Vec3b>(i, j)[k] = temp;
					++tempCount_m;
				}
			}
			EnProgress.SetPos((tempCount_m-1 )* 1);//设置一个位置
		}
	}
	count_n = tempCount_n;
	count_m = tempCount_m;
}

//定义图像解密函数
void CEncryptionMFCDlg::DecrytingMat(cv::Mat & Enimg, const double Enx_chaos[], const double Eny_chaos[])
{
	//int tempCount_n = count_n - 1;
	//int tempCount_m = count_m - 1;
	int tempCount_n = Enimg.rows * Enimg.cols * Enimg.channels() - 1;
	int tempCount_m = Enimg.rows * Enimg.cols * Enimg.channels() - 1;
	decryption_lena = Enimg.clone();
	std::vector<int> lenacols(Enimg.rows);
	//反向逐列遍历加密图像矩阵
	for (int k = Enimg.channels() - 1; k >= 0; k--)
	{
		for (int j = Enimg.cols - 1; j >= 0; j--)
		{
			//判断是否为第一列，执行与加密相反的操作
			if (j == 0)
			{
				for (int i = Enimg.rows - 1; i >= 0; i--)
				{
					lenacols[i] = static_cast<int>(Enimg.at<cv::Vec3b>(i, j)[k]) ^ static_cast<int>(*(Eny_chaos + tempCount_m));
					tempCount_m--;
				}
			}
			else
			{
				for (int i = Enimg.rows - 1; i >= 0; i--)
				{
					lenacols[i] = static_cast<int>(Enimg.at<cv::Vec3b>(i, j)[k]) ^ static_cast<int>(*(Eny_chaos + tempCount_m));
					lenacols[i] = lenacols[i] ^ static_cast<int>(Enimg.at<cv::Vec3b>(i, j - 1)[k]);
					tempCount_m--;
				}
			}
			int num_shf = Enimg.rows - static_cast<int>(*(Eny_chaos + tempCount_m + 1));
			array_rightshift(lenacols, num_shf);
			for (int i = 0; i < Enimg.rows; i++)
			{
				decryption_lena.at<cv::Vec3b>(i, j)[k] = lenacols[i];
			}
		}
	}

	std::vector<int> lenarow(Enimg.cols);
	//进行行解密
	//反向逐行遍历加密图像矩阵
	for (int k = Enimg.channels() - 1; k >= 0; k--)
	{
		for (int i = Enimg.rows - 1; i >= 0; i--)
		{
			//判断是否为第一列，执行与加密相反的操作
			if (i == 0)
			{
				for (int j = Enimg.cols - 1; j >= 0; j--)
				{
					lenarow[j] = static_cast<int>(decryption_lena.at<cv::Vec3b>(i, j)[k]) ^ static_cast<int>(*(Enx_chaos + tempCount_n));
					tempCount_n--;
				}
			}
			else
			{
				for (int j = Enimg.cols - 1; j >= 0; j--)
				{
					lenarow[j] = static_cast<int>(decryption_lena.at<cv::Vec3b>(i, j)[k]) ^ static_cast<int>(*(Enx_chaos + tempCount_n));
					lenarow[j] = lenarow[j] ^ static_cast<int>(decryption_lena.at<cv::Vec3b>(i - 1, j)[k]);
					tempCount_n--;
				}
			}
			int num_shf = Enimg.cols - static_cast<int>(*(Enx_chaos + tempCount_n + 1));
			array_rightshift(lenarow, num_shf);
			for (int j = 0; j < Enimg.cols; j++)
			{
				decryption_lena.at<cv::Vec3b>(i, j)[k] = lenarow[j];
			}
			DeProgress.SetPos(Enimg.rows * Enimg.cols * Enimg.channels() - tempCount_n);//设置一个位置
		}
	}
}



void CEncryptionMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_listRect.GetCount() > 0)
	{
		CRect dlgNow;
		GetWindowRect(&dlgNow);
		POSITION pos = m_listRect.GetHeadPosition();//第一个保存的是对话框的Rect  

		CRect dlgSaved;
		dlgSaved = m_listRect.GetNext(pos);
		ScreenToClient(dlgNow);

		float x = dlgNow.Width() * 1.0 / dlgSaved.Width();//根据当前和之前保存的对话框的宽高求比例  
		float y = dlgNow.Height()  *1.0 / dlgSaved.Height();
		ClientToScreen(dlgNow);

		CRect childSaved;

		CWnd* pWnd = GetWindow(GW_CHILD);
		while (pWnd)
		{
			childSaved = m_listRect.GetNext(pos);//依次获取子窗体的Rect  
			childSaved.left = dlgNow.left + (childSaved.left - dlgSaved.left)*x;//根据比例调整控件上下左右距离对话框的距离  
			childSaved.right = dlgNow.right + (childSaved.right - dlgSaved.right)*x;
			childSaved.top = dlgNow.top + (childSaved.top - dlgSaved.top)*y;
			childSaved.bottom = dlgNow.bottom + (childSaved.bottom - dlgSaved.bottom)*y;
			ScreenToClient(childSaved);
			pWnd->MoveWindow(childSaved);
			pWnd = pWnd->GetNextWindow();
		}
	}
	// TODO: 在此处添加消息处理程序代码
}


