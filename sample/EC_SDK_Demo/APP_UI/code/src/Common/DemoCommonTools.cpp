//
//  DemoCommonTools.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "StdAfx.h"
#include "DemoCommonTools.h"
#include "service_os_adapt.h"
#include <fstream>

const int MAX_IMAGE_HEIGHT = 50;// 自定义图片高度
const int MAX_IMAGE_WIDTH = 55;// 自定义图片宽度
const int MAX_NUM = 256;

#define TIME_FORMAT _T("%Y-%m-%d %H:%M:%S")

CTools::CTools(void)
{
}

CTools::~CTools(void)
{
}

std::wstring CTools::string2wstring(const std::string& str)
{
    //确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
    int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    if (0 >= (nLen + 1))
    {
        return L"";
    }
    wchar_t *pUnicode = new  wchar_t[nLen + 1];
    service_memset_s(pUnicode, (nLen + 1)*sizeof(wchar_t), 0, (nLen + 1)*sizeof(wchar_t));
    ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, nLen);
    std::wstring  rt;
    rt = (wchar_t*)pUnicode;
    delete[] pUnicode;
    pUnicode = NULL;
    return rt;
}

CString CTools::UTF2UNICODE(const std::string& str)
{
    //确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
    int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    if (0 >= (nLen + 1))
    {
        return _T("");
    }
    wchar_t *pUnicode = new  wchar_t[nLen + 1];
    service_memset_s(pUnicode, (nLen + 1)*sizeof(wchar_t), 0, (nLen + 1)*sizeof(wchar_t));
    ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, nLen);
    std::wstring  rt;
    rt = (wchar_t*)pUnicode;
    CString cstr(rt.c_str());
    delete[] pUnicode;
    pUnicode = NULL;
    return cstr;
}
std::string CTools::UNICODE2UTF(const CString& cstr)
{
    char*     pElementText;
    int    iTextLen;
    std::wstring wstr = (LPCWSTR)CStringW(cstr);;
    // wide char to multi char
    iTextLen = WideCharToMultiByte(CP_UTF8,
        0,
        wstr.c_str(),
        -1,
        NULL,
        0,
        NULL,
        NULL);
    if (0 >= (iTextLen + 1))
    {
        return "";
    }
    pElementText = new char[iTextLen + 1];
    service_memset_s((void*)pElementText, sizeof(char) * (iTextLen + 1), 0, sizeof(char) * (iTextLen + 1));
    ::WideCharToMultiByte(CP_UTF8,
        0,
        wstr.c_str(),
        -1,
        pElementText,
        iTextLen,
        NULL,
        NULL);
    std::string strText;
    strText = pElementText;
    delete[] pElementText;
    pElementText = NULL;
    return strText;
}

void CTools::CString2Char(const CString &str, char* ch, unsigned int lenth)
{
    std::string stdstr = UNICODE2UTF(str);
    strncpy_s(ch, lenth * sizeof(char), stdstr.c_str(), _TRUNCATE);
}
void CTools::string2CString(const std::string& str, CString& CStr)
{
    CStr = UTF2UNICODE(str);
}
long long CTools::GetCurUTCTime()
{
    CTime cur = CTime::GetCurrentTime();
    return cur.GetTime() * 1000;
}
CString CTools::FormatUTCTime(long long& iUTCtime)
{
    CTime cur(iUTCtime / 1000);
    CString cstrTime = cur.Format(_T("%Y-%m-%d %H:%M:%S"));
    return cstrTime;
}

CString CTools::getCurrentPath()
{
    TCHAR tcPath[MAX_PATH];
    TCHAR tcFilename[MAX_PATH];
    TCHAR tcDrive[_MAX_DRIVE];
    TCHAR tcDir[_MAX_DIR];
    TCHAR tcFname[_MAX_FNAME];
    TCHAR tcExt[_MAX_EXT];

    (void)GetModuleFileName(NULL, tcFilename, _MAX_PATH);

    _tsplitpath_s(tcFilename, tcDrive, tcDir, tcFname, tcExt);
    _tcscpy_s(tcPath, tcDrive);
    _tcscat_s(tcPath, tcDir);

    CString strAppPath = tcPath;
    int nPos = strAppPath.ReverseFind(_T('\\'));
    strAppPath = strAppPath.Left(nPos);
    return strAppPath;
}

