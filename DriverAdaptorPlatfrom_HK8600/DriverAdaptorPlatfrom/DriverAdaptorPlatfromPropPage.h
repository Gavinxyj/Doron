#pragma once

// DriverAdaptorPlatfromPropPage.h : CDriverAdaptorPlatfromPropPage ����ҳ���������


// CDriverAdaptorPlatfromPropPage : �й�ʵ�ֵ���Ϣ������� DriverAdaptorPlatfromPropPage.cpp��

class CDriverAdaptorPlatfromPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDriverAdaptorPlatfromPropPage)
	DECLARE_OLECREATE_EX(CDriverAdaptorPlatfromPropPage)

// ���캯��
public:
	CDriverAdaptorPlatfromPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_DRIVERADAPTORPLATFROM };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

