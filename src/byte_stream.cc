#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
  capacity_( capacity ), 
  buffer_count( 0 ),
  pop_count( 0 ),
  stream(),
  is_closed_flag( false),
  is_error_flag( false )
 {}

void Writer::push( string data )
{
  // Your code here.
  for (char& x:data) {
    if (available_capacity() > 0) {
      stream.push(x);
      buffer_count++;
    } 
  }
  (void)data;
}

void Writer::close()
{
  if (!is_closed_flag)
    is_closed_flag = true;
  // Your code here.
}

void Writer::set_error()
{
  // Your code here.
  if (!is_error_flag)
    is_error_flag = true;
}

bool Writer::is_closed() const
{
  // Your code here.
  return is_closed_flag;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - static_cast<uint64_t>(stream.size());
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return buffer_count;
}

string_view Reader::peek() const
{
  // Your code here.
  return string_view(&stream.front(),1);
}

bool Reader::is_finished() const
{
  // Your code here.
  if (stream.size() == 0 && is_closed_flag == true) {
    return true;
  } else {
    return false;
  }
}

bool Reader::has_error() const
{
  // Your code here.
  return is_error_flag;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  while (len--) {
    stream.pop();
    pop_count++;
  }
  (void)len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return stream.size();
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return pop_count;
}
