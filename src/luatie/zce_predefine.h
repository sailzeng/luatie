/*!
* @copyright  2004-2013  Apache License, Version 2.0 FULLSAIL
* @filename   zce_predefine.h
* @author     Sailzeng <sailerzeng@gmail.com>
* @version
* @date       2003-5-14
* @brief      所有预定义信息描述，包括所有的外部头文件，全局使用的宏，
*             个个平台兼容性的一些小东东，数值的typedef，
*
*
*  @details   在yunfei改进后的再改进一下，发现每个人看问题的思路还是不一样的。
*             也吸取教训，写注释，免得大家不理解为啥要这样
*             请大家仔细看一下每段的分割线和说明，我认为我的划分是很清晰的，不要
*             一看就认为代码宏定义混乱，
*             请各位大神动之前放慢你奔腾野马式样的思维，仔细阅读一下注释头文
*             件分成几个个部分，操作系统定义，头文件包含，数值定义，一些常用宏，
*
*             头文件包含情况如下
*             1.WINDOWS特有部分的，主要是WINDOWS兼容东西多，容易冲突，甚至
*               Windows那排文件的定义顺序也是有讲究的
*             2.LINUX特有部分的，
*             3.C头文件
*             4.C++特有部分的，
*             5.依赖的第3方的库的,请务必不要搞乱，（大部分都是可以打开关闭的）
*
*             数值定义typedef部分代码，以及相关的头文件信息,
*             宏的定义以宏为核心，不按照操作系统分开，免得找起来痛苦，不要试图
*             归类，而改变顺序，反而让人难以理解，
*
*             记录一点纯属YY，的东东，
*             一个得道修仙老前辈送的一段话，记录下来：
*             侠者，性情也，意气也。故不文，不饰，不求，不争，合则留，不合则去。
*             故卫青，将也；周亚夫，侠也；徐达，将也；常遇春，侠也。真侠近乎道。
*             我回复：
*             神，请赐予我平静， 去接受我无法改变的。
*             给予我勇气，去改变我能改变的，
*             赐我智慧，分辨这两者的区别。
*/

#ifndef ZCE_LIB_PREDEFINE_H_
#define ZCE_LIB_PREDEFINE_H_

//==================================================================================================
//用于某些简化的代码预定义
#ifndef ZCE_SIMPLE_LUBTIE
#define ZCE_SIMPLE_LUBTIE  1
#endif

//==================================================================================================
//根据操作系统，编译器，给出不同的定义，因为这些定义会影响全局，所以在最开始的部分
//我的库只打算适应两个环境，Windows(MSVC)和Linux(GCC)，

//WINDOWS平台(MSVC)
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)

#define ZCE_OS_WINDOWS 1

#if (defined(WIN64) || defined(_WIN64))
#define ZCE_WIN64 1
#endif //

#if (defined(WIN32) || defined(_WIN32)) && !(defined(WIN64) || defined(_WIN64))
#define ZCE_WIN32 1
#endif

#endif //#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)

// LINUX平台(GCC)我只打算支持GCC，不好意思
#if defined(__linux__) && defined (__GNUC__)
#define ZCE_OS_LINUX 1
#ifndef _GCC_VER
#define _GCC_VER (__GNUC__ * 10000 \
                  + __GNUC_MINOR__ * 100 \
                  + __GNUC_PATCHLEVEL__)
#endif
#if defined(__LP64__)
#define ZCE_LINUX64 1
#else
#define ZCE_LINUX32 1
#endif

#endif

#if  ( defined (ZCE_WIN64) || defined(ZCE_LINUX64)  \
  || defined(__x86_64__)|| defined(__x86_64) || defined(__amd64__)  \
  || defined(__amd64) || defined(__ppc64__) || defined(_WIN64) \
  || defined(__LP64__) || defined(_LP64) || defined(__ia64__) )
#  define ZCE_OS64 1
#else
#  define ZCE_OS32 1
#endif

//如果你啥都不是或者啥都是，我不活了。
#if (!defined (ZCE_OS_WINDOWS) && !defined (ZCE_OS_LINUX)) \
    || (defined (ZCE_OS_WINDOWS) && defined (ZCE_OS_LINUX))
#error "[Error]ZCE_OS_WINDOWS and ZCE_OS_LINUX all defined or all undefined.  error."
#endif


