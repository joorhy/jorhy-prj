#ifndef __X_PING_H_
#define __X_PING_H_
#include "j_common.h"

#define PACKET_SIZE 4096

class CXPing
{
    public:
        CXPing();
        CXPing(const char *pAddr);
        ~CXPing();

    public:
        int SetAddr(const char *pAddr);
        int SendPacket();
        int RecvPacket();

    private:
        int Init();
        int Pack(int nPackNo, int nDataLen);
        int UnPack(int nLen);

    private:
        int m_socket;
        struct sockaddr_in m_destAddr;
        std::string m_addr;
        pid_t m_pid;
        char m_sendPacket[PACKET_SIZE];
        char m_recvPacket[PACKET_SIZE];
};
#endif // __X_PING_H_
