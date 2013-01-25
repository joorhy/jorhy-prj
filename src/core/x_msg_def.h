#ifndef __X_MSG_DEF_H_
#define __X_MSG_DEF_H_

///定义消息类型
#define MAKE_MESSAGE(type, sub)			(unsigned int)(type | sub)

///媒体播放消息
#define MSG_MEDIA								10000
#define MSG_MEDIA_BROKEN					MAKE_MESSAGE(MSG_MEDIA, 0x01)

///媒体控制消息
#define MSG_MEDIA_CONTROL					20000
#define MSG_RECORD_CONTROL					MAKE_MESSAGE(MSG_MEDIA_CONTROL, 0x01)
#define MSG_PTZ_CONTROL						MAKE_MESSAGE(MSG_MEDIA_CONTROL, 0x02)

///客户端消息

#endif //~__X_MSG_DEF_H_
