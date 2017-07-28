// ShareMemoryClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"  
#include <Windows.h>
#include <iostream>  
using namespace std;  
//int main()
//{    
//	HANDLE hMutex      = NULL;    
//	HANDLE hFileMapping   = NULL;    
//	LPVOID lpShareMemory  = NULL;    
//	HANDLE hServerWriteOver = NULL;    
//	HANDLE hClientReadOver = NULL;       
//	hMutex = OpenMutex(MUTEX_ALL_ACCESS,      FALSE,      L"SM_Mutex");  
//	if (NULL == hMutex)    
//	{     
//		if (ERROR_FILE_NOT_FOUND == GetLastError())    
//		{        
//			cout << "OpenMutex fail: file not found!" << endl;        
//			goto CLIENT_SHARE_MEMORY_END;    
//		}      
//		else    
//		{        
//			cout << "OpenMutex fail:" << GetLastError() << endl;       
//			goto CLIENT_SHARE_MEMORY_END;     
//		}  
//	}      
//	if (WaitForSingleObject(hMutex, 5000) != WAIT_OBJECT_0)//hMutex 一旦互斥对象处于有信号状态，则该函数返回   
//	{      
//		DWORD dwErr = GetLastError();      
//		goto CLIENT_SHARE_MEMORY_END;    
//	}      
//	//open share memory   
//	hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,      FALSE,      L"ShareMemoryTest");   
//	if (NULL == hFileMapping)  
//	{      
//		cout << "OpenFileMapping" << GetLastError() << endl;      
//		goto CLIENT_SHARE_MEMORY_END;   
//	}      
//	lpShareMemory = MapViewOfFile(hFileMapping,      FILE_MAP_ALL_ACCESS,      0,      0,      0);   
//	if (NULL == lpShareMemory)   
//	{    
//		cout << "MapViewOfFile" << GetLastError() << endl;      
//		goto CLIENT_SHARE_MEMORY_END;   
//	}      
//	//read and write data    
//	hServerWriteOver = CreateEvent(NULL,      TRUE,      FALSE,      L"ServerWriteOver");    
//	hClientReadOver = CreateEvent(NULL,      TRUE,      FALSE,      L"ClientReadOver");   
//	if (NULL == hServerWriteOver ||      NULL == hClientReadOver)    
//	{     
//		cout << "CreateEvent" << GetLastError() << endl;     
//		goto CLIENT_SHARE_MEMORY_END;   
//	}       
//	char p = 0;   
//	char* q = (char*)lpShareMemory;    
//	do    
//	{     
//		if (!SetEvent(hClientReadOver))         
//			goto CLIENT_SHARE_MEMORY_END;        
//		if (WaitForSingleObject(hServerWriteOver, INFINITE) != WAIT_OBJECT_0)         
//			goto CLIENT_SHARE_MEMORY_END;        
//		p = q[0];      putchar(p);     
//		if (!ResetEvent(hServerWriteOver))       
//			goto CLIENT_SHARE_MEMORY_END;   
//	} while (p != '\n');    
//
//	CLIENT_SHARE_MEMORY_END:   
//	//release share memory   
//	if (NULL != hServerWriteOver)
//		CloseHandle(hServerWriteOver);   
//	if (NULL != hClientReadOver) 
//		CloseHandle(hClientReadOver);   
//	if (NULL != lpShareMemory)   
//		UnmapViewOfFile(lpShareMemory);   
//	if (NULL != hFileMapping)    
//		CloseHandle(hFileMapping);   
//	if (NULL != hMutex)      
//		ReleaseMutex(hMutex);    
//	return 0; 
//} 


int main()
{

	int loop = 1000000;
	while(loop)
	{
		HANDLE hRemoteVideoFileMap = NULL;
		HANDLE hLocalVideoFileMap = NULL;
		int n = 1000;

		if (!hRemoteVideoFileMap)  // 不存在则创建  
		{  
			hRemoteVideoFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1920*1080*3/2*6,  ("RemoteVideoData"));  
		} 

		if (!hLocalVideoFileMap)  // 不存在则创建  
		{  
			hLocalVideoFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1920*1080*3/2*6,  ("LocalVideoData"));  
		}  

		while(n > 0)
		{
			HANDLE hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ("LocalVideoData"));   
			if(hFileMap)
			{
				char* dataBuffer = (char*)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0,  0, 0);   
				if(dataBuffer == NULL)
				{
					DWORD ErrNo = GetLastError();
				}
				UnmapViewOfFile(dataBuffer);  
			}
			n--;
		}

		HANDLE hRemoteVideoFileMap1 = NULL;
		HANDLE hLocalVideoFileMap1 = NULL;

		hRemoteVideoFileMap1 = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ("RemoteVideoData"));  
		hLocalVideoFileMap1 = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ("LocalVideoData"));  

		CloseHandle(hRemoteVideoFileMap1);
		CloseHandle(hLocalVideoFileMap1);
		hRemoteVideoFileMap1 = NULL;
		hLocalVideoFileMap1 = NULL;
		loop--;
	}
}

