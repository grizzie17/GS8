#ifndef _GAUGE_APP_H_
#define _GAUGE_APP_H_


enum videoCommands
{
	CMD_VID1 = 0,
	CMD_VID2,
	CMD_VID3,
	CMD_VID4,
	CMD_STILL1,
	CMD_STILL2,
	CMD_PLAY,
	CMD_PAUSE,
	CMD_CAPTURE_YUYV,
	CMD_CAPTURE_RGB,
	CMD_MAX_VALUE = CMD_CAPTURE_RGB,
	CMD_COUNT
};

#endif // _GAUGE_APP_H_



