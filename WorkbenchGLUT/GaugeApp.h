#ifndef H_GaugeApp
#define H_GaugeApp


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

#endif // H_GaugeApp
