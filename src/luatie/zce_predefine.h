/*!
* @copyright  2004-2013  Apache License, Version 2.0 FULLSAIL
* @filename   zce_predefine.h
* @author     Sailzeng <sailerzeng@gmail.com>
* @version
* @date       2003-5-14
* @brief      ����Ԥ������Ϣ�������������е��ⲿͷ�ļ���ȫ��ʹ�õĺ꣬
*             ����ƽ̨�����Ե�һЩС��������ֵ��typedef��
*
*
*  @details   ��yunfei�Ľ�����ٸĽ�һ�£�����ÿ���˿������˼·���ǲ�һ���ġ�
*             Ҳ��ȡ��ѵ��дע�ͣ���ô�Ҳ����ΪɶҪ����
*             ������ϸ��һ��ÿ�εķָ��ߺ�˵��������Ϊ�ҵĻ����Ǻ������ģ���Ҫ
*             һ������Ϊ����궨����ң�
*             ���λ����֮ǰ�����㱼��Ұ��ʽ����˼ά����ϸ�Ķ�һ��ע��ͷ��
*             ���ֳɼ��������֣�����ϵͳ���壬ͷ�ļ���������ֵ���壬һЩ���ú꣬
*
*             ͷ�ļ������������
*             1.WINDOWS���в��ֵģ���Ҫ��WINDOWS���ݶ����࣬���׳�ͻ������
*               Windows�����ļ��Ķ���˳��Ҳ���н�����
*             2.LINUX���в��ֵģ�
*             3.Cͷ�ļ�
*             4.C++���в��ֵģ�
*             5.�����ĵ�3���Ŀ��,����ز�Ҫ���ң����󲿷ֶ��ǿ��Դ򿪹رյģ�
*
*             ��ֵ����typedef���ִ��룬�Լ���ص�ͷ�ļ���Ϣ,
*             ��Ķ����Ժ�Ϊ���ģ������ղ���ϵͳ�ֿ������������ʹ�࣬��Ҫ��ͼ
*             ���࣬���ı�˳�򣬷�������������⣬
*
*             ��¼һ�㴿��YY���Ķ�����
*             һ���õ�������ǰ���͵�һ�λ�����¼������
*             ���ߣ�����Ҳ������Ҳ���ʲ��ģ����Σ����󣬲�������������������ȥ��
*             �����࣬��Ҳ�����Ƿ���Ҳ������Ҳ������������Ҳ��������������
*             �һظ���
*             ���������ƽ���� ȥ�������޷��ı�ġ�
*             ������������ȥ�ı����ܸı�ģ�
*             �����ǻۣ��ֱ������ߵ�����
*/

#ifndef ZCE_LIB_PREDEFINE_H_
#define ZCE_LIB_PREDEFINE_H_

//==================================================================================================
//����ĳЩ�򻯵Ĵ���Ԥ����
#ifndef ZCE_SIMPLE_LUBTIE
#define ZCE_SIMPLE_LUBTIE  1
#endif

//==================================================================================================
//���ݲ���ϵͳ����������������ͬ�Ķ��壬��Ϊ��Щ�����Ӱ��ȫ�֣��������ʼ�Ĳ���
//�ҵĿ�ֻ������Ӧ����������Windows(MSVC)��Linux(GCC)��

//WINDOWSƽ̨(MSVC)
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)

#define ZCE_OS_WINDOWS 1

#if (defined(WIN64) || defined(_WIN64))
#define ZCE_WIN64 1
#endif //

#if (defined(WIN32) || defined(_WIN32)) && !(defined(WIN64) || defined(_WIN64))
#define ZCE_WIN32 1
#endif

#endif //#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)

// LINUXƽ̨(GCC)��ֻ����֧��GCC��������˼
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

//�����ɶ�����ǻ���ɶ���ǣ��Ҳ����ˡ�
#if (!defined (ZCE_OS_WINDOWS) && !defined (ZCE_OS_LINUX)) \
    || (defined (ZCE_OS_WINDOWS) && defined (ZCE_OS_LINUX))
#error "[Error]ZCE_OS_WINDOWS and ZCE_OS_LINUX all defined or all undefined.  error."
#endif


