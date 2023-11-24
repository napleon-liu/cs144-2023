#include "reassembler.hh"
#include <iostream>
using namespace std;

Reassembler::Reassembler():
  _reassemblerBuffer(),
  _flagBuffer(),
  _first_unpopped_index(0),
  _first_unassembled_index(0),
  _first_unacceptable_index(0),
  _bytes_pending(0),
  _eof_index(0),
  _init_flag(true){}

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  if (_init_flag == true) {
    _reassemblerBuffer.resize(64*INT16_MAX);
    _flagBuffer.resize(64*INT16_MAX);
    _flagBuffer.assign(64*INT16_MAX, false);
    _first_unacceptable_index = _first_unassembled_index + output.available_capacity();
    _init_flag = false;
  }

  _first_unacceptable_index = output.bytes_pushed() + output.available_capacity();



  uint64_t origin_first_index = first_index;
  uint64_t end_index = _first_unacceptable_index < (first_index + data.size()) ?
                      _first_unacceptable_index : (first_index + data.size()); 

  if (first_index >= _first_unacceptable_index)
    return ; 

  if (first_index <= _first_unassembled_index)
    first_index = _first_unassembled_index;


  for (uint64_t i = first_index; i < end_index; i++) {
    _reassemblerBuffer[i] = data[i-origin_first_index];
    if (_flagBuffer[i] == false)
      _bytes_pending++;
    _flagBuffer[i] = true;
  }

  if (is_last_substring) {
    _eof_index = origin_first_index + data.size() + 1;
  }


  if (first_index != _first_unassembled_index) {
    return ;
  }

  uint64_t curr_index = first_index;
  int push_size = 0;
  string push_data = "";
  while (curr_index < _first_unacceptable_index && _flagBuffer[curr_index] == true) {
    _flagBuffer[curr_index] = false;
    push_data += _reassemblerBuffer[curr_index];
    push_size++;
    curr_index++;
  }
  // if (data == "ab" && first_index == 0)
  //   cout << push_data << endl;
  output.push(push_data);
  _first_unassembled_index += push_size;
  // cout << _bytes_pending;
  _bytes_pending -= push_size;
  // cout << _bytes_pending;
  if (data == "b")
    cout << "is_last_substring: " << is_last_substring << endl;
  if (is_last_substring) {
    _eof_index = origin_first_index + data.size() + 1;
  }

  if (output.bytes_pushed() + 1 == _eof_index) {
    output.close();
  }
  
  (void)first_index;
  (void)data;
  (void)is_last_substring;
  (void)output;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return _bytes_pending;
}
