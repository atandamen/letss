#pragma once

#include <Windows.h>
#include <string>
#include <vector>

class FileSearcher final
{
	bool hadBeenError;
	std::wstring searchIn, searchFor;
public:
	FileSearcher();
public:
	void SetSearchInFolder(const std::wstring &srchIn);
	void SetSearchPattern(const std::wstring& srchFor);

	bool Letss(std::vector<std::wstring>& outList);

private:
	bool IsSpecialFile(std::wstring& fileName);
	void AddTrailingSplashIfNeccesary(std::wstring& path);
	void LetssRecoursive(std::wstring& inDir, std::vector<std::wstring>& outList);
};

