#pragma once
#include <map>
#include <string>
#include <memory>
#include <tchar.h>
template<typename T>
class TAssetManager
{
public:
	std::map<std::wstring, std::unique_ptr<T>> m_AssetMap;
public:
	std::wstring GetSplitName(std::wstring fullpath)
	{
		std::wstring name;
		TCHAR dirve[256] = { 0, };
		TCHAR dir[256] = { 0, };
		TCHAR filename[256] = { 0, };
		TCHAR ext[256] = { 0, };
		_tsplitpath_s(fullpath.c_str(),	dirve, dir, filename, ext);
		name = filename;
		name += ext;
		return name;
	}
	T* LoadPtr(const std::wstring& filePath)
	{
		auto name = GetSplitName(filePath);
		auto it = m_AssetMap.find(name);
		if (it != m_AssetMap.end())
		{
			return it->second.get(); // Asset already exists
		}
		std::unique_ptr<T> asset = std::make_unique<T>();
		if (!asset->Load(filePath))
		{
			return nullptr; // Failed to load asset
		}
		m_AssetMap.insert(std::make_pair(name, std::move(asset)));
		return m_AssetMap[name].get();
	}
	bool    Load(const std::wstring& filePath, std::wstring& name)
	{
		name = GetSplitName(filePath);
		auto it = m_AssetMap.find(name);
		if (it != m_AssetMap.end())
		{
			return true; // Asset already exists
		}
		std::unique_ptr<T> asset = std::make_unique<T>();
		if (!asset->Load(filePath))
		{
			return false; // Failed to load asset
		}
		m_AssetMap.insert(std::make_pair(name, std::move(asset)));
		return true;
	}	
	T* GetAsset(const std::wstring& name)
	{
		auto it = m_AssetMap.find(name);
		if (it != m_AssetMap.end())
		{
			return it->second.get();
		}
		return nullptr;
	}
	void AddAsset(const std::wstring& name, std::unique_ptr<T> asset)
	{
		m_AssetMap[name] = std::move(asset);
	}
	void RemoveAsset(const std::wstring& name)
	{
		m_AssetMap.erase(name);
	}
	void Clear()
	{
		m_AssetMap.clear();
	}

};