void CTools::GetIPPort(const std::string& serverURL, std::string& ip, int& port)
{
    ip.clear();
    std::string instr = serverURL;
    std::string::size_type pos = instr.find(':');
    std::string::size_type pos1 = instr.find(';');
    if (pos != std::string::npos)
    {
        ip = instr.substr(0, pos);
        std::string outPort("");
        if (std::string::npos == pos1)
        {
            //UC服务器地址172.22.8.61:8011
            outPort = instr.substr(pos + 1);
        }
        else
        {
            //SIP服务器地址，返回值有3个，必然有;为界/////
            outPort = instr.substr(pos + 1, pos1 - pos - 1);
        }
        port = atoi(outPort.c_str());
    }
    else
    {
        ip = "";
        port = 0;
    }


    return;
}
void CTools::GetIPPort(const CString& cstrserverURL, CString& cstrip, CString& cstrport)
{
    std::string  serverURL = CTools::UNICODE2UTF(cstrserverURL);
    std::string ip;
    int port;
    CTools::GetIPPort(serverURL, ip, port);
    cstrip = CTools::UTF2UNICODE(ip);
    cstrport = CTools::UTF2UNICODE(CTools::num2str(port));
}

std::string CTools::num2str(int i)
{
    char str[STRING_LENGTH] = { 0 };
    sprintf_s(str, STRING_LENGTH - 1, "%d", i);
    return std::string(str);
}

int CTools::str2num(const std::string& str)
{
    return atoi(str.c_str());
}

void CTools::ShowMessageTimeout(LPCTSTR msg, DWORD delay)
{
    MessageBoxTimeout(NULL, msg, _T("Call Notify"), MB_OK, GetSystemDefaultLangID(), delay);
}

//************************************************************************
void CTools::ReplaceParagraphTag(std::string& str)
{
    ReplaceToXMLString(str, "<DIV>", "");
    ReplaceToXMLString(str, "</DIV>", "");
    ReplaceToXMLString(str, "<div>", "");
    ReplaceToXMLString(str, "</div>", "");
    ReplaceToXMLString(str, "<P>", "");
    ReplaceToXMLString(str, "</P>", "");
    ReplaceToXMLString(str, "<p>", "");
    ReplaceToXMLString(str, "</p>", "");
}
//************************************************************************
//************************************************************************
void CTools::ReplaceSpecialTag(std::string& str)
{
    ReplaceToXMLString(str, "&amp;", "&");
    ReplaceToXMLString(str, "&lt;", "<");
    ReplaceToXMLString(str, "&gt;", ">");
    ReplaceToXMLString(str, "&apos;", "\'");
    ReplaceToXMLString(str, "&quot;", "\"");
    ReplaceToXMLString(str, "&nbsp;", " ");
    ReplaceToXMLString(str, "&amp;nbsp;", " ");
    ReplaceToXMLString(str, "&lt;BR&gt;", "\r\n");
}

//************************************************************************
void CTools::ReplaceToXMLString(std::string& str, std::string strXML, const std::string& strReplace)
{
    size_t beginPos = str.find(strXML);
    std::string tempstr = str;
    size_t len = 0;
    while (beginPos != std::string::npos)
    {
        (void)str.replace(beginPos + len, strXML.size(), strReplace);
        tempstr = str;
        len = beginPos + len + strReplace.size();
        tempstr = tempstr.substr(len);
        beginPos = tempstr.find(strXML);
    }
}


