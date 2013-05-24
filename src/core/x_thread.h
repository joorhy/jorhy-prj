#ifndef __X_THREAD_H_
#define __X_THREAD_H_
#include "j_common.h"
#include "j_obj.h"

typedef struct
{
	j_thread_entry_t entry;
	void *data;
	int stack_size;
	int priority;
}j_thread_parm;

class JO_API CJoThread : public J_Obj
{
public:
	CJoThread();
	~CJoThread();

	j_result_t Create(j_thread_parm &parm);
	j_result_t Suspend();
	j_result_t Resume();
	void Release();			//Ç¿ÐÐÍË³ö

private:
	j_thread_parm m_parm;
	j_thread_t m_hThread;
};

#endif //~__X_THREAD_H_