//==================================================================================================
//����C++11������ʹ�����⣬C++11�ĺܶ���Ч��˵����ˣ��������İ���������һЩ�ż��ġ�
//��������װC++98���ƹ��ٶ���Ϊ�����ǵ�2015����Կ�ʼʹ��C++11���ԣ�2018������ƹ㣬
//����һ�α�����ĳ��̸о����Ƚ�Ŭ������2013�꣬VC++��GCC �Ѿ��󲿷�������񣬵�Ҫ����
//�еĴ�������ʹ��C++11���ף�����֮�ͱȽϵ����ˡ�
//�������Ȥ��������ƪ�ĵ�
//http://gcc.gnu.org/projects/cxx0x.html
//http://msdn.microsoft.com/en-us/library/hh567368.aspx
//����оټ���
//auto-typed variables                               GCC 4.4 VC++��2010��ʼ��֧��
//Non-static data member initializers                GCC 4.7 VC++2013
//Variadic templates                                 GCC 4.3 VC++2013
//Default template arguments for function templates  GCC 4.3 VC++2013
//����׿�����ķ��ӵ���Ч������Ϊ��VC++����2010�汾��ʼ֧�֣���2013�汾֧����Ч�Ƚ�������
//GCC ��4.3�汾��ʼ��.��4.8�汾֧�ֱȽ����ϣ�GCC4.8��֧�����������̶ȶ�Զ����VC++2013
#if (defined (ZCE_OS_WINDOWS) && defined (_MSC_VER) &&  (_MSC_VER >= 1800)) \
    || (defined (ZCE_OS_LINUX) && defined (_GCC_VER) &&  (_GCC_VER >= 40800))
#define ZCE_SUPPORT_CPP11 1
#else
#define ZCE_SUPPORT_CPP11 0
#endif

//�����ˣ��Ҳ��뵹�˻�ȥ֧�ַ�C11�ı������ˣ���Ŭ��ӵ��C11�������Ҫ����͵�VS������������Ҫ�޸�
//һЩauto����Ĭ�ϷǾ�̬��Ա��ʼ����
#if ZCE_SUPPORT_CPP11 == 0
#error "[Error]Only support C11 compiler, include Visual Studio 2013 and "\
"upper version, or GCC 4.8 and upper version."
#endif

//==================================================================================================
//LINUX GCC�µĸ澯���ι��ܣ��������GCC 4.2�Ժ���У�����push,pop�Ĺ��ܣ�������GCC��4.6�Ժ���У�
//���������θ澯�Ķ���Ҫ�ȴ�GCC4.6�Ժ���С�������ˡ�
//#pragma GCC diagnostic push
//#pragma GCC diagnostic pop

//==================================================================================================


//WINDOWS������ͷ�ļ����֣�

#if defined(ZCE_OS_WINDOWS)

// ��WINDOWS�º�POSIX��׼���ݵĺ꣬VS2003���°汾��Σ���û�в��ԣ�2003�Ժ�Windows���ںܶ������ʹ��"_"ǰ׺��
#define _CRT_NONSTDC_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_WARNINGS  1

// ���ڸ���VC++���Ҳ�ǿ��ʹ��_s���͵�API��_CRT_SECURE_NO_DEPRECATE��_CRT_SECURE_NO_WARNINGS���ϰ汾
#define _CRT_SECURE_NO_WARNINGS   1
#define _CRT_SECURE_NO_DEPRECATE  1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

//==================================================================================================

//ΪʲôWindowsͷ�ļ��������ǰ�棬��Ϊ�����д����Ķ��壬����������������������������γɳ�ͻ��

//֧��WINSERVER2008,VISTA �����������1�������֧�����������0
#define ZCE_SUPPORT_WINSVR2008 1

//Windows ��Vista��WinServer2008�Ժ�֧���˺ܶ��µ�API,�����Ҫ֧�֣���Ҫ��֧�ֿ���
#ifndef ZCE_SUPPORT_WINSVR2008
#if (defined _WIN32_WINNT) && (_WIN32_WINNT >=  0x0600) && defined (_MSC_VER) && (_MSC_VER >= 1400)
#define ZCE_SUPPORT_WINSVR2008 1
#else
#define ZCE_SUPPORT_WINSVR2008 0
#endif
#endif

//�ܶ�ͷ�ļ��Լ���ֵ���屾�����Էŵ�����OS�������ļ�����ȥ�ģ����Ǹо��Ƚ���Ҫ�����Ƿŵ�����ط���
// pretend it's at least Windows XP or Win2003������������������ʱ�����һЩAPI�޷�ʹ�õ�����
#if !defined (_WIN32_WINNT)
#if (defined ZCE_SUPPORT_WINSVR2008) && (ZCE_SUPPORT_WINSVR2008 == 1)
# define _WIN32_WINNT 0x0600
#else
# define _WIN32_WINNT 0x0501
#endif
#endif

