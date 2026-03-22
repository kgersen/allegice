// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#define WINVER 0x0601  
#define _WIN32_WINNT 0x0601  

// #include <SDKDDKVer.h>

//// Modify the following defines if you have to target a platform prior to the ones specified below.
//#ifndef WINVER				// Allow use of features specific to Win 2K or later
//#define WINVER 0x0502
//#endif
//
//#ifndef _WIN32_WINNT		// Allow use of features specific to Win 2K or later
//#define _WIN32_WINNT 0x0502
//#endif
//
//#ifndef _WIN32_WINDOWS		// Allow use of features specific to Win 98 or later
//#define _WIN32_WINDOWS 0x0410
//#endif
//
//#ifndef _WIN32_IE			// Allow use of features specific to IE 5.01 or later
//#define _WIN32_IE 0x0502
//#endif

// #include <windows.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <stdarg.h>
#include <algorithm>
#include <iostream>
#include <fstream>

typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define UCHAR unsigned char
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned long
#define UINT unsigned int
#define LONGLONG long long
#define ULONGLONG unsigned long long

// Stub CString using std::string
class CString {
public:
    std::string s;
    CString() {}
    CString(const char* ptr) : s(ptr ? ptr : "") {}
    CString(const std::string& str) : s(str) {}
    CString(const CString& other) : s(other.s) {}
    
    operator const char*() const { return s.c_str(); }
    operator char*() { return const_cast<char*>(s.c_str()); }
    const char* GetBuffer(int) { return s.c_str(); }
    void ReleaseBuffer() {}

    void Format(const char* fmt, ...) {
        char buf[2048];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
        s = buf;
    }
    
    void AppendFormat(const char* fmt, ...) {
        char buf[2048];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
        s += buf;
    }

    CString& operator+=(const char* str) { s += str; return *this; }
    CString& operator+=(const CString& str) { s += str.s; return *this; }
    CString operator+(const char* str) const { return CString(s + str); }
    CString operator+(const CString& str) const { return CString(s + str.s); }
    friend CString operator+(const char* lhs, const CString& rhs) { return CString(std::string(lhs) + rhs.s); }
    
    bool operator==(const char* str) const { return s == str; }
    bool operator==(const CString& str) const { return s == str.s; }
    bool operator!=(const char* str) const { return s != str; }
    bool operator!=(const CString& str) const { return s != str.s; }
    bool operator<(const CString& str) const { return s < str.s; }

    int GetLength() const { return (int)s.length(); }
    bool IsEmpty() const { return s.empty(); }
    void Empty() { s.clear(); }
    
    int CompareNoCase(const char* str) const {
        std::string s1 = s;
        std::string s2 = str;
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        return s1.compare(s2);
    }

    CString Left(int nCount) const { return CString(s.substr(0, nCount)); }
    CString Right(int nCount) const { return CString(s.length() > nCount ? s.substr(s.length() - nCount) : s); }
    CString Mid(int nFirst, int nCount = -1) const { 
        if (nCount == -1) return CString(s.substr(nFirst));
        return CString(s.substr(nFirst, nCount));
    }

    void Trim(const char* chars = " \t\r\n") {
        size_t first = s.find_first_not_of(chars);
        if (std::string::npos == first) {
            s.clear();
            return;
        }
        size_t last = s.find_last_not_of(chars);
        s = s.substr(first, (last - first + 1));
    }
    CString Trim() const {
        CString res = *this;
        res.Trim();
        return res;
    }
};

// Stub CArray using std::vector
template<class T, class ARG_T>
class CArray {
    std::vector<T> m_data;
public:
    int GetSize() const { return (int)m_data.size(); }
    int GetCount() const { return (int)m_data.size(); }
    void SetSize(int nNewSize) { m_data.resize(nNewSize); }
    void RemoveAll() { m_data.clear(); }
    void RemoveAt(int nIndex, int nCount = 1) { m_data.erase(m_data.begin() + nIndex, m_data.begin() + nIndex + nCount); }
    int Add(ARG_T newElement) { m_data.push_back(newElement); return (int)m_data.size() - 1; }
    T& operator[](int nIndex) { return m_data[nIndex]; }
    const T& operator[](int nIndex) const { return m_data[nIndex]; }
    T& GetAt(int nIndex) { return m_data[nIndex]; }
    void SetAt(int nIndex, ARG_T newElement) { m_data[nIndex] = newElement; }
};

// Stub CList using std::list
template<class T, class ARG_T>
class CList {
    std::list<T> m_data;
public:
    int GetCount() const { return (int)m_data.size(); }
    bool IsEmpty() const { return m_data.empty(); }
    void RemoveAll() { m_data.clear(); }
    void AddTail(ARG_T newElement) { m_data.push_back(newElement); }
    // Positions are tricky with std::list, but ICE seems to use it mostly for storage
};

