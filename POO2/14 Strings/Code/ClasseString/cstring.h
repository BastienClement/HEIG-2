/* 
 * File:   cstring.h
 * Author: Alain
 *
 * Created on 10. mars 2016, 11:31
 */

#ifndef CSTRING_H
#define    CSTRING_H

#include <ostream>
#include <stdexcept>

class String {
public:
	String();
	String(const char*);
	String(const String&);
	String(const char);
	String(const int);
	String(const double);
	String(const bool);
	String(const char* cs, size_t start, size_t len);
	String(const String& str, size_t start, size_t len);

	~String();

	const int size() const;
	const char* c_str() const;
	char& at(size_t) throw(std::runtime_error);
	const char& at(size_t) const throw(std::runtime_error);
	bool isEqual(const char*) const;
	bool isEqual(const String&) const;
	String& assign(const char*);
	String& assign(const String&);
	String& append(const char*);
	String& append(const String&);

	bool operator==(const char*) const;
	bool operator==(const String&) const;
	String& operator=(const String&);
	String operator+(const String&) const;
	String& operator+=(const String&);

	String slice(size_t start, size_t end) const throw(std::runtime_error);

	friend std::ostream& operator<<(std::ostream&, const String&);

private:
	char* _str;
	size_t _size;

};

#endif	/* CSTRING_H */