//==================================================================================================
//关于C++11的特性使用问题，C++11的很多特效如此的诱人，但想真心爱他还是有一些门槛的。
//我曾经安装C++98的推广速度认为，我们到2015年可以开始使用C++11特性，2018年才能推广，
//但这一次编译机的厂商感觉都比较努力，到2013年，VC++和GCC 已经大部分完成任务，但要在现
//有的代码里面使用C++11容易，兼容之就比较蛋疼了。
//如果有兴趣看看这两篇文档
//http://gcc.gnu.org/projects/cxx0x.html
//http://msdn.microsoft.com/en-us/library/hh567368.aspx
//随便列举几个
//auto-typed variables                               GCC 4.4 VC++从2010开始逐步支持
//Non-static data member initializers                GCC 4.7 VC++2013
//Variadic templates                                 GCC 4.3 VC++2013
//Default template arguments for function templates  GCC 4.3 VC++2013
//如果抛开上面的繁杂的特效可以认为，VC++，从2010版本开始支持，在2013版本支持特效比较完整，
//GCC 从4.3版本开始到.到4.8版本支持比较晚上，GCC4.8的支持特性数量程度都远好于VC++2013
#if (defined (ZCE_OS_WINDOWS) && defined (_MSC_VER) &&  (_MSC_VER >= 1800)) \
    || (defined (ZCE_OS_LINUX) && defined (_GCC_VER) &&  (_GCC_VER >= 40800))
#define ZCE_SUPPORT_CPP11 1
#else
#define ZCE_SUPPORT_CPP11 0
#endif

//我懒了，我不想倒退回去支持非C11的编译器了，我努力拥抱C11，如果你要向更低的VS编译器靠近，要修改
//一些auto或者默认非静态成员初始化，
#if ZCE_SUPPORT_CPP11 == 0
#error "[Error]Only support C11 compiler, include Visual Studio 2013 and "\
"upper version, or GCC 4.8 and upper version."
#endif

//==================================================================================================
//LINUX GCC下的告警屏蔽功能，其必须在GCC 4.2以后才有，而且push,pop的功能，必须在GCC，4.6以后才有，
//这两个屏蔽告警的东东要等待GCC4.6以后才有。命苦的人。
//#pragma GCC diagnostic push
//#pragma GCC diagnostic pop

//==================================================================================================


//WINDOWS的特有头文件部分，

#if defined(ZCE_OS_WINDOWS)

// 在WINDOWS下和POSIX标准兼容的宏，VS2003以下版本如何，我没有测试，2003以后，Windows对于很多代码宏会使用"_"前缀，
#define _CRT_NONSTDC_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_WARNINGS  1

// 用于告诉VC++，我不强迫使用_s类型的API，_CRT_SECURE_NO_DEPRECATE是_CRT_SECURE_NO_WARNINGS的老版本
#define _CRT_SECURE_NO_WARNINGS   1
#define _CRT_SECURE_NO_DEPRECATE  1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

//==================================================================================================

//为什么Windows头文件必须放在前面，因为里面有大量的定义，如果步不按照这个规矩来，很容易形成冲突，

//支持WINSERVER2008,VISTA 将下面调整成1，如果不支持下面调整成0
#define ZCE_SUPPORT_WINSVR2008 1

//Windows 的Vista和WinServer2008以后，支持了很多新的API,如果需要支持，需要打开支持开关
#ifndef ZCE_SUPPORT_WINSVR2008
#if (defined _WIN32_WINNT) && (_WIN32_WINNT >=  0x0600) && defined (_MSC_VER) && (_MSC_VER >= 1400)
#define ZCE_SUPPORT_WINSVR2008 1
#else
#define ZCE_SUPPORT_WINSVR2008 0
#endif
#endif

//很多头文件以及数值定义本来可以放到各个OS的配置文件里面去的，但是感觉比较重要，还是放到这个地方了
// pretend it's at least Windows XP or Win2003，如果不定义这个，有时候会有一些API无法使用的问题
#if !defined (_WIN32_WINNT)
#if (defined ZCE_SUPPORT_WINSVR2008) && (ZCE_SUPPORT_WINSVR2008 == 1)
# define _WIN32_WINNT 0x0600
#else
# define _WIN32_WINNT 0x0501
#endif
#endif

