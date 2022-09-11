#include "FileSearcher.h"

#include <assert.h>
#include "utils/Win32.h"
 

FileSearcher::FileSearcher()
	: hadBeenError(false)
	, searchIn()
	, searchFor()
{
}

void FileSearcher::SetSearchInFolder(const std::wstring& srchIn)
{
	searchIn = srchIn;
	AddTrailingSplashIfNeccesary(searchIn);
}

void FileSearcher::SetSearchPattern(const std::wstring& srchFor)
{
	searchFor = srchFor;
}

bool FileSearcher::Letss(std::vector<std::wstring>& outList)
{
	if (searchIn.size() == 0 && searchFor.size() == 0) {
		return false;
	}

	hadBeenError = false;
	std::wstring withPrefix = L"\\\\?\\" + searchIn;
	LetssRecoursive(withPrefix, outList);
	return !hadBeenError;
}

bool FileSearcher::IsSpecialFile(std::wstring& fileName)
{
	static std::wstring dotFile = std::wstring(L".");
	static std::wstring ddotFile = std::wstring(L"..");

	return (fileName == dotFile) || (fileName == ddotFile);
}

void FileSearcher::AddTrailingSplashIfNeccesary(std::wstring& path)
{
	wchar_t slash = L'\\';
	if (path.back() != slash) path += slash;
}

void FileSearcher::LetssRecoursive(std::wstring& inDir, std::vector<std::wstring>& outList)
{
	AddTrailingSplashIfNeccesary(inDir);

	const std::wstring path = inDir + searchFor;

	WIN32_FIND_DATAW ffData;
	HANDLE hFind = ::FindFirstFileW(path.data(), &ffData);
	if (!IsWinHandleValid(hFind)) {
		hadBeenError = true;
		return;
	}

	do {
		std::wstring fileName(ffData.cFileName);
		if (IsSpecialFile(fileName)) continue;

		std::wstring entry = inDir + fileName;
		outList.push_back(entry);

		if ((ffData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			LetssRecoursive(entry, outList);					
	} while (::FindNextFileW(hFind, &ffData));			

	::FindClose(hFind);
}
