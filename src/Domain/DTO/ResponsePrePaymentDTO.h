#pragma once
#include <string>
using namespace std;

class ResponsePrePaymentDTO{
    public:
        string msg_type;
        string src_id;
        string dst_id;
        int item_code;
        int item_num;
        bool availability;

        ResponsePrePaymentDTO() = default;
        ResponsePrePaymentDTO(string msg_type, string src_id, string dst_id, int item_code, int item_num, bool availability) : msg_type(msg_type), src_id(src_id), dst_id(dst_id), item_code(item_code), item_num(item_num), availability(availability) {}
};