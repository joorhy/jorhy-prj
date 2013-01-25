#ifndef __X_XML_STREAM_H_
#define __X_XML_STREAM_H_

#include <wx/stream.h>

class CXMLStream : public wxInputStream
{
    public:
        CXMLStream();
        ~CXMLStream();

    public:
        size_t OnSysRead(void* buffer, size_t bufsize);

};

#endif // __X_XML_STREAM_H_