// ���¶���FD_SETSIZE����Ҫ��winsock2.hǰ�棬Ҳ��������ע��
#ifndef FD_SETSIZE
#define FD_SETSIZE   1024
#endif

//��Щ�ļ�ǰ׺�Ǵ�д�ģ��������ֵֹģ���Windows���������Ǵ�д�ġ�

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
//LINUX �����еĲ���ͷ�ļ�
#if defined(ZCE_OS_LINUX)

// Ϊ��ʹ��
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

// C ͷ�ļ�
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

// c++ͷ�ļ�
#include <string>

#if defined ZCE_OS_WINDOWS
#pragma warning ( pop )
#endif

//==================================================================================================

//��׼������ֵ���岿�֣�����VS2010ǰ�Ŀ�û�а���C99�ı�׼ִ�У�����������������û�С�
//���еĴ�����,(�������ڼ���API)����׼����long��longlong���ֶ��壬��׼�����־͵�СJJ . ע��������

//�������Ͷ���,�Ƽ�ʹ�ã��ر���64λ��uint64_t,

//LINUX���Ѿ�����صĶ����ˣ�����
#if defined(ZCE_OS_LINUX)
#include <stdint.h>
#include <inttypes.h>
#endif //#if defined(ZCE_OS_LINUX)

//WINDOWS�£����ֲ�ͬ�����ֲ�һ�£���ֻ���Լ���
#if defined(ZCE_OS_WINDOWS)

//��VS2010Ϊֹ��ssize_t��û�б�֧��
#if defined (ZCE_WIN64)
typedef SSIZE_T ssize_t;
#else
typedef int ssize_t;
#endif

//VC++ 2010���Լ����������׼��
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
//����������ⲿ�⣬Ŀǰ����,rapidxml,MYSQL,SQLite,Lua,

//�Ƿ�ʹ��LUA
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
//�ֽ����Сͷ�ʹ�ͷ������
#define ZCE_LITTLE_ENDIAN  0x1234
#define ZCE_BIG_ENDIAN     0x4321

//Ŀǰ���ִ����ǿ�����Сͷ���ʹ�ͷ�������⣬��֪������֮�����״����Ƿ񻹻�Ϊ��ͷ������һ�Σ�
//��Ҫ��hash�ͼ��ܲ��ֵĴ��룬�ǿ��ǹ��ֽ������������ġ�
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
//��ʵ���˴�ͷ����Сͷ�����⣬���������ɱ������渴�ӡ�
#define ZCE_BYTES_ORDER    ZCE_LITTLE_ENDIAN
#endif
#endif  //#ifndef ZCE_BYTES_ORDER


//==================================================================================================
//���ֺ궨�壬���붨�壬һЩ�Ƚϳ��õĺ꣬�������ʡһЩ����

//�ⲿͷ�ļ�����������ǰ��ѽ������Ԥ����ͷ�ļ��Ͳ���������
//��������ڶ�����߱�����������Ĵ���Ͳ���Ԥ�����ˣ���Ҫ���ڼӿ������룬��LINUXĿǰ����֧��

#if defined ZCE_OS_WINDOWS
#pragma hdrstop
#endif //#if defined ZCE_OS_WINDOWS

//���ǳ�ACE_UNUSED_ARG��ѽ���ҳ���ѽ��windows��Ҳ��Ҳ���Կ��Ƕ����__noopѽ��
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

//BOOL����
#ifndef FALSE
#  define FALSE               0
#endif
#ifndef TRUE
#  define TRUE                1
#endif


//__FUNCTION__������滻���������ܰ������������ϸ�ĺ���������Ϣ
//Windows ���������__FUNCSIG__�����ŵ��ǻ��в�����Ϣ����ȱ��Ҳ���в�����Ϣ��һЩ����ģ�����Ϣ�ܳ��ܳ�������Ӱ����ĸо�
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

//BITλ��һЩ���������

//���û���������ֵĳ��λ���ϵ�bitλ
//_value û����()�����������ɵģ���ú����룬�Ǻ�
#if !defined(ZCE_SET_BITS)
#  define ZCE_SET_BITS(set_value, bits) (set_value |= (bits))
#endif
#if !defined(ZCE_CLR_BITS)
#  define ZCE_CLR_BITS(clr_value, bits) (clr_value &= ~(bits))
#endif

