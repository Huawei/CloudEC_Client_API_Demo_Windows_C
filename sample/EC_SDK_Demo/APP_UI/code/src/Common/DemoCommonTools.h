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
    int m_Pos;    ////该参数图文混合发送时需要用，一般PC端使用/////
    std::string umFileUrl;
    std::string umFileType;
    std::string umFileSize;
    std::string umFileName;
    std::string umFileDuration;
    std::string umTransCode;
    std::string umExtraParam;
}UMINFo;  ////UM消息结构体///
struct FontInfo
{
    int         m_size;  /////单位是PX//////
    COLORREF    m_rgb;  /////字体颜色/////
    CString     face;    //////字体的名称/////
    bool        m_isI;   ////是否斜体////
    bool        m_isB;   ////是否加粗////
    bool        m_isU;   ////是否下划线////
    FontInfo()
    {
        m_isI = false;
        m_isB = false;
        m_isU = false;
    }
};///////发送消息结构体///
typedef struct
{
    FontInfo m_font;
    CString Content;
    UMINFo  m_uminfo;
}IMINfo; ////解析消息结构体///


struct PicPathInfo
{
    int index;      ///////控件提取图片信息时使用/////
    int pos;        ///////图片在文本中的位置////////
    std::string picPath;   /////图片的本地地址//////
}; ////图片标记///

struct MsgToSend
{
    std::string txtMsg;
    vector<PicPathInfo> pictures;
    MsgToSend()
    {
        txtMsg = "";
    }
};///////发送消息结构体////

struct PicInfo
{
    std::string m_picKey;             //////转换成/:D等查询///
    std::string m_picStyle;            /////UM地址转换成压缩后的<IMG style="" src="">格式///
    std::string m_picURARStyle;        /////UM地址转换成未压缩的<IMG style="" src="">格式///
    std::string m_picfullPath;        ////本地地址////
    int picIndex;                     ////文本中的位置///
};///////发送消息结构体///

struct TagInfo
{
    CString m_content;             //////特殊符号///
    CString m_Converttype;         /////片UM地址转换成压缩后的格式///
    int TagIndex;                      ////文本中的位置///
};///////发送消息结构体///

struct PICUMInfo
{
    CString      UMURL;
    CString      UMID;
    CString      m_strLocalPath;
};///////图片上传UM后的信息/////

const int EMOTION_CUSTOM_MAXCOUNT = 90;   // 表情符号数量上限///

const int STRING_LENGTH = 100;//所有对外字符串固定长度
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
