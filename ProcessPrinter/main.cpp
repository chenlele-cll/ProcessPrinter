#pragma warning(disable:4996) 
#include <iostream>
#include <forward_list>
#include <string> 
#include <windows.h>  
#include <TlHelp32.h> 
#include <time.h>
#include <psapi.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>

#include "DoubleLinkList.h"
#include "SingleLinkList.h"
#include "ProcessInfo.h"
#include "EndProcessInfo.h"

using datastructure::linklist::DoubleLinkList;
using datastructure::linklist::SingleLinkList;
using datastructure::linklist::DoubleNode;
using datastructure::linklist::SingleNode;

/*————————————————
版权声明：本文为CSDN博主「陈乐乐happy」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/weixin_39139505/article/details/90295704
*/

//取出 pslist 打印中的无效信息
void GetRidOfInvalidMsg(std::string& pro_list) {
	int index;
	for (int i = 0; i < 3; i++) {
		index = pro_list.find_first_of('\n');
		pro_list = pro_list.substr(index + 1);
	}
}

//压缩空格
std::string CompressBlank(std::string pro_list) {
	std::string c_pro_list;
	bool flag = false;
	for (auto c : pro_list) {
		if (c != ' ') {
			c_pro_list += c;
			flag = false;
		}
		else if (c == ' '&&flag == false) {
			c_pro_list += c;
			flag = true;
		}
		else if (c == ' '&&flag == true) continue;
	}
	return c_pro_list;
}

//通过 pslist 获取全部进程信息
std::string GetProcessMsgList() {
	const std::string& path = R"(F:\msg.txt)";
	std::string command = R"(F:\pslist>)" + path + "&&exit";
	system(command.data());
	std::ifstream msg(path);
	std::stringstream buffer;
	buffer << msg.rdbuf();
	std::string pro_list(buffer.str());
	GetRidOfInvalidMsg(pro_list);
	pro_list = CompressBlank(pro_list);
	return pro_list;
}

//获取一条进程的信息
std::string GetOneProcessMsg(std::string& pro_list) {
	int index = pro_list.find_first_of('\n');
	if (index != -1) {
		std::string process = pro_list.substr(0, index + 1);
		pro_list = pro_list.substr(index + 1);
		return process;
	}
	else {
		std::string tmp = pro_list;
		pro_list = "";
		return tmp;
	}
}

//提取进程的信息存储到结构体
ProcessInfo ExtractInfo(std::string pro) {
	ProcessInfo process;
	int index = pro.find_first_of(' ');
	while ((pro[index+1] <= 'z'&&pro[index+1] >= 'a') || (pro[index+1] <= 'Z'&&pro[index+1] >= 'A')||pro[index+1]==' ')
		index++;
	process.process_name = pro.substr(0, index);
	pro = pro.substr(index + 1);

	index = pro.find_first_of(' ');
	process.process_id = pro.substr(0, index);
	pro = pro.substr(index + 1);

	for (int i = 0; i < 3; i++) {
		index = pro.find_first_of(' ');
		pro = pro.substr(index + 1);
	}

	index = pro.find_first_of(' ');
	process.memory_usage = std::atoi(pro.substr(0, index).c_str());
	pro = pro.substr(index + 1);

	index = pro.find_first_of(' ');
	pro = pro.substr(index + 1);
	pro.pop_back();
	process.elapsed_time = pro;

	return process;
}

//打印当前全部进程详情
void PrintCurProcessInfo(DoubleLinkList<ProcessInfo>& process_list) {
	
	auto process = process_list.GetHead()->prev_;
	int len = process_list.GetLength();
	std::cout << "----------------------当前进程详情----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << std::setiosflags(std::ios::right) << "[pid]" << std::resetiosflags(std::ios::right);
	std::cout << std::setw(14) << std::setiosflags(std::ios::right) << "[持续时间]"<< std::resetiosflags(std::ios::right);
	std::cout << std::setw(15) << std::setiosflags(std::ios::right) << "[工作内存/KB]" << std::resetiosflags(std::ios::right);
	std::cout << "    ";
	std::cout << std::setw(19) << std::setiosflags(std::ios::left) << "[进程名]" << std::resetiosflags(std::ios::left);
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	while (len) {
		std::string memory_usage = std::to_string(process->val_.memory_usage)  + "     ";
		std::cout << std::setw(10) << std::setiosflags(std::ios::right) << process->val_.process_id << std::resetiosflags(std::ios::right);
		std::cout << std::setw(14) << std::setiosflags(std::ios::right)<<process->val_.elapsed_time << std::resetiosflags(std::ios::right);
		std::cout <<std::setw(15) << std::setiosflags(std::ios::right) << memory_usage << std::resetiosflags(std::ios::right);
		std::cout << "    ";
		std::cout << std::setw(19) << std::setiosflags(std::ios::left) << process->val_.process_name << std::resetiosflags(std::ios::left);
		std::cout << std::endl;
		len--;
		process = process->prev_;
	}
	std::cout << "--------------------------------------------------------------" << std::endl;
}

