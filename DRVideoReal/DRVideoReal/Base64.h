// Base64.h: interface for the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_)
#define AFX_BASE64_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=48C787640052
class CBase64  
{
public:
	//##ModelId=48C78764005D
	static int DecodeBase64(const char* pSrc, unsigned char* pDst, int nSrcLen);
	//##ModelId=48C787640062
	static int EncodeBase64(const unsigned char* pSrc, char* pDst, int nSrcLen);
	//##ModelId=48C787640067
	CBase64();
	//##ModelId=48C787640068
	virtual ~CBase64();

};

#endif // !defined(AFX_BASE64_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_)
