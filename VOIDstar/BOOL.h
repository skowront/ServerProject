#define BOOL boolean32



struct BOOL
{
private:
	unsigned int b = 0;
public:
	BOOL();
	BOOL(bool);
	BOOL(bool&);
	BOOL(unsigned int);
	BOOL(unsigned int&);
	BOOL(bool, unsigned int);
	void set(bool val, unsigned int i);
	void set(bool val);
	void set(bool tab [], unsigned int count, bool val);
	bool get(unsigned int i);
	bool get();
	operator int();
	operator bool();
	BOOL operator[](unsigned int);
	void operator=(unsigned int&);
	void operator=(const unsigned int&);
	void operator=(bool&);
	void operator=(const bool&);
	void operator=(BOOL&);
	void operator=(const BOOL&);
};



