#ifndef __FLV_MUX_H_
#define __FLV_MUX_H_
#include "j_includes.h"
#include "x_time.h"
#include "x_module_manager_def.h"

typedef struct _avcConfiguretion
{
	j_int8_t version;									//版本号
	j_int8_t profile_id;								//sps[1]
	j_int8_t profile_cmp;							//sps[2]
	j_int8_t level_id;								//sps[3]
	j_int8_t reserved:6;							//111111
	j_int8_t length_size_minus_one:2;		//NALUnitLength-1,一般为3
	j_int8_t reserved2:3;							//111
	j_int8_t sps_num:5;							//sps个数,一般为1
	j_int16_t sps_size;
	j_int8_t pps_num;								//pps个数,一般为1
	j_int16_t pps_size;

} AVCConfiguretion;

class CFlvMux : public J_MuxFilter
{
public:
	CFlvMux();
	~CFlvMux();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CFlvMux();
		return J_OK;
	}

public:
	virtual j_result_t Init();
	virtual void Deinit();
	virtual j_result_t Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata = 0);

private:
	j_int32_t MakeFlvHead(int nPrevTagLen, int nTagType, int nDataLen, int timeStamp, int nStreamId, char *pBuffer);
	j_int32_t MakeAVCConfig(char *sps, int sps_len, char *pps, int pps_len, char *pBuffer);
	j_int32_t MakeFlvVideoData(char *pData, int nDataLen, char *pBuffer, bool bIFrame = true);
	j_int32_t MakeAmfHead(int nTagType, int nDataLen, int timeStamp, int nStreamId, char *pBuffer);
	j_int32_t MakeAmfVideoData(char *pData, int nDataLen, char *pBuffer, bool bIFrame = true, int nChunkSize = 4096);
	j_int32_t MakeMetaData(double nDuration, double nWidth, double nHeigth, double nFrameRate, double nFileSeize, char *pBuffer);

private:
	j_int32_t m_nPrevTagLen;
	j_int32_t m_nTimeStamp;
	j_char_t *m_pBuffer;
};
#endif //~__FLV_MUX_H_