// Old stubs removed

class CFile {
protected:
    std::fstream m_file;
    std::string m_path;
public:
    enum OpenFlags {
        modeRead = 0x0000,
        modeWrite = 0x0001,
        modeReadWrite = 0x0002,
        modeCreate = 0x1000,
        typeBinary = 0x8000
    };
    enum SeekPosition { begin = 0, current = 1, end = 2 };

    CFile() {}
    virtual bool Open(const char* lpszFileName, UINT nOpenFlags) {
        std::ios_base::openmode mode = std::ios::binary;
        if (nOpenFlags & modeRead) mode |= std::ios::in;
        if (nOpenFlags & modeWrite) mode |= std::ios::out;
        if (nOpenFlags & modeReadWrite) mode |= std::ios::in | std::ios::out;
        if (nOpenFlags & modeCreate) mode |= std::ios::trunc | std::ios::out;
        
        m_file.open(lpszFileName, mode);
        if (m_file.is_open()) {
            m_path = lpszFileName;
            return true;
        }
        return false;
    }
    virtual void Close() { m_file.close(); }
    virtual UINT Read(void* lpBuf, UINT nCount) {
        m_file.read((char*)lpBuf, nCount);
        return (UINT)m_file.gcount();
    }
    virtual void Write(const void* lpBuf, UINT nCount) {
        m_file.write((const char*)lpBuf, nCount);
    }
    virtual ULONGLONG Seek(LONGLONG lOff, SeekPosition nFrom) {
        std::ios::seekdir dir;
        if (nFrom == begin) dir = std::ios::beg;
        else if (nFrom == current) dir = std::ios::cur;
        else dir = std::ios::end;
        if (m_file.is_open()) {
            m_file.seekg(lOff, dir);
            m_file.seekp(lOff, dir);
        }
        return (ULONGLONG)m_file.tellg();
    }
    virtual ULONGLONG GetPosition() const {
        return (ULONGLONG)const_cast<std::fstream&>(m_file).tellg();
    }
    virtual CString GetFileName() const {
        size_t last = m_path.find_last_of("\\/");
        if (last == std::string::npos) return CString(m_path);
        return CString(m_path.substr(last + 1));
    }
    virtual void Flush() { m_file.flush(); }
    virtual ULONGLONG GetLength() {
        if (!m_file.is_open()) return 0;
        auto cur = m_file.tellg();
        m_file.seekg(0, std::ios::end);
        auto size = m_file.tellg();
        m_file.seekg(cur);
        return (ULONGLONG)size;
    }
};

class CStdioFile : public CFile {
public:
    CStdioFile() {}
    virtual bool Open(const char* lpszFileName, UINT nOpenFlags) override {
        // CStdioFile is text mode by default, but ICE might expect binary for some things.
        // Let's stick to binary for now as per CFile shim.
        return CFile::Open(lpszFileName, nOpenFlags);
    }
    void WriteString(const char* lpsz) {
        Write(lpsz, (UINT)strlen(lpsz));
    }
    bool ReadString(CString& rString) {
        std::string line;
        if (std::getline(m_file, line)) {
            rString = line;
            return true;
        }
        return false;
    }
};

#ifndef _MSC_VER
#define strcpy_s(d, n, s) strncpy(d, s, n)
#endif

#define ASSERT(x) 
#define VERIFY(x) (x)
#define AfxMessageBox(msg) MessageBox(NULL, (const char*)(msg), "ICE", MB_OK)

// memory leaks tracking
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <math.h>
#include <string.h>
#include <stdio.h>
// change these to whatever you need
#ifndef assert
#define assert(exp)
#endif
#define ZError(psz) 

// these should be defined if you use DirectX otherwise they'll be defined here
// UCHAR and WORD moved to top

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef D3DCOLORVALUE_DEFINED
typedef struct _D3DCOLORVALUE {
    float r;
    float g;
    float b;
    float a;
} D3DCOLORVALUE;
#define D3DCOLORVALUE_DEFINED
#endif

// Allegiance Source includes
// adjust paths 
// TODO: reference current alleg source files instead of these copies but requires to split igc.h into 3 files
#include "IGCLib/igcstatic.h"

class IMainUI {
public:
    virtual void SelectPCE(LPARAM p) = 0;
    virtual HICON GetJumpIcon() = 0;
};

#ifdef _DEBUG
// simple debug fucntion
void debugf(const char* format, ...);
#else
#define debugf(...)
#endif