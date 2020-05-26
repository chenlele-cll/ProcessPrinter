#include <iostream>
#include <forward_list>
#include <string>
#include <map>  
#include <windows.h>  
#include <TlHelp32.h> 
#include <time.h>
#include <psapi.h>
#include <algorithm>
#include <iomanip>
#include "DoubleLinkList.h"
#include "SingleLinkList.h"

using datastructure::linklist::DoubleLinkList;
using datastructure::linklist::SingleLinkList;
using datastructure::linklist::DoubleNode;
using datastructure::linklist::SingleNode;

/*————————————————
版权声明：本文为CSDN博主「陈乐乐happy」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/weixin_39139505/article/details/90295704
*/

struct ProcessInfo {
public:
	DWORD process_id;	//进程 id
	std::string process_name;  //程序名
	int memory_usage;	//内存使用情况
	FILETIME creation_time;	//创建时间
	FILETIME exit_time;	//结束时间

	std::string duration;	//持续时间
	std::string end_time;	//结束时间
};

DoubleLinkList<ProcessInfo> GetProcesses() {
	DoubleLinkList<ProcessInfo> data;

	//PROCESSENTRY32结构体，保存进程具体信息
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	//获得系统进程快照的句柄
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		std::cout << "CreateToolhelp32Snapshot Error!" << std::endl;;
		return data;
	}

	//首先获得第一个进程
	BOOL bResult = Process32First(hProcessSnap, &pe32);

	//循环获取所有进程
	while (bResult) {
		ProcessInfo process;
		process.process_id = pe32.th32ProcessID;
		process.process_name = pe32.szExeFile;
		data.HeadInsert(process);

		bResult = Process32Next(hProcessSnap, &pe32);
	}

	CloseHandle(hProcessSnap);
	return data;
}


void GetMemoryInfo(DWORD processID, DoubleNode<ProcessInfo> *process)
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	// Print information about the memory usage of the process.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;

	FILETIME creation_time, exit_time,kernel_time,user_time;
	GetProcessTimes(hProcess, &creation_time, &exit_time,&kernel_time,&user_time);
	process->val_.creation_time = creation_time;
	process->val_.exit_time = exit_time;

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
		process->val_.memory_usage = pmc.WorkingSetSize/1024;
	}

	CloseHandle(hProcess);
}

void PrintProcessInfo(DoubleLinkList<ProcessInfo>& process_list) {
	std::cout << " 进程 ID" << "     工作设置内存(/KB)" << "      进程名       " << std::endl;
	auto process = process_list.GetHead()->next_;
	int len = process_list.GetLength();
	while(len) {
		std::cout << "  " << std::setw(15) << std::setiosflags(std::ios::left) << process->val_.process_id;
		std::cout << std::setw(10) << process->val_.memory_usage << "\t"  << process->val_.process_name <<  "\t" << process->val_.creation_time.dwHighDateTime<<std::endl;
		len--;
		process = process->next_;
	}
}

int main() {
	//TODO 写对应的复制构造函数
	auto process_list = GetProcesses();
	std::cout << process_list.GetLength() << std::endl;
	int len = process_list.GetLength();
	auto process = process_list.GetHead()->next_->next_;
	for (int i = 0; i < len; i++) {
		std::cout << process->val_.process_id << std::endl;
		process = process->next_;
	}
	while(len) {
		GetMemoryInfo(process->val_.process_id, process);
		process = process->next_;
		len--;
	}
	while (process_list.Back()->val_.memory_usage < 0){
		process_list.PopBack();
	}
	PrintProcessInfo(process_list);
	system("pause");
	return 0;
}