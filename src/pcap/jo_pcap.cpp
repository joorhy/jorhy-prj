#include "x_errtype.h"
#include "jo_pcap.h"
#include "x_log.h"
#include "x_goose.h"
#include "j_module.h"

CPcap::CPcap()
{
	m_dev = NULL;
    memset(m_errBuff, 0, sizeof(m_errBuff));
	m_mask = 0;
    m_net = 0;
    m_handle = NULL;
	m_thread = 0;
	
	pEventParser = new CXGooseCap;
}

CPcap::~CPcap()
{
	if (pEventParser)
		delete pEventParser;
}

int CPcap::InitialPcap(const char *pFilterExp)
{
    m_dev = pcap_lookupdev(m_errBuff);
    if (m_dev == NULL)
    {
        J_OS::LOGINFO("CPcap::InitialPcap Could not find default device:%s\n", m_errBuff);
        return J_DEV_ERROR;
    }
    J_OS::LOGINFO("CPcap::InitialPcap device:%s\n", m_dev);

    if (pcap_lookupnet(m_dev, &m_net, &m_mask, m_errBuff) == -1)
    {
        printf("CPcap::InitialPcap Counld not get netmask for device %s;%s\n", m_dev ,m_errBuff);
        m_net = 0;
        m_mask = 0;
    }

    m_handle = pcap_open_live(m_dev, PCAP_SNAPLEN, 1, 1000, m_errBuff);
    if (m_handle == NULL)
    {
        J_OS::LOGINFO("CPcap::InitialPcap Could not open device %s;%s", m_dev, m_errBuff);
        return J_DEV_ERROR;
    }

    if (pcap_compile(m_handle, &m_bf, pFilterExp, 0, m_net) == -1)
    {
        J_OS::LOGINFO("CPcap::InitialPcap Counld not parse filter %s;%s\n", pFilterExp, pcap_geterr(m_handle));
        return J_DEV_ERROR;
    }

    if (pcap_setfilter(m_handle, &m_bf) == -1)
    {
        J_OS::LOGINFO("CPcap::InitialPcap Counld not install filter %s;%s\n", pFilterExp, pcap_geterr(m_handle));
        return J_DEV_ERROR;
    }
    pcap_freecode(&m_bf);

    if (pthread_create(&m_thread, NULL, CPcap::CAP_Thread, this) != 0)
    {
        J_OS::LOGINFO("CPcap::InitialPcap Counld not create thread\n");
        return J_DEV_ERROR;
    }
    pthread_detach(m_thread);

    return J_OK;
}

int CPcap::DestroyPcap()
{
    if (pthread_cancel(m_thread) != 0)
    {
        J_OS::LOGINFO("CPcap::DestroyPcap Counld not cancel thread\n");
        return J_DEV_ERROR;
    }

    if (m_handle)
    {
        pcap_close(m_handle);
        m_handle = NULL;
    }

    return J_OK;
}

void CPcap::CAP_CaptureData()
{
    struct pcap_pkthdr *packet_header = NULL;
    const u_char *packet_data = NULL;
    int ret_val = 0;

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    while ((ret_val = pcap_next_ex(m_handle, &packet_header, &packet_data)) >= 0)
    {
        if (ret_val == 0)
        {
            usleep(10000);
            continue;
        }

		pEventParser->AnalyzePacket(packet_data);
        //GSE_AnalyzePacket(*packet_header, packet_data);
    }
}