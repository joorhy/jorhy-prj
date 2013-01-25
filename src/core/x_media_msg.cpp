#include "x_media_msg.h"

CMediaMessage::CMediaMessage()
{

}

CMediaMessage::~CMediaMessage()
{

}

std::string CMediaConvert::Convert(CMediaMessage &mediaMessage)
{
	return mediaMessage.GetResid();
}