//打印已结束进程详情
void PrintEndProcessInfo(SingleLinkList<EndProcessInfo>& process_list) {
	std::cout << "----------------------已结束进程详情--------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << std::setiosflags(std::ios::right) << "[pid]" << std::resetiosflags(std::ios::right);
	std::cout << std::setw(14) << std::setiosflags(std::ios::right) << "[持续时间]" << std::resetiosflags(std::ios::right);
	std::cout << std::setw(14) << std::setiosflags(std::ios::right) << "[结束时间]" << std::resetiosflags(std::ios::right);
	std::cout << "    ";
	std::cout << std::setw(14) << std::setiosflags(std::ios::left) << "[进程名]" << std::resetiosflags(std::ios::left);
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	auto it = process_list.Front();
	while (it) {
		std::cout << std::setw(10) << std::setiosflags(std::ios::right) << it->val_.process_id << std::resetiosflags(std::ios::right);
		std::cout << std::setw(14) << std::setiosflags(std::ios::right) << it->val_.elapsed_time << std::resetiosflags(std::ios::right);
		std::cout << std::setw(14) << std::setiosflags(std::ios::right) << it->val_.end_time << std::resetiosflags(std::ios::right);
		std::cout << "    ";
		std::cout << std::setw(19) << std::setiosflags(std::ios::left) << it->val_.process_name << std::resetiosflags(std::ios::left);
		it = it->next_;
		std::cout << std::endl;
	}
	std::cout << "--------------------------------------------------------------" << std::endl;

}

std::string GetCurrentSystemTime() {
	struct tm *local;
	time_t nowtime = time(NULL); //获取日历时间

	local = localtime(&nowtime);
	std::string time = asctime(local);
	for (int i = 0; i <= 5; i++) time.pop_back();
	for (int i = 0; i < 3; i++) {
		int index = time.find_first_of(' ');
		time = time.substr(index + 1);
	}
	return time;
}

int main() {
	DoubleLinkList<ProcessInfo> pre_process_list;	//存储上一秒的进程列表  
	DoubleLinkList<ProcessInfo> cur_process_list;	//存储当前的进程列表
	SingleLinkList<EndProcessInfo> end_process_list;	//存储结束进程列表
	std::map<std::string, DoubleNode<ProcessInfo>*> cur_pro_map;	//存储 pid 到进程结点的映射
	int len = 50;	//定义循环次数
	while (len) {

		//获取进程信息到双链表
		std::string process_msg_list = GetProcessMsgList();
		while (!process_msg_list.empty()) {
			cur_process_list.SelectInsert(ExtractInfo(GetOneProcessMsg(process_msg_list)));
		}

		//添加映射关系
		auto it = cur_process_list.Front();
		while (it != cur_process_list.GetHead()) {
			cur_pro_map.insert(std::pair<std::string, DoubleNode<ProcessInfo>*>(it->val_.process_id, it));
			it = it->next_;
		}

		/*
		if (end_process_list.GetLength() != 0) {
			auto end_it = end_process_list.Front();
			while (end_it) {
				if (cur_pro_map.count(end_it->val_.process_id)) {
					end_it = end_process_list.Delete(end_it);
				}
				end_it = end_it->next_;
			}
		}*/

		//比较链表元素判断是否存在已结束进程
		std::string current_time = GetCurrentSystemTime();
		if (pre_process_list.GetLength() != 0) {
			auto pre_it = pre_process_list.Front();
			
			while (pre_it!= pre_process_list.GetHead()) {
				if (!cur_pro_map.count(pre_it->val_.process_id)) {
					if (pre_it->val_.process_name!="pslist"&&pre_it->val_.process_name != "cmd") {
						EndProcessInfo end_pro;
						end_pro.process_id = pre_it->val_.process_id;
						end_pro.process_name = pre_it->val_.process_name;
						end_pro.elapsed_time = pre_it->val_.elapsed_time;
						end_pro.end_time = current_time;
						end_process_list.TopInsert(end_pro);
					}
				}
				pre_it = pre_it->next_;
			}
		}

		//清除终端数据
		system("cls");

		//打印
		PrintCurProcessInfo(cur_process_list);
		std::cout << std::endl;
		PrintEndProcessInfo(end_process_list);

		//初始化状态
		cur_pro_map.clear();
		pre_process_list = cur_process_list;
		cur_process_list.Clear();
		len--;

		//休眠
		Sleep(1000);
	}
	

	system("pause");
	return 0;
}