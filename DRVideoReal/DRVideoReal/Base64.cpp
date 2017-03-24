// Base64.cpp: implementation of the CBase64 class.
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "Base64.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=48C787640067
CBase64::CBase64()
{
}

//##ModelId=48C787640068
CBase64::~CBase64()
{
}

//##ModelId=48C787640062
int CBase64::EncodeBase64(const unsigned char *pSrc, char *pDst, int nSrcLen)
{
	const char EnBase64Tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
	unsigned char c1, c2, c3;    // ���뻺��������3���ֽ�
    int nDstLen = 0;             // ������ַ�����
    int nLineLen = 0;            // ������г��ȼ���
    int nDiv = nSrcLen / 3;      // �������ݳ��ȳ���3�õ��ı���
    int nMod = nSrcLen % 3;      // �������ݳ��ȳ���3�õ�������
	
    // ÿ��ȡ3���ֽڣ������4���ַ�
    for (int i = 0; i < nDiv; i ++)
    {
        // ȡ3���ֽ�
        c1 = *pSrc++;
        c2 = *pSrc++;
        c3 = *pSrc++;
		
        // �����4���ַ�
        *pDst++ = EnBase64Tab[c1 >> 2];
        *pDst++ = EnBase64Tab[((c1 << 4) | (c2 >> 4)) & 0x3f];
        *pDst++ = EnBase64Tab[((c2 << 2) | (c3 >> 6)) & 0x3f];
        *pDst++ = EnBase64Tab[c3 & 0x3f];
        nLineLen += 4;
        nDstLen += 4;
    }
	
    // �������µ��ֽ�
    if (nMod == 1)
    {
        c1 = *pSrc++;
        *pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
        *pDst++ = EnBase64Tab[((c1 & 0x03) << 4)];
        *pDst++ = '=';
        *pDst++ = '=';
        nLineLen += 4;
        nDstLen += 4;
    }
    else if (nMod == 2)
    {
        c1 = *pSrc++;
        c2 = *pSrc++;
        *pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
        *pDst++ = EnBase64Tab[((c1 & 0x03) << 4) | ((c2 & 0xf0) >> 4)];
        *pDst++ = EnBase64Tab[((c2 & 0x0f) << 2)];
        *pDst++ = '=';
        nDstLen += 4;
    }
	
    // ����Ӹ�������
    *pDst = '\0';
	
    return nDstLen;
}


//##ModelId=48C78764005D
int CBase64::DecodeBase64(const char *pSrc, unsigned char *pDst, int nSrcLen)
{
	const char DeBase64Tab[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			62,        // '+'
			0, 0, 0,
			63,        // '/'
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61,        // '0'-'9'
			0, 0, 0, 0, 0, 0, 0,
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,        // 'A'-'Z'
			0, 0, 0, 0, 0, 0,
			26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
			39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,        // 'a'-'z'
	};
	int nDstLen;            // ������ַ�����
    int nValue;             // �����õ��ĳ�����
    int i;
	
    i = 0;
    nDstLen = 0;
	
    // ȡ4���ַ������뵽һ�����������پ�����λ�õ�3���ֽ�
    while (i < nSrcLen)
    {
        if (*pSrc != '\r' && *pSrc!='\n')
        {
            nValue = DeBase64Tab[*pSrc++] << 18;
            nValue += DeBase64Tab[*pSrc++] << 12;
            *pDst++ = (nValue & 0x00ff0000) >> 16;
            nDstLen++;
			
            if (*pSrc != '=')
            {
                nValue += DeBase64Tab[*pSrc++] << 6;
                *pDst++ = (nValue & 0x0000ff00) >> 8;
                nDstLen++;
				
                if (*pSrc != '=')
                {
                    nValue += DeBase64Tab[*pSrc++];
                    *pDst++ =nValue & 0x000000ff;
                    nDstLen++;
                }
            }
			
            i += 4;
        }
        else        // �س����У�����
        {
            pSrc++;
            i++;
        }
	}
	
    // ����Ӹ�������
    *pDst = '\0';
	
    return nDstLen;
}