//���ĳ��bitλ�Ƿ�������
#if !defined(ZCE_BIT_IS_SET)
#  define ZCE_BIT_IS_SET(compare_value, bits) (((compare_value) & (bits)) != 0)
#endif
#if !defined(ZCE_BIT_ISNOT_SET)
#  define ZCE_BIT_ISNOT_SET(compare_value, bits) (((compare_value) & (bits)) == 0)
#endif

///�����������,ע�⴫�ݵ��ͱ��
#ifndef ZCE_ARRAY_SIZE
#define ZCE_ARRAY_SIZE(ary) (sizeof(ary)/sizeof((ary)[0]))
#endif


//·������󳤶ȣ�
//�ռ�һ��С֪ʶ��ע��һ����ʵMAX_PATHδ���������ã�MSһ��Ķ�����260�����ǣ���ʵ����Գ���,
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

// һЩC�����������������ּ��ݣ������������
#if defined ZCE_OS_WINDOWS

#if _MSC_VER <= 1300
#define snprintf     _snprintf
#define vsnprintf    _vsnprintf
#else
//��VS2005�Ժ�ʹ�ð�ȫAPI,��֤WINDOWS�¸��ӽӽ���LINUX����֤ĩβ�����'\0'
#define snprintf(buffer,buf_count,fmt,...) _snprintf_s((buffer),(buf_count),((buf_count)-1),(fmt),__VA_ARGS__)
#define vsnprintf(buffer,buf_count,fmt,argptr_list)  _vsnprintf_s((buffer),((buf_count)),(buf_count-1),(fmt),(argptr_list))
#endif

#define strtoull _strtoui64
#define strcasecmp   _stricmp
#define strncasecmp  _strnicmp

#endif

//==================================================================================================
//���ʹ����LUA���Զ�����LUA�Ŀ⣬
#if defined ZCE_USE_LUA && ZCE_USE_LUA == 1
#pragma comment(lib, "lualib.lib" )
#endif

//==================================================================================================

//�򵥵���־��������������滻���������е���־����,��������ɵ��滻Ϊ�����־���롣

///RS����д�����ڼ���Richard steven
///��־�������,��־��¼ʱʹ�õ��Ǽ���,
enum ZCE_LOG_PRIORITY
{
    ///������Ϣ,Ĭ��Mask�������,Ĭ��ȫ�����
    RS_TRACE = 1,
    ///������Ϣ
    RS_DEBUG = 2,
    ///��ͨ��Ϣ
    RS_INFO = 3,
    ///������Ϣ
    RS_ERROR = 4,
    ///�澯���͵Ĵ���
    RS_ALERT = 5,
    ///��������
    RS_FATAL = 6,
};



class ZCE_Simple_Log
{
protected:
    ///�����־��Ϣ��Maskֵ,С�������Ϣ����Ϣ���������
    static ZCE_LOG_PRIORITY      permit_outlevel_;

public:
    ///ΪC������׼���ķ�װ���Ҽǲ�Ҫ����,���һ��(��)��־��¼.
    static void write_logmsg(ZCE_LOG_PRIORITY outlevel, const char *str_format, ...)
    {
        va_list args;
        va_start(args, str_format);
        vwrite_logmsg(outlevel, str_format, args);
        va_end(args);
    }

    ///������־��������Level
    static ZCE_LOG_PRIORITY set_log_priority(ZCE_LOG_PRIORITY outlevel)
    {
        ZCE_LOG_PRIORITY oldlevel = permit_outlevel_;
        permit_outlevel_ = outlevel;
        return oldlevel;
    }
protected:

    ///ʵ��д����־�ĺ���
    static void vwrite_logmsg(ZCE_LOG_PRIORITY outlevel, const char *str_format, va_list args)
    {
        if (outlevel >= permit_outlevel_)
        {
            vprintf(str_format, args);
        }
    }
};



//���MASK����,С������������־��Ϣ�������
#ifndef ZLOG_SET_OUTLEVEL
#define ZLOG_SET_OUTLEVEL ZCE_Simple_Log::set_log_priority
#endif

//ʹ�õ��Լ��������־
#ifndef ZCE_LOG
#define ZCE_LOG           ZCE_Simple_Log::write_logmsg
#endif

#ifndef ZCE_ASSERT    
#define ZCE_ASSERT        assert
#endif

#endif //ZCE_LIB_PREDEFINE_H_
