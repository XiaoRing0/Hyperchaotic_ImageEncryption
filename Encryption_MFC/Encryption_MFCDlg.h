
// Encryption_MFCDlg.h: 头文件
//

#pragma once

// CEncryptionMFCDlg 对话框
class CEncryptionMFCDlg : public CDialogEx
{
// 构造
public:
	CEncryptionMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENCRYPTION_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChooseImg();
public:


	//添加成员变量行列标号
	int count_n;
	int count_m;
	//原图、加密、解密图像数据
	cv::Mat lena;
	cv::Mat encryption_lena;
	cv::Mat decryption_lena;
	CProgressCtrl EnProgress;
	CProgressCtrl DeProgress;
	//缩放窗体链表
	CList<CRect, CRect&> m_listRect;

	afx_msg void DrawMat(cv::Mat & img, UINT nID);
	afx_msg void OnBnClickedEncrypting();
	afx_msg void OnBnClickedDecrypting();
	afx_msg void EncrytingMat(cv::Mat & Enimg, const double Enx_chaos[], const double Eny_chaos[]);
	afx_msg void DecrytingMat(cv::Mat & Deimg, const double Enx_chaos[], const double Eny_chaos[]);
	afx_msg void OnBnClickedSaveEncrypting();
	afx_msg void OnBnClickedSaveDecrypting();
	afx_msg void OnBnClickedLoadencryption2enWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedUnchangedChooseImg();
};
//数组循环右移函数声明
template <typename T>
void array_rightshift(std::vector<T> &a, int &N);
//数组循环右移函数定义
template <typename T>
void array_rightshift(std::vector<T> &a, int &N)
{
	//采用空间换时间，构建等长临时数组
	//将原数组后num_shift1位（移位位数）元素放置临时数组前面，将原数组前面的元素放置临时数组后面，将临时数组赋值给原数组
	int bitnum = static_cast<int>(a.size());
	int num_shift1 = N % bitnum;
	std::vector<T> temp(bitnum);
	for (int i = 0; i < num_shift1; i++)
	{
		temp[i] = a[bitnum - num_shift1 + i];
	}
	for (int j = 0; j < bitnum - num_shift1; j++)
	{
		temp[j + num_shift1] = a[j];
	}
	for (int k = 0; k < bitnum; k++)
	{
		a[k] = temp[k];
	}
}