// 重新定义FD_SETSIZE来，要在winsock2.h前面，也请其他人注意
#ifndef FD_SETSIZE
#define FD_SETSIZE   1024
#endif

//有些文件前缀是大写的，看起来怪怪的，但Windows下他就真是大写的。

#include <winsock2.h>
#include <MSWSock.h>
#include <winerror.h>
#include <windows.h>
#include <winnt.h>
#include <winbase.h>
#include <Psapi.h>
#include <windef.h>
#include <WTypes.h>
#include <process.h>
#include <ws2tcpip.h>
#include <direct.h>
#include <crtdbg.h>
#include <io.h>
#include <share.h>
#include <DbgHelp.h>
#include <intrin.h>

#endif //#ifdef ZCE_OS_WINDOWS

//==================================================================================================
//LINUX 下特有的部分头文件
#if defined(ZCE_OS_LINUX)

// 为了使用
#define _BSD_SOURCE

#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/io.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include <sys/resource.h>
#include <sys/epoll.h>
#include <time.h>
#include <netdb.h>
#include <pthread.h>
#include <iconv.h>
#include <ucontext.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sysinfo.h>
#include <sys/inotify.h>

#if defined(__GNUC__)
#include <execinfo.h>
#endif //#if defined(__GNUC__)

#endif // #ifdef ZCE_OS_LINUX

//==================================================================================================

// C 头文件
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

//==================================================================================================
#if defined ZCE_OS_WINDOWS
#pragma warning ( push )
#pragma warning ( disable : 4702)
#pragma warning ( disable : 4267)
#endif

// c++头文件
#include <string>

#if defined ZCE_OS_WINDOWS
#pragma warning ( pop )
#endif

//==================================================================================================

//标准整数数值定义部分，由于VS2010前的库没有按照C99的标准执行，所以下面这两个库没有。
//所有的代码中,(除非用于兼容API)，不准出现long，longlong这种定义，不准，出现就弹小JJ . 注：弹到死

//整数类型定义,推荐使用，特别是64位的uint64_t,

//LINUX下已经有相关的定义了，万幸
#if defined(ZCE_OS_LINUX)
#include <stdint.h>
#include <inttypes.h>
#endif //#if defined(ZCE_OS_LINUX)

//WINDOWS下，各种不同，各种不一致，你只能自己来
#if defined(ZCE_OS_WINDOWS)

//到VS2010为止，ssize_t还没有被支持
#if defined (ZCE_WIN64)
typedef SSIZE_T ssize_t;
#else
typedef int ssize_t;
#endif

//VC++ 2010，以及遵守这个标准了
#if _MSC_VER >= 1500
#include <stdint.h>
//VC++ 2005
#else

//The stdint declaras
typedef  signed char        int8_t;
typedef  short              int16_t;
typedef  int                int32_t;
typedef  unsigned char      uint8_t;
typedef  unsigned short     int8_tuint16_t;
typedef  unsigned int       uint32_t;

//
#if _MSC_VER >= 1300
typedef unsigned long long  uint64_t;
typedef long long           floatint64_t;
#else
typedef unsigned __int64    uint64_t;
typedef __int64             int64_t;
#endif //#if _MSC_VER >= 1300

#endif //#if _MSC_VER >= 1500

#endif //#if defined(ZCE_OS_WINDOWS)


//==================================================================================================
//我们引入的外部库，目前包括,rapidxml,MYSQL,SQLite,Lua,

//是否使用LUA
#ifndef ZCE_USE_LUA
#define ZCE_USE_LUA 1
#endif


#if defined ZCE_USE_LUA && ZCE_USE_LUA == 1
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#endif

//==================================================================================================
//字节序的小头和大头的问题
#define ZCE_LITTLE_ENDIAN  0x1234
#define ZCE_BIG_ENDIAN     0x4321

//目前部分代码是考虑了小头党和大头党的问题，不知道有生之年这套代码是否还会为大头党服务一次？
//主要是hash和加密部分的代码，是考虑过字节序兼容性问题的。
// Little Endian or Big Endian ?
// Overwrite the #define below if you know your architecture endianess
#if defined (__GLIBC__)
#  include <endian.h>
#endif

