#include "String.hpp"
String::String() = default;
String::String(size_t sz, char character) {
  size_ = sz;
  capacity_ = sz;
  string_ = new char[sz];
  memset(string_, character, capacity_);
}
String::String(const char* str_cpy) {
  size_ = strlen(str_cpy);
  capacity_ = size_ + 1;
  string_ = new char[capacity_];
  memcpy(string_, str_cpy, capacity_);
}
String::~String() { delete[] string_; }
String::String(const String& string_cpy) {
  size_ = string_cpy.size_;
  capacity_ = size_;
  string_ = new char[size_];
  memcpy(string_, string_cpy.string_, size_);
}
void String::Clear() {
  memset(string_, '\0', size_);
  size_ = 0;
}
void String::Swap(String& other) {
  size_t tmp_sz = other.size_;
  size_t tmp_capacity = other.capacity_;
  char* tmp_str = other.string_;
  other.size_ = size_;
  other.capacity_ = capacity_;
  other.string_ = string_;
  size_ = tmp_sz;
  capacity_ = tmp_capacity;
  string_ = tmp_str;
}
String& String::operator=(String string_cpy) {
  Swap(string_cpy);
  return *this;
}
char String::operator[](const size_t kIndex) const {
  return *(string_ + kIndex);
}
char& String::operator[](const size_t kIndex) { return *(string_ + kIndex); }
String& String::operator+=(const String& str_plus) {
  size_t sz = size_;
  Resize(size_ + str_plus.size_);
  memcpy((string_ + sz), str_plus.string_, str_plus.size_);
  return *this;
}
String String::operator+(const String& str_plus) {
  String copy = *this;
  copy += str_plus;
  return copy;
}
String operator+(const String& left, const String& right) {
  String copy = left;
  copy += right;
  return copy;
}
bool String::operator==(const String& s) const {
  bool res = !(*this > s || s > *this);
  return res;
}
bool String::operator<(const String& str_cmp) const {
  size_t cnt = 0;
  for (; cnt != str_cmp.size_ && cnt != size_ &&
         str_cmp.string_[cnt] == string_[cnt];
       ++cnt) {
  }
  if (cnt == size_ && cnt == str_cmp.size_) {
    return false;
  }
  if (cnt == size_) {
    return true;
  }
  if (cnt == str_cmp.size_) {
    return false;
  }
  return (*(str_cmp.string_ + cnt) > *(string_ + cnt));
}

bool String::operator>(const String& s) const { return (s < *this); }

bool String::operator!=(const String& s) const { return !(*this == s); }

bool String::operator<=(const String& s) const {
  return (*this < s) || (*this == s);
}

bool String::operator>=(const String& s) const {
  return (*this > s) || (*this == s);
}
String& String::operator*=(size_t mul_val) {
  String copy;
  for (size_t i = 0; i < mul_val; ++i) {
    copy += *this;
  }
  Swap(copy);
  return *this;
}
String operator*(const String& str, size_t mul_val) {
  String copy(str);
  copy *= mul_val;
  return copy;
}
void String::PushBack(char character) {
  if (capacity_ == size_) {
    Reserve(2 * capacity_ + 1);
  }
  *(string_ + size_) = character;
  ++size_;
}
void String::PopBack() {
  if (size_ > 0) {
    --size_;
    string_[size_] = '\0';
  }
}
void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    String copy(new_cap);
    copy.size_ = size_;
    memcpy(copy.string_, string_, size_);
    Swap(copy);
  }
}
void String::ShrinkToFit() {
  if (capacity_ <= size_) {
    return;
  }
  String copy;
  copy.capacity_ = size_;
  copy.size_ = size_;
  copy.string_ = new char[size_];
  memcpy(copy.string_, string_, size_);
  Swap(copy);
}
void String::Resize(size_t new_size, char character) {
  if (size_ < new_size) {
    if (capacity_ > new_size) {
      memset(string_ + size_, ' ', new_size - size_);
      size_ = new_size;
    } else {
      capacity_ = 2 * new_size;
      String copy = String(capacity_, character);
      memcpy(copy.string_, string_, size_);
      Swap(copy);
      size_ = new_size;
    }
  } else if (size_ > new_size) {
    size_ = new_size;
    memset(string_ + size_, ' ', capacity_ - size_);
  }
}
String String::Join(const std::vector<String>& strings) const {
  String copy;
  if (strings.empty()) {
    return copy;
  }
  copy += strings[0];
  for (size_t i = 1; i < strings.size(); ++i) {
    copy += *this;
    copy += strings[i];
  }
  return copy;
}
std::vector<String> String::Split(const String& delim) {
  std::vector<String> ans;
  size_t i = 0;
  String tmp_buff;
  while (size_ > 0 && i <= size_ - delim.size_) {
    String tmp = String(delim.size_);
    for (size_t j = 0; j < delim.size_; ++j) {
      tmp.string_[j] = string_[i + j];
    }
    if (tmp != delim) {
      String sing_str = String(1);
      memcpy(sing_str.string_, string_ + i, sizeof(char));
      tmp_buff += sing_str;
      ++i;
    } else {
      i += delim.size_;
      ans.push_back(tmp_buff);
      tmp_buff.Clear();
    }
  }
  if (i != size_) {
    String tmp = String(size_ - i);
    memcpy(tmp.string_, string_ + i, (size_ - i) * sizeof(char));
    if (tmp != delim) {
      tmp_buff += tmp;
    }
  }
  ans.push_back(tmp_buff);
  return ans;
}
char String::Front() const { return string_[0]; }
char String::Back() const {
  return size_ > 0 ? string_[size_ - 1] : string_[0];
}
char& String::Front() { return string_[0]; }
char& String::Back() { return size_ > 0 ? string_[size_ - 1] : string_[0]; }
size_t String::Size() const { return size_; }
size_t String::Capacity() const { return capacity_; }
const char* String::Data() const { return string_; }
bool String::Empty() const { return size_ <= 0; }
std::ostream& operator<<(std::ostream& ostream, const String& string) {
  for (int i = 0; i < string.Size(); ++i) {
    ostream << string.Data()[i];
  }
  return ostream;
}
std::istream& operator>>(std::istream& istream, String& string) {
  char ch;
  string.Clear();
  while (istream.get(ch) && ch != '\n') {
    string.PushBack(ch);
  }
  return istream;
}