#ifndef _CLASSEVENT_HPP_
#define _CLASSEVENT_HPP_

/**
*   @brief      Class Event define is used in the test.
*/
class Event {
 public:
    Event() { /* Empty */ }
 
    Event(void *_ptr, std::time_t _time) {
        ptr = _ptr;
        time = _time;
    }
 
    std::time_t getTime() {
        return this->time;
    }
 
    void *getPtr() {
        return this->ptr;
    }

    bool operator<(Event event) const {
        return (this->time < event.getTime());
    }

 private:
    void *ptr;       
    std::time_t time;  
};

#ifndef