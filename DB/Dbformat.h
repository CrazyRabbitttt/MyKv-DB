#ifndef KVDB_DBFORMAT_H_
#define KVDB_DBFORMAT_H_

#include <string>
#include <stdint.h>

#include "../Include/Comparator.h"
namespace kvdb {

class InternalKey;

//The type of value which is inserted on the SkipList, value Or delete 
enum ValueType {kTypeDelete = 0, kTypeValue = 1 };

//Sequence number, 64 bits   7bytes(sequence), 1byte(type)
typedef uint64_t SequenceNumber;

//7-bit SeqNumber
static const SequenceNumber kMaxSequenceNumber = ((0x1ull << 56) - 1);

static const ValueType kValueTypeForSeek = kTypeValue;


//A tool class for Get
class LookupKey {
public:

    //用于构造Key
    LookupKey(const Slice& user_key, SequenceNumber sequence);

    //No copying 
    LookupKey(const LookupKey&)=delete;
    LookupKey& operator=(const LookupKey&)=delete;

    ~LookupKey();

    //返回适用于Memtable中的key
    Slice memtable_key() const {

    }



private:
    //Get的时候传入的是Key, args for construct the Key 
    
    // klen             varint32        size_
    // user_key         char[klen]      key_
    // tag(seq & type)  uint64          
    //                                  end_

    const char* size_;
    const char* userKey_;
    const char* end_;
    
    char space_[200];  
};




//抽象的一个类，使用了内部中的一个指定的比较器
class InternalKeyComparator : public Comparator {
 private:
     const Comparator* user_comparator_;        //????

 public:

    explicit InternalKeyComparator(const Comparator* c) 
        :user_comparator_(c) {}
    
    const char* Name() const override;

    int Compare(const Slice& a, const Slice& b) const override;

    void FindShortestSeparator(std::string* start,
                                     const Slice& limit) const override;
    void FindShortSuccessor(std::string* key) const override;

    int Compare(const InternalKey& a, const InternalKey& b) const ;

    const Comparator* user_Comparator() const {
        return user_comparator_;
    }

};







}
#endif