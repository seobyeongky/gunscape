/*OOPARTS OOPARTS OOPARTS OOPARTS OOPARTS OOPARTS OOPARTS
=========================================================
	s_map.h

	smap template container class�� header file�Դϴ�.

	smap�� Static Map�� �ظ��Դϴ�.

	���� :

	{
		smap<int, string> s_map;

		s_map.insert(38, "ho ho");
		s_map.insert(3232, "ha ha");

		cout << "38 : " <<  s_map[38] << endl;
	}

=======================================================*/

#pragma once

#include <algorithm>
#include <vector>
#include <list>

template <typename KeyT, typename T>
class smap {
/*	���� �迭(associative array) container�Դϴ�.
	STL�� map�� red-black tree�� ��������� �� class�� �ٸ� ����ε�
	���� �뷮, �幮 ����, ������ �� ������ sorted vector����Դϴ�.
	�˻� ������尡 ��������� �۴ٰ� �� �� �ְڽ��ϴ�.
	��, KeyT Ÿ���� < �����ڰ� �����Ǿ��־���մϴ�. */

private:
	typedef typename std::list<T>			el_list_t;
	typedef typename el_list_t::iterator	iter_t;

public:
	class Pair
	{
		friend class smap;

	public:
		const KeyT &	key() const { return _key; }
		T &				element() { return *_iter;}

		bool	operator < (const KeyT & key) const { return this->_key < key; }

	private:
		KeyT		_key;
		iter_t		_iter;

		Pair() : _key(), _iter() { }
		Pair(const KeyT & key, const iter_t & iter) : _key(key), _iter(iter) { }
	};

private:
	typedef std::vector<Pair>	pair_vec_t;

public:
	class Iter
	{
	friend class smap;
	
	private:
		typedef typename pair_vec_t::iterator iter_type_t; 

		iter_type_t _it;

	public:
				 Iter() : _it() { }
				 Iter(const Iter & iter) : _it(iter._it) { }
				 Iter(const iter_type_t & it) : _it(it) { }
		Iter &	 operator = (const Iter & iter) { _it = iter._it; return *this; }
				~Iter() { }

		Pair	 operator * () { return *_it; }
		Pair	 operator -> () { return *_it; }
		bool	 operator == (const Iter & iter) const { return this->_it == iter._it; }
		bool	 operator != (const Iter & iter) const { return this->_it != iter._it; }
		Iter &	 operator ++ () { ++_it; return *this; }
		Iter &	 operator -- () { --_it; return *this; }
		Iter &	 operator += (int n) { _it += n; return *this; }
		Iter &	 operator -= (int n) { _it -= n; return *this; }
		Iter &	 operator + (int n) { Iter new_it(*this); new_it += n; return new_it; }
		Iter &	 operator - (int n) { Iter new_it(*this); new_it -= n; return new_it; }
	};

public:
			 smap() : _pair_vec(), _el_list() { }
			~smap() { }

	// ���Ҹ� �����մϴ�.
	// key�� �̹� ������ false�� ��ȯ�ϰ� ��� ���Կ� �����ϸ� true�� ��ȯ�մϴ�.
	bool	 insert(const KeyT & key, const T & el);
	bool	 insert(const Pair & pair) { return insert(pair.key, *pair.el_ptr); }

	// ���Ҹ� ����ϴ�.
	// ���� ���� ���� iterator�� ��ȯ�մϴ�.
	// ���Ҹ� ����� ���� iterator�� �Ҵ��� �ǹǷ� ��ȯ�� iterator�� �����Ͻʽÿ�.
	Iter	 erase(const Iter & iter) 
	{
		_el_list.erase(iter._it->_iter);
		return _pair_vec.erase(iter._it);
	}

	void	 erase(const KeyT & key)
	{
		Iter iter;
		if(find(key, &iter)) erase(iter);
	}
	
	// Ư�� ���Ҹ� ã���ϴ�.
	// ��ã���� false�� ��ȯ�մϴ�.
	// ã���� true�� ��ȯ�ϰ� ���� it_ptr�� ã�� iterator�� �����մϴ�.
	bool	 find(const KeyT & key, Iter * it_ptr = nullptr);

	void	 clear() { _pair_vec.clear(); _el_list.clear(); }
	bool	 check_empty() const { return _pair_vec.empty(); }

	Iter	 begin() { return Iter(_pair_vec.begin()); }
	Iter	 end() { return Iter(_pair_vec.end()); }

	T	&	 operator [] (const KeyT & key);

	size_t	 size() const { return _pair_vec.size(); }

private:
	pair_vec_t	_pair_vec;
	el_list_t	_el_list;
};

template <typename KeyT, typename T>
bool smap<KeyT, T>::insert(const KeyT & key, const T & el)
{
	pair_vec_t::iterator it = std::lower_bound(_pair_vec.begin(), _pair_vec.end(), key);
	if(it != _pair_vec.end() && it->_key == key) return false;

	_el_list.push_front(el);
	_pair_vec.insert(it, Pair(key, _el_list.begin()));
	return true;
}

template <typename KeyT, typename T>
bool smap<KeyT, T>::find(const KeyT & key, Iter * it_ptr)
{
	if(_pair_vec.empty()) return false;
	pair_vec_t::iterator it = lower_bound(_pair_vec.begin(), _pair_vec.end(), key);
	if(it == _pair_vec.end() || it != _pair_vec.end() && it->_key != key) return false;
	if(it_ptr != nullptr) it_ptr->_it = it;
	return true;
}

template <typename KeyT, typename T>
T & smap<KeyT, T>::operator [] (const KeyT & key)
{
	Iter iter;
	if(find(key, &iter)) return (*iter).element();
	else
	{
		// �� ã������ �ϳ� �����.
		// T Ÿ���� �⺻ �����ڰ� �־����
		insert(key, T());
		return _el_list.front();
	}
}