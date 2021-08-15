#ifndef __BOXUTIL_OPTIONAL_H__
#define __BOXUTIL_OPTIONAL_H__

namespace boxutil {

template <typename T>
class Optional final {

public:

    Optional():is_value_set{false}, value{} {}
    Optional(T _v):is_value_set{true}, value{_v} {}
    ~Optional(){}

    Optional(const Optional &_other){
        is_value_set = _other.is_value_set;
        value = _other.value;
    }
    Optional(Optional&&) = delete;
    Optional& operator=(const Optional&) = delete;
    Optional& operator=(Optional&&) = delete;

    void SetValue(T _v) {
        value = _v;
        is_value_set = true;
    }
    bool IsSet() const {
        return is_value_set;
    }
    T GetValue() const {
        return value;
    }

private:

    bool is_value_set;
    T value;

};

} // ns: boxutil

#endif // __BOXUTIL_OPTIONAL_H__
