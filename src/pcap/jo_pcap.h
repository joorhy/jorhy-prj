#ifndef __JO_PCAP_H_
#define __JO_PCAP_H_
#include "x_ether.h"
#include "j_module.h"

class CPcap
{
	public:
		CPcap();
		~CPcap();
		
	public:
		int InitialPcap(const char *pFilterExp = "ether proto 0x88B8");
		int DestroyPcap();
		
	private:
		static void *CAP_Thread(void *param)
        {
            CPcap *pThis = (CPcap *)param;
            if (pThis)
                pThis->CAP_CaptureData();

            return (void *)0;
        }
		void CAP_CaptureData();
		
	private:
		char *m_dev;
        char m_errBuff[PCAP_ERRBUF_SIZE];
		bpf_u_int32 m_mask;
        bpf_u_int32 m_net;
        pcap_t *m_handle;
		struct bpf_program m_bf;
		pthread_t m_thread;
		J_EventParser *pEventParser;
};

#endif //__JO_PCAP_H_