#ifndef ZCE_BYTES_ORDER
#if ( (defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)) || defined(__BIG_ENDIAN__) || defined(__BIG_ENDIAN) || defined(_BIG_ENDIAN) ) && !(defined(__LITTLE_ENDIAN__) || defined(__LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN))
#  define ZCE_BYTES_ORDER ZCE_BIG_ENDIAN
#elif defined(__sparc) || defined(__sparc__) \
    || defined(__ppc__) || defined(_POWER) || defined(__powerpc__) || defined(_ARCH_PPC) || defined(__PPC__) || defined(__PPC) || defined(PPC) \
    || defined(__powerpc__) || defined(__powerpc) || defined(powerpc) \
    || defined(__hpux)  || defined(__hppa)  || defined(_MIPSEB) || defined(__s390__)
#  define  ZCE_BYTES_ORDER ZCE_BIG_ENDIAN
#else
// Little Endian assumed. PDP Endian and other very rare endian format are unsupported.
//其实除了大头党和小头党以外，还有其他派别，人类真复杂。
#define ZCE_BYTES_ORDER    ZCE_LITTLE_ENDIAN
#endif
#endif  //#ifndef ZCE_BYTES_ORDER


//==================================================================================================
//各种宏定义，编译定义，一些比较常用的宏，帮助你节省一些代码

//外部头文件，都放在这前面呀，否则预编译头文件就不起作用了
//这个红用于定义告诉编译器，后面的代码就不做预处理了，主要用于加快代码编译，但LINUX目前还不支持

#if defined ZCE_OS_WINDOWS
#pragma hdrstop
#endif //#if defined ZCE_OS_WINDOWS

//我是抄ACE_UNUSED_ARG的呀。我承认呀。windows下也许也可以考虑定义成__noop呀，
#if !defined (ZCE_UNUSED_ARG)
#if defined ZCE_OS_LINUX
#  if defined ( _GCC_VER >= 40200)
#    define ZCE_UNUSED_ARG(a) (void) (a)
#  else
#    define ZCE_UNUSED_ARG(a) do {/* null */} while (&a == 0)
#  endif
#elif defined ZCE_OS_WINDOWS
#    define ZCE_UNUSED_ARG(a)    UNREFERENCED_PARAMETER(a)
#  endif
#endif //#if !defined (ZCE_UNUSED_ARG)

//BOOL变量
#ifndef FALSE
#  define FALSE               0
#endif
#ifndef TRUE
#  define TRUE                1
#endif


//__FUNCTION__定义的替换，尽最大可能帮你输出更加详细的函数名称信息
//Windows 下你可以用__FUNCSIG__，其优点是会有参数信息，但缺点也是有参数信息，一些带有模板的信息很长很长，反而影响你的感觉
#if defined ZCE_OS_WINDOWS
#define __ZCE_FUNC__   __FUNCTION__
#elif defined ZCE_OS_LINUX
#define __ZCE_FUNC__   __PRETTY_FUNCTION__
#else
#define __ZCE_FUNC__   __FUNCTION__
#endif

//
#if defined(ZCE_OS_LINUX) && defined(__GNUC__)
#define ZCE_LIKELY(x)      __builtin_expect (x, 1)
#define ZCE_UNLIKELY(x)    __builtin_expect (x, 0)
#else
#define ZCE_LIKELY(x)      (x)
#define ZCE_UNLIKELY(x)    (x)
#endif

//BIT位的一些操作定义宏

//设置或者清理数值某个位置上的bit位
//_value 没有用()保护是有理由的，请好好想想，呵呵
#if !defined(ZCE_SET_BITS)
#  define ZCE_SET_BITS(set_value, bits) (set_value |= (bits))
#endif
#if !defined(ZCE_CLR_BITS)
#  define ZCE_CLR_BITS(clr_value, bits) (clr_value &= ~(bits))
#endif

//检查某个bit位是否设置了
#if !defined(ZCE_BIT_IS_SET)
#  define ZCE_BIT_IS_SET(compare_value, bits) (((compare_value) & (bits)) != 0)
#endif
#if !defined(ZCE_BIT_ISNOT_SET)
#  define ZCE_BIT_ISNOT_SET(compare_value, bits) (((compare_value) & (bits)) == 0)
#endif

