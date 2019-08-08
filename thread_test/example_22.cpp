#include <future>
#include <iostream>
#include <thread>

void modifyMessage(std::promise<std::string> &&prms, std::string message) {
  std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
  std::string modifiedMessage = message + " has been modified";
  prms.set_value(modifiedMessage);
}

int main() {
  // define message
  std::string messageToThread = "My Message";

  // create promise and future
  std::promise<std::string> prms;
  std::future<std::string> ftr = prms.get_future();

  // start thread and pass promise as argument
  std::thread t(modifyMessage, std::move(prms), messageToThread);

  // print original message to console
  std::cout << "Original message from main(): " << messageToThread << std::endl;

  // retrieve modified message via future and print to console
  std::string messageFromThread = ftr.get();
  std::cout << "Modified message from thread(): " << messageFromThread
            << std::endl;

  // thread barrier
  t.join();

  return 0;
}

/*
In the following example, we want to declare a promise which allows for
transmitting a string between two threads and modifying it in the process.

Image

After defining a message, we have to create a suitable promise that can take a
string object. To obtain the corresponding future, we need to call the method
get_future() on the promise. Promise and future are the two types of the
communication channel we want to use to pass a string between threads. The
communication channel set up in this manner can only pass a string.

We can now create a thread that takes a function and we will pass it the promise
as an argument as well as the message to be modified. Promises can not be
copied, because the promise-future concept is a two-point communication channel
for one-time use. Therefore, we must pass the promise to the thread function
using std::move. The thread will then, during its execution, use the promise to
pass back the modified message.

The thread function takes the promise as an rvalue reference in accordance with
move semantics. After waiting for several seconds, the message is modified and
the method set_value() is called on the promise.

Back in the main thread, after starting the thread, the original message is
printed to the console. Then, we start listening on the other end of the
communication channel by calling the function get() on the future. This method
will block until data is available - which happens as soon as set_value has been
called on the promise (from the thread). If the result is movable (which is the
case for std::string), it will be moved - otherwise it will be copied instead.
After the data has been received (with a considerable delay), the modified
message is printed to the console.

Image

It is also possible that the worker value calls set_value on the promise before
get() is called on the future. In this case, get() returns immediately without
any delay. After get() has been called once, the future is no longer usable.
This makes sense as the normal mode of data exchange between promise and future
works with std::move - and in this case, the data is no longer available in the
channel after the first call to get(). If get() is called a second time, an
exception is thrown.

*/