CString CTools::GetFileName(const CString & fileFullPath, BOOL bHasExt)
{
    CString returnFileNameStr = _T("");
    if (fileFullPath.IsEmpty())
    {
        return returnFileNameStr;
    }

    returnFileNameStr = fileFullPath;
    int pos = returnFileNameStr.ReverseFind('\\');
    if (pos > 0)
    {
        returnFileNameStr = returnFileNameStr.Right((returnFileNameStr.GetLength() - pos) - 1);
    }

    //不带扩展名
    if (!bHasExt)
    {
        int extPos = returnFileNameStr.ReverseFind('.');
        if (extPos > 0)
        {
            returnFileNameStr = returnFileNameStr.Left(pos);
        }
    }

    return returnFileNameStr;
}

ULONGLONG CTools::GetFileSize(const CString & filePath)
{
    ULONGLONG fileSize = 0;

    CFileStatus fs;
    if (CFile::GetStatus(filePath, fs))
    {
        fileSize = fs.m_size;
    }

    return fileSize;
}

void CTools::WriteIniConfigParam(const CString& sectionConfig, const CString& sectionName, const CString& sectionValue)
{
    CString serverParamPath = CTools::getCurrentPath() + _T("\\server.ini");
    (void)WritePrivateProfileString(sectionConfig, sectionName, sectionValue, serverParamPath);
}

void CTools::GetIniConfigParam(const CString& sectionConfig,const CString& sectionName, CString& sectionValue)
{
    CString serverParamPath = CTools::getCurrentPath() + _T("\\server.ini");
    (void)GetPrivateProfileString(sectionConfig, sectionName, _T(""), sectionValue.GetBuffer(MAX_PATH), MAX_PATH, serverParamPath);
}

CString CTools::UTCTime2LocalTime(string strTime)
{
    CString cstrDateTime(_T(""));
    _tzset();
    COleDateTime dataTime;
    (void)dataTime.ParseDateTime(
        CTools::UTF2UNICODE(strTime), LOCALE_NOUSEROVERRIDE, (MAKELANGID(LANG_NEUTRAL, SUBLANG_CHINESE_SIMPLIFIED)));
    SYSTEMTIME sysTimeUTC = { 0 };
    (void)dataTime.GetAsSystemTime(sysTimeUTC);
    SYSTEMTIME sysTimeLocal = { 0 };
    TIME_ZONE_INFORMATION *lpTimeZone = new TIME_ZONE_INFORMATION;
    (void)GetTimeZoneInformation(lpTimeZone);
    (void)SystemTimeToTzSpecificLocalTime(lpTimeZone, &sysTimeUTC, &sysTimeLocal);//UTC转本地时间

    CTime tmpTime(sysTimeLocal);
    cstrDateTime = CTools::GetLocalTimeFormat(tmpTime);
    delete lpTimeZone;
    return cstrDateTime;
}

CString CTools::GetLocalTimeFormat(const CTime& times)
{
    CString timeFormat = _T("");

    timeFormat = times.Format(TIME_FORMAT);

    return timeFormat;
}

CString CTools::GetSipNumber(CString strInputNum)
{
    int npos = strInputNum.Find(_T("@"));
    CString sipNumber;
    if (0 <= npos)
    {
        sipNumber = strInputNum.Left(strInputNum.Find(_T("@")));
    }
    else
    {
        sipNumber = strInputNum;
    }
    return sipNumber;
}

bool CTools::JudgeAllSameStar(const char* strValue)
{
    if (NULL == strValue)
    {
        return false;
    }

    unsigned int strLen = strlen(strValue);
    char strTmp[MAX_NUM];
    service_memset_s(strTmp, sizeof(strTmp),0,sizeof(strTmp));
    for (unsigned int i = 0; i < strLen;i++)
    {
        if(strValue[i]=='*')
        { 
            strTmp[i] = strValue[i];
        }
    }

    if (strcmp(strValue, strTmp) == 0)
    {
        return true;
    }
    
    return false;
}
