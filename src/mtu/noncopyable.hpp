#pragma once


namespace mtu{

class noncopyable
{
public:
    noncopyable() = default;
    ~noncopyable() = default;

private:
    noncopyable(const noncopyable& other) = delete;
    noncopyable& operator=(const noncopyable& opther) = delete;
};

} // ns