///计算数组个数,注意传递的型别喔
#ifndef ZCE_ARRAY_SIZE
#define ZCE_ARRAY_SIZE(ary) (sizeof(ary)/sizeof((ary)[0]))
#endif


//路径的最大长度，
//普及一下小知识，注意一下其实MAX_PATH未必真正够用，MS一般的定义是260，但是，其实你可以超过,
#ifndef MAX_PATH
#  define MAX_PATH 512
#endif
#if !defined (PATH_MAX)
#  if defined (_MAX_PATH)
#    define PATH_MAX _MAX_PATH
#  elif defined (MAX_PATH)
#    define PATH_MAX MAX_PATH
#  elif defined (_POSIX_PATH_MAX)
#     define PATH_MAX _POSIX_PATH_MAX
#  else /* !_MAX_PATH */
#    define PATH_MAX 512
#  endif /* _MAX_PATH */
#endif /* !PATH_MAX */

// 一些C函数的重命名，保持兼容，避免费力折腾
#if defined ZCE_OS_WINDOWS

#if _MSC_VER <= 1300
#define snprintf     _snprintf
#define vsnprintf    _vsnprintf
#else
//在VS2005以后，使用安全API,保证WINDOWS下更加接近于LINUX，保证末尾会添加'\0'
#define snprintf(buffer,buf_count,fmt,...) _snprintf_s((buffer),(buf_count),((buf_count)-1),(fmt),__VA_ARGS__)
#define vsnprintf(buffer,buf_count,fmt,argptr_list)  _vsnprintf_s((buffer),((buf_count)),(buf_count-1),(fmt),(argptr_list))
#endif

#define strtoull _strtoui64
#define strcasecmp   _stricmp
#define strncasecmp  _strnicmp

#endif

//==================================================================================================
//如果使用了LUA，自动链接LUA的库，
#if defined ZCE_USE_LUA && ZCE_USE_LUA == 1
#pragma comment(lib, "lualib.lib" )
#endif

//==================================================================================================

//简单的日志输出函数，用于替换真正代码中的日志部分,你可以轻松的替换为你的日志代码。

///RS的缩写是用于纪念Richard steven
///日志输出级别,日志记录时使用的是级别,
enum ZCE_LOG_PRIORITY
{
    ///跟踪信息,默认Mask输出级别,默认全部输出
    RS_TRACE = 1,
    ///调试信息
    RS_DEBUG = 2,
    ///普通信息
    RS_INFO = 3,
    ///错误信息
    RS_ERROR = 4,
    ///告警类型的错误
    RS_ALERT = 5,
    ///致命错误
    RS_FATAL = 6,
};



class ZCE_Simple_Log
{
protected:
    ///输出日志信息的Mask值,小于这个信息的信息不予以输出
    static ZCE_LOG_PRIORITY      permit_outlevel_;

public:
    ///为C爱好者准备的封装，且记不要混用,输出一条(行)日志记录.
    static void write_logmsg(ZCE_LOG_PRIORITY outlevel, const char *str_format, ...)
    {
        va_list args;
        va_start(args, str_format);
        vwrite_logmsg(outlevel, str_format, args);
        va_end(args);
    }

    ///设置日志输出级别的Level
    static ZCE_LOG_PRIORITY set_log_priority(ZCE_LOG_PRIORITY outlevel)
    {
        ZCE_LOG_PRIORITY oldlevel = permit_outlevel_;
        permit_outlevel_ = outlevel;
        return oldlevel;
    }
protected:

    ///实际写入日志的函数
    static void vwrite_logmsg(ZCE_LOG_PRIORITY outlevel, const char *str_format, va_list args)
    {
        if (outlevel >= permit_outlevel_)
        {
            vprintf(str_format, args);
        }
    }
};



//输出MASK级别,小于这个级别的日志信息不予输出
#ifndef ZLOG_SET_OUTLEVEL
#define ZLOG_SET_OUTLEVEL ZCE_Simple_Log::set_log_priority
#endif

//使用调试级别输出日志
#ifndef ZCE_LOG
#define ZCE_LOG           ZCE_Simple_Log::write_logmsg
#endif

#ifndef ZCE_ASSERT    
#define ZCE_ASSERT        assert
#endif

#endif //ZCE_LIB_PREDEFINE_H_
