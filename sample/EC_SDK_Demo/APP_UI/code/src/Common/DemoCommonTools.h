//
//  DemoCommonTools.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include <string>
#include <vector>
#include <list>
#include <iosfwd>
#include <map>

#ifdef WIN32
#include <tchar.h>
#include <time.h>
#include <atltime.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Iphlpapi.h"
#endif

using namespace std;

typedef struct
{
    int m_Pos;    ////�ò���ͼ�Ļ�Ϸ���ʱ��Ҫ�ã�һ��PC��ʹ��/////
    std::string umFileUrl;
    std::string umFileType;
    std::string umFileSize;
    std::string umFileName;
    std::string umFileDuration;
    std::string umTransCode;
    std::string umExtraParam;
}UMINFo;  ////UM��Ϣ�ṹ��///
struct FontInfo
{
    int         m_size;  /////��λ��PX//////
    COLORREF    m_rgb;  /////������ɫ/////
    CString     face;    //////���������/////
    bool        m_isI;   ////�Ƿ�б��////
    bool        m_isB;   ////�Ƿ�Ӵ�////
    bool        m_isU;   ////�Ƿ��»���////
    FontInfo()
    {
        m_isI = false;
        m_isB = false;
        m_isU = false;
    }
};///////������Ϣ�ṹ��///
typedef struct
{
    FontInfo m_font;
    CString Content;
    UMINFo  m_uminfo;
}IMINfo; ////������Ϣ�ṹ��///


struct PicPathInfo
{
    int index;      ///////�ؼ���ȡͼƬ��Ϣʱʹ��/////
    int pos;        ///////ͼƬ���ı��е�λ��////////
    std::string picPath;   /////ͼƬ�ı��ص�ַ//////
}; ////ͼƬ���///

struct MsgToSend
{
    std::string txtMsg;
    vector<PicPathInfo> pictures;
    MsgToSend()
    {
        txtMsg = "";
    }
};///////������Ϣ�ṹ��////

struct PicInfo
{
    std::string m_picKey;             //////ת����/:D�Ȳ�ѯ///
    std::string m_picStyle;            /////UM��ַת����ѹ�����<IMG style="" src="">��ʽ///
    std::string m_picURARStyle;        /////UM��ַת����δѹ����<IMG style="" src="">��ʽ///
    std::string m_picfullPath;        ////���ص�ַ////
    int picIndex;                     ////�ı��е�λ��///
};///////������Ϣ�ṹ��///

struct TagInfo
{
    CString m_content;             //////�������///
    CString m_Converttype;         /////ƬUM��ַת����ѹ����ĸ�ʽ///
    int TagIndex;                      ////�ı��е�λ��///
};///////������Ϣ�ṹ��///

struct PICUMInfo
{
    CString      UMURL;
    CString      UMID;
    CString      m_strLocalPath;
};///////ͼƬ�ϴ�UM�����Ϣ/////

const int EMOTION_CUSTOM_MAXCOUNT = 90;   // ���������������///

const int STRING_LENGTH = 100;//���ж����ַ����̶�����
extern "C"
{
    int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
    int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
};
#ifdef UNICODE
#define MessageBoxTimeout MessageBoxTimeoutW
#else
#define MessageBoxTimeout MessageBoxTimeoutA
#endif 

class CTools
{
private:
    CTools(void);
    ~CTools(void);
public:
    static CString UTF2UNICODE(const std::string& str);
    static std::wstring string2wstring(const std::string& str);
    static std::string UNICODE2UTF(const CString& cstr);
    static void CString2Char(const CString &str, char* ch, unsigned int lenth);
    static void string2CString(const std::string&, CString&);
    static long long GetCurUTCTime();
    static CString FormatUTCTime(long long&);
    static CString getCurrentPath();//Modified by w00321336 to fix some unreasonable code at 2015-1-21
    static void GetIPPort(const std::string& serverURL, std::string& ip, int& port);
    static void GetIPPort(const CString& cstrserverURL, CString& cstrip, CString& cstrport);
    static std::string num2str(int);
    static int str2num(const std::string& str);
    static void ShowMessageTimeout(LPCTSTR msg, DWORD delay);
    static void ReplaceParagraphTag(std::string& str);
    static void ReplaceSpecialTag(std::string& str);
    static void ReplaceToXMLString(std::string& str, std::string strXML, const std::string& strReplace);

    static CString GetFileName(const CString & fileFullPath, BOOL bHasExt);
    static ULONGLONG GetFileSize(const CString & filePath);

    static CString UTCTime2LocalTime(string strTime);
    static CString GetLocalTimeFormat(const CTime& times);

    static void WriteServerParam(const CString& sectionname, const CString& sectionvalue);
    static void GetServerParam(CString &server_Ip, CString &server_Port);
    static void WriteAccountParam(const CString& sectionname, const CString& sectionvalue);
    static void GetAccountParam(CString &login_account);
    static void WritePwdParam(const CString& sectionname, const CString& sectionvalue);
    static void GetPwdParam(CString &login_pwd);

    static CString GetSipNumber(CString strInputNum);
};
