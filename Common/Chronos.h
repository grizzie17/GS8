#ifndef Chronos_H_
#define Chronos_H_

#include "UDeclCommon.h"
#include "UPlatform.h"
#include <time.h>

//#define USE_CHRONOS  1

#ifndef USE_CHRONOS

#    define CHRONOS( nID )  //(0)

#else

#    if defined( OS_LINUX )
#        define CHRONOS( nID ) Chronos oChronosTimer( nID, __func__ )
#    else
#        define CHRONOS( nID )                                     \
            static const char chronos_function__[] = __FUNCTION__; \
            Chronos           oChronosTimer( nID, chronos_function__ )
#    endif

#    define CHRONOS_STR( x ) #    x

#endif

namespace Yogi { namespace Common {


enum ChronosID
{
    TE_ALL = 0,
    TE_BEGIN,
    TE_END,
    TE_BEGINCONTEXT,
    TE_ENDCONTEXT,
    //TE_BUFFERCREATE,
    //TE_BUFFERDESTROY,
    //TE_PENSELECT,
    //TE_BRUSHSELECT,
    //TE_FONTSELECT,
    TE_LINE,
    TE_ARC,
    TE_CIRCLE,
    TE_PIE,
    TE_ENDPOLYLINE,
    TE_ENDPOLYGON,
    TE_RECTANGLE,
    TE_TEXTSTRING,
    //TE_IMAGE,
    TE_IMAGELOADFILE,
    TE_IMAGEPRELOADED,
    TE_MAX
};


class COMMON_CLASS Chronos
{
public:
    Chronos();
    Chronos( int nID );
    Chronos( int nID, const char* sName );
    ~Chronos();

public:
    time_t
    StartTimer();
    time_t
    StopTimer();
    static void
    PrintLog();

protected:
    typedef struct ChronosLogEntry
    {
        long        nCount;
        time_t      nElapsedTime;
        const char* sName;
    } ChronosLogEntry;

    static time_t
    Frequency();

    time_t m_nStart;
    int    m_nID;

    static ChronosLogEntry g_aLog[];
};


}}  // namespace Yogi::Common


#endif  // Chronos_H_
