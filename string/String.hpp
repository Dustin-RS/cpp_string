#pragma once
#include <cstring>
#include <iostream>
#include <vector>
class String {
 public:
  String();
  ~String();
  String(size_t sz, char character = '\0');
  String(const String& str);
  String(const char* str_cpy);
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size, char character = '\0');
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& Front();
  char& Back();
  char Front() const;
  char Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;
  String& operator=(String string_cpy);
  String& operator+=(const String& str_plus);
  String operator+(const String& str_plus);
  String& operator*=(size_t mul_val);
  char& operator[](size_t index);
  char operator[](size_t index) const;
  bool operator<(const String& str_cmp) const;
  bool operator<=(const String& str_cmp) const;
  bool operator>(const String& str_cmp) const;
  bool operator>=(const String& str_cmp) const;
  bool operator!=(const String& str_cmp) const;
  bool operator==(const String& str_cmp) const;
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings) const;
  friend std::istream& operator>>(std::istream& istream, String& string);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* string_ = nullptr;
};
std::ostream& operator<<(std::ostream& ostream, const String& string);
std::istream& operator>>(std::istream& istream, String& string);
String operator+(const String& left, const String& right);
String operator*(const String& str, size_t mul_val);