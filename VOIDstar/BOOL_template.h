#define BOOL boolean32


template <typename T>
struct BOOL
{
private:
	T b = 0;
public:
	BOOL<T>();
	BOOL<T>(bool);
	BOOL<T>(bool&);
	BOOL<T>(T);
	BOOL<T>(T&);
	BOOL<T>(bool, T);
	void set(bool val, T i);
	void set(bool val);
	void set(bool tab[], T count, bool val);
	bool get(T i);
	bool get();
	operator int();
	operator bool();
	bool operator[](T) const;
	bool & operator[](T);
	void operator=(T&);
	void operator=(const T&);
	void operator=(bool&);
	void operator=(const bool&);
	void operator=(BOOL&);
	void operator=(const BOOL&);
};

template <typename T>
BOOL<T>::BOOL()
{
	this->set(false);
}

template <typename T>
BOOL<T>::BOOL(bool i)
{
	this->set(i);
}

template <typename T>
BOOL<T>::BOOL(bool & i)
{
	this->set(i);
}

template <typename T>
BOOL<T>::BOOL(T i)
{
	this->set(i);
}

template <typename T>
BOOL<T>::BOOL(T & i)
{
	this->set(i);
}

template <typename T>
BOOL<T>::BOOL(bool val, T i)
{
	this->set(val, i);
}

template <typename T>
void BOOL<T>::set(bool val, T ix)
{
	if (ix > (sizeof(T) * 8) - 1 || ix < 0)
	{
		return;
	}
	T* tab = new T[sizeof(T) * 8];
	for (T i = 0; i < sizeof(T) * 8; i++)
	{
		tab[i] = 0;
	}
	T temp = this->b;
	unsigned int tsize = (sizeof(T));
	for (T i = (sizeof(T) * 8) - 1;; i--)
	{
		tab[i] = temp % 2;
		temp = temp >> 1;
		if (i==0)
		{
			break;
		}
	}
	tab[ix] = val;
	this->b = 0;
	for (T i = 0; i < (sizeof(T) * 8); i++)
	{
		this->b += tab[i];
		i != (sizeof(T) * 8) - 1 ? this->b = this->b << 1 : false;
	}

	delete[]tab;
}

template <typename T>
void BOOL<T>::set(bool val)
{
	this->set(val, 0);
}

template <typename T>
void BOOL<T>::set(bool tab[], T count, bool val)
{
	for (int i = 0; i < count; i++)
	{
		this->set(val, tab[i]);
	}
}

template <typename T>
bool BOOL<T>::get(T ix)
{
	if (ix > (sizeof(T) * 8) - 1 || ix < 0)
	{
		return 0;
	}
	T temp = this->b;
	temp = (temp >> ((sizeof(T) * 8) - ix - 1));
	temp = temp % 2;
	return temp;
}

template <typename T>
bool BOOL<T>::get()
{
	return this->get(0);
}

template <typename T>
BOOL<T>::operator int()
{
	return (int)this->get();
}

template <typename T>
BOOL<T>::operator bool()
{
	return this->get();
}

template <typename T>
bool & BOOL<T>::operator[](T ix)
{
	bool ret = this->get(ix);
	return ret;
}

template <typename T>
bool BOOL<T>::operator[](T ix) const
{
	return this->get(ix);;
}

template <typename T>
void BOOL<T>::operator=(T &other)
{
	this->b = other;
	return;
}

template <typename T>
void BOOL<T>::operator=(const T &other)
{
	this->b = other;
	return;
}

template <typename T>
void BOOL<T>::operator=(bool &other)
{
	this->b = other;
	return;
}

template <typename T>
void BOOL<T>::operator=(const bool &other)
{
	this->b = other;
	return;
}

template <typename T>
void BOOL<T>::operator=(BOOL &other)
{
	this->b = other.b;
	return;
}

template <typename T>
void BOOL<T>::operator=(const BOOL &other)
{
	this->b = other.b;
	return;
}