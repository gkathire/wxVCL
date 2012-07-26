/*
 Authors : Guru Kathiresan - gururamnath@yahoo.com ,
 FreePascal Team - http://www.freepascal.org

 License :

 Short Verion : wxVCL is distributed under Modified LGPL
 (the same license used by FCL, LCL). In short,
 this license allows you to use wxVCL in your application either
 statically or dynamically linked (and keep your source code as
 closed source) but you cannot sell wxVCL alone as a seperate
 product or claim owner ship for it and when you make a change to
 the wxVCL library (not your application code), you have to give
 the changes (of the wxVCL library code) back to the community.

 Long Version : The source code of wxVCL is distributed under the
 Library GNU General Public License with the following modification:

 As a special exception, the copyright holders of this library give you
 permission to link this library with independent modules to produce an
 executable, regardless of the license terms of these independent modules,
 and to copy and distribute the resulting executable under terms of your choice,
 provided that you also meet, for each linked independent module, the terms
 and conditions of the license of that module. An independent module is a module
 which is not derived from or based on this library. If you modify this
 library, you may extend this exception to your version of the library, but you are
 not obligated to do so. If you do not wish to do so, delete this exception
 statement from your version.
 */

#ifndef SysSetH
#define SysSetH

#include <set>
#include <iterator>
#include <cstdarg>

template<class T>
class DelphiSet
{
private:
	std::set<T>FSet;

public:
	DelphiSet()
	{
	}

	DelphiSet(T StartValue, T EndValue)
	{
		int Value = EndValue - StartValue;
		if (StartValue > EndValue)
			throw 1;
		// ERangeError::CreateFmt ( wxT("Start Value %d is greater than End Value %d"), StartValue, EndValue );
		this->AddRange(StartValue, Value);
	}

	DelphiSet(T StartValue, T EndValue, const int Count)
	{
		if (StartValue > EndValue)
			throw 1;
		// ERangeError::CreateFmt ( wxT("Start Value %d is greater than End Value %d"), StartValue, EndValue );
		this->AddRange(StartValue, Count);
	}

	DelphiSet(const DelphiSet<T>& src)
	{
		FSet = src.FSet;
	}

	DelphiSet<T>&operator = (const DelphiSet<T>&rhs)
	{
		if (this != &rhs)
		{
			FSet.clear();
			FSet.insert(rhs.FSet.begin(), rhs.FSet.end());
		}
		return *this;
	}

	DelphiSet<T>& operator += (const DelphiSet<T>& rhs)
	{
		FSet.insert(rhs.FSet.begin(), rhs.FSet.end());
		return *this;
	}

	DelphiSet<T>& operator -= (const DelphiSet<T>& rhs)
	{
		FSet.erase(rhs.FSet.begin(), rhs.FSet.end());
		return *this;
	}

	// commenting becos this does not work with GCC
	DelphiSet<T>& operator *= (const DelphiSet<T>& rhs)
	{
		typename std::set<T>::const_iterator itr;
		for (itr = rhs.FSet.begin(); itr != rhs.FSet.end(); itr++)
		{
			if (FSet.find(*itr) == FSet.end())
				continue;
			FSet.erase(*itr);
		}
		return *this;
	}

	DelphiSet<T>operator +(const DelphiSet<T>& rhs) const
	{
		DelphiSet<T>S = *this;
		S.FSet.insert(rhs.FSet.begin(), rhs.FSet.end());
		return S;
	}

	DelphiSet<T>& Add(const T Value)
	{
		FSet.insert(Value);
		return *this;
	}

	DelphiSet<T>& AddRange(const T RangeStartValue, const int Count)
	{
		T RangeStartForAdd = RangeStartValue;
		for (int i = 0; i < Count; ++i)
			this->Add(RangeStartForAdd++);
		return *this;
	}

	DelphiSet<T>& Add(const T RangeStartValue, const T RangeEndValue)
	{
		if (RangeEndValue < RangeStartValue)
			throw 1;
		// ERangeError::CreateFmt ( wxT("Start Value %d is greater than End Value %d"), RangeStartValue, RangeEndValue );
		int Range = RangeEndValue - RangeStartValue;
		T RangeStartForAdd = RangeStartValue;
		for (int i = 0; i < Range; ++i)
			this->Add(RangeStartForAdd++);
		return *this;
	}

	DelphiSet<T>& Remove(T Value)
	{
		FSet.erase(Value);
		return *this;
	}

	DelphiSet<T>& Remove(T RangeStartValue, T RangeEndValue)
	{
		if (RangeEndValue < RangeStartValue)
			throw 1;
		// ERangeError::CreateFmt ( wxT("Start Value %d is greater than End Value %d"), RangeStartValue, RangeEndValue );
		for (T i = RangeStartValue; i <= RangeEndValue; ++i)
			this->Remove(i);
		return *this;
	}

	bool Contains(const T Value) const
	{
		if (FSet.find(Value) == FSet.end())
			return false;
		else
			return true;
	}

	bool In(const T Value) const
	{
		return Contains(Value);
	}

	bool Has(const T Value) const
	{
		return Contains(Value);
	}

	void Clear()
	{
		FSet.clear();
	}

	void Empty() const
	{
		FSet.empty();
	}

	bool operator == (const DelphiSet<T>& rhs) const
	{
		if (FSet.size() != rhs.FSet.size())
			return false;

		std::set<T>setDifference;
		set_symmetric_difference(FSet.begin(), FSet.end(), rhs.FSet.begin(),
		  rhs.FSet.end(), back_inserter(setDifference));
		return (setDifference.size() == 0);

	}

	bool operator != (const DelphiSet<T>& rhs) const
	{
		return !operator == (rhs);
	}

	DelphiSet<T>& AddItems(T FirstItem, ...)
	{
		va_list argList;
		this->Add(FirstItem);
		va_start(argList, FirstItem);
		T NewItem;
		while ((NewItem = (T)va_arg(argList, int)) != 0)
		{
			this->Add(NewItem);
		}
		va_end(argList);
		return *this;
	}

	static DelphiSet<T>& Init(T FirstItem, ...)
	{
		DelphiSet<T> *NewOne = new DelphiSet<T>();
		va_list argList;
		NewOne->Add(FirstItem);
		va_start(argList, FirstItem);
		T NewItem;
		while ((NewItem = (T)va_arg(argList, int)) != 0)
		{
			NewOne->Add(NewItem);
		}
		va_end(argList);
		return *NewOne;
	}

	static DelphiSet<T>& InitRange(T FirstItem, T LastItem)
	{
		DelphiSet<T> *NewOne = new DelphiSet<T>();
		NewOne->Add(FirstItem, LastItem);
		return *NewOne;
	}

	static DelphiSet<T>& InitRange(T FirstItem, T LastItem, const int Count)
	{
		DelphiSet<T> *NewOne = new DelphiSet<T>();
		NewOne->AddRange(FirstItem, Count);
		return *NewOne;
	}

	bool IsEmpty(void)
	{
		return (FSet.size() == 0);
	}

	wxString ToString(void)
	{
		wxString Result;
		Result.Alloc(FSet.size());
		typename std::set<T>::const_iterator itr;
		for (itr = FSet.begin(); itr != FSet.end(); itr++)
		{
			Result += (wxChar) * itr;
		}

		return Result;
	}

};

#